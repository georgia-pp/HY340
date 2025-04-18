#include "avm.h"

/* 
    HY340 Languages and Compilers              Alpha Compiler Virtual Machine

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

vector<double> constNumArr;
vector<string> constStrArr;
vector<string> constLibFunArr;
vector<userfunc*> constUserFunArr;
map<char*,library_func_t> libfunctions;
vector<avminstr*> avm_code;
vector<string> warnings;
vector<string> errors;
avm_memcell stack[AVM_STACKSIZE];
int GLOBAL_NUM = 0;

avm_memcell ax, bx, cx;
avm_memcell retval;
unsigned top, topsp;
unsigned int totalActuals=0;

extern void execute_assign (avminstr*);
extern void execute_add (avminstr*);
extern void execute_sub (avminstr*);
extern void execute_mul (avminstr*);
extern void execute_div (avminstr*);
extern void execute_mod (avminstr*);
extern void execute_uminus (avminstr*);
extern void execute_and (avminstr*);
extern void execute_or (avminstr*);
extern void execute_not (avminstr*);
extern void execute_jeq (avminstr*);
extern void execute_jne (avminstr*);
extern void execute_jle (avminstr*);
extern void execute_jge (avminstr*);
extern void execute_jlt (avminstr*);
extern void execute_jgt (avminstr*);
extern void execute_call (avminstr*);
extern void execute_pusharg (avminstr*);
extern void execute_funcenter (avminstr*);
extern void execute_funcexit (avminstr*);
extern void execute_newtable (avminstr*);
extern void execute_tablegetelem (avminstr*);
extern void execute_tablesetelem (avminstr*);
extern void execute_nop (avminstr*);
extern void execute_jump (avminstr*);

extern bool executionFinished;
extern unsigned pc;

memclear_func_t memclearFuncs[]={
    0,
    memclear_string,
    0,
    memclear_table,
    0,
    0,
    0,
    0
};

tostring_func_t tostringFuncs[]{
    number_tostring,
    string_tostring,
    bool_tostring,
    table_tostring,
    userfunc_tostring, 
    libfunc_tostring,
    nil_tostring,
    undef_tostring,  
};

execute_func_t executeFuncs[]={
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_funcenter,
    execute_funcexit,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop,
    execute_jump
};

string convert_vmopcodeenum[] =
{
    "assign",
    "add",
    "sub", 
    "mul",
    "div", 
    "mod",
    "uminus", 
    "and", 
    "or", 
    "not", 
    "jeq", 
    "jne",
    "jle", 
    "jge", 
    "jlt",
    "jgt", 
    "call",
    "pusharg", 
    "funcenter",
    "funcexit",
    "newtable",
    "tablegetelem",
    "tablesetelem",
    "nop",
    "jump" 
};

string convert_vmargenum[] =
{
    "label_a",
    "global_a",
    "formal_a", 
    "local_a",
    "number_a", 
    "string_a",
    "bool_a", 
    "nil_a", 
    "userfunc_a", 
    "libfunc_a", 
    "retval_a", 
    "empty_a",
};

string convert_memcelltype[] =
{
    "number_m",
    "string_m",
    "bool_m", 
    "table_m",
    "userfunc_m", 
    "libfunc_m",
    "nil_m", 
    "undef_m"
};

arithmetic_func_t arithmeticFuncs[] = {
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl
};

cmp_func comparisonFuncs[] = {
    jle_impl,
    jge_impl,
    jlt_impl,
    jgt_impl,
};

tobool_func_t toboolFuncs[]={
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undef_tobool
};

string typeStrings[]{
    "number",
    "string",
    "boolean",
    "table",
    "userfunction",
    "libraryfunction",
    "nil",
    "undef"
};

//-----------------------Clear Memory--------------------------------
void avm_memcellclear(avm_memcell* m){
    if(m->type != undef_m){
        memclear_func_t f = memclearFuncs[m->type];
        if(f)
            (*f)(m);
        m->type = undef_m;
    }
}

void memclear_string(avm_memcell* m){
    assert(m->strVal);
    free(m->strVal);
}

void memclear_table(avm_memcell* m){
    assert(m->tableVal);
    avm_tabledecrefcounter(m->tableVal);
}

//--------------------------------------------------------
void avm_warning(string str) {
    warnings.push_back(str);
}

void avm_error(string str) {
    errors.push_back(str);
    cout<<"\033[1;31m"<<str<<"\033[0m"<<endl;
    exit(1);
    executionFinished = 1;
}

void avm_initstack(void){
    for(unsigned i=0; i<AVM_STACKSIZE; i++){
        AVM_WIPEOUT(stack[i]);
        stack[i].type = undef_m;
    }

    top = AVM_STACKSIZE - GLOBAL_NUM - 1;
    topsp = AVM_STACKSIZE - 1;
}

double consts_getnumber(unsigned index) {
    return constNumArr.at(index);
}

string consts_getstring(unsigned index) {
    return constStrArr.at(index);
}

string libfuncs_getused(unsigned index) {
    return constLibFunArr.at(index);
}

userfunc* userfuncs_getfunc(unsigned index) {
    return constUserFunArr.at(index);
}

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg){
    switch(arg->type){
        case global_a: return &stack[AVM_STACKSIZE-1-arg->val];
        case formal_a: return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
        case local_a: return &stack[topsp-arg->val];
        case number_a: {
            reg->type = number_m;
            reg->numVal = consts_getnumber(arg->val);
            return reg;
        }
        case string_a:{ 
            reg->type = string_m;
            reg->strVal = strdup(consts_getstring(arg->val).c_str());
            return reg;
        }
        case bool_a:{   
            reg->type = bool_m;
            reg->boolVal = arg->val;
            return reg;
        }
        case nil_a: {
            reg->type = nil_m; 
            return reg;
        }
        case userfunc_a:{
            reg->type = userfunc_m;
            reg->funcVal = userfuncs_getfunc(arg->val)->address;
            return reg;
        }
        case libfunc_a: { 
            reg->type = libfunc_m;
            reg->libfuncVal = strdup(libfuncs_getused(arg->val).c_str());
            return reg;
        }
        case retval_a: return &retval;
        default: assert(0);
    }
}

void avm_tableincrefcounter(avm_table* t){
    ++t->refCounter;
}

void avm_tabledecrefcounter(avm_table* t){
    assert(t->refCounter > 0);
    if(!--t->refCounter) avm_tabledestroy(t);
}

void avm_tablebucketsinit(avm_table_bucket** p){
    for(unsigned i=0; i<AVM_TABLE_HASHSIZE; i++)
        p[i] = (avm_table_bucket*) 0;
}

void avm_tablebucketsdestroy(avm_table_bucket** p){
    for(unsigned i=0; i<AVM_TABLE_HASHSIZE; ++i, ++p){
        for(avm_table_bucket* b = *p; b;){
            avm_table_bucket* del = b;
            b = b->next;
            avm_memcellclear(&del->key);
            avm_memcellclear(&del->value);
            free(del);
        }
        p[i] = (avm_table_bucket*) 0;
    }
    
}

void avm_tabledestroy(avm_table* t){
    //avm_tablebucketsdestroy(t->strIndexed);
    //avm_tablebucketsdestroy(t->numIndexed);
    for (size_t i = 0; i < t->numtotal; i++)
    {
        avm_memcellclear(&t->numIndexed[i]->key);
        avm_memcellclear(&t->numIndexed[i]->value);
        free(t->numIndexed[i]);
    }

    for (size_t i = 0; i < t->strtotal; i++)
    {
        avm_memcellclear(&t->strIndexed[i]->key);
        avm_memcellclear(&t->strIndexed[i]->value);
        free(t->strIndexed[i]);
    }
    
    free(t);
}

avm_memcell* avm_tablegetelem(avm_table* table, avm_memcell* index){
    if (index->type == string_m) {
        if (lookUpIndex(table,index) != -1) return &table->strIndexed[lookUpIndex(table,index)]->value;
        
    } else if (index->type == number_m) {
        if (lookUpIndex(table,index) != -1) return &table->numIndexed[lookUpIndex(table,index)]->value;
           
    } else {
        avm_error("index of array is type: "+convert_memcelltype[index->type]+", must be number_m or string_m");
        exit(1);
    }
    avm_memcell* m = (avm_memcell*) malloc(sizeof(avm_memcell));
    m->type = nil_m;
    return m;
}

avm_table* avm_tablenew(void) {
    avm_table* t = (avm_table*) malloc(sizeof(avm_table));
    AVM_WIPEOUT(*t);

    t->refCounter = t->total = 0;
    t->strtotal = 0;
    t->numtotal = 0;
    avm_tablebucketsinit(t->numIndexed);
    avm_tablebucketsinit(t->strIndexed);
    return t;
}

//---------------------------------------------------------------------------
void avm_assign(avm_memcell* lv, avm_memcell* rv){
    if(lv==rv) return;
    if(lv->type == table_m && rv->type == table_m && lv->tableVal== rv->tableVal) return;
    if(rv->type == undef_m) avm_warning("assigning from 'undef' content!");
    avm_memcellclear(lv);
    memcpy(lv,rv,sizeof(avm_memcell));

    if(lv->type == string_m) lv->strVal = strdup(rv->strVal);
    else{
        if(lv->type == table_m) avm_tableincrefcounter(lv->tableVal);
    }
}

void avm_dec_top(void) {
    if (!top) {
        avm_error("stack overflow");
        executionFinished = 1;
    } else --top;
}

void avm_push_envvalue (unsigned val){
    stack[top].type = number_m;
    stack[top].numVal = val;
    avm_dec_top();
}

void avm_callsaveenvironment(){
    avm_push_envvalue(totalActuals);
    assert(avm_code[pc]->opcode ==call_v);
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top + totalActuals+2);
    avm_push_envvalue(topsp);
}

void avm_calllibfunc(char* id){
    library_func_t f = avm_getlibraryfunc(id);
    if(!f){
        avm_error("unsupported library function called");
        executionFinished = true;
    }
    else{
        avm_callsaveenvironment();
        topsp=top;
        totalActuals=0;
        (*f)();
        if(!executionFinished) execute_funcexit((avminstr*) 0);
    }
}

void avm_push_table_arg(avm_table* t){
    stack[top].type = table_m;
    avm_tableincrefcounter(stack[top].tableVal=t);
    ++totalActuals;
    avm_dec_top();
}

void avm_call_functor(avm_table* t){
    cx.type= string_m;
    string s = "\"()\"";
    cx.strVal= strdup(s.c_str());
    avm_memcell* f = avm_tablegetelem(t,&cx);
    if(!f) avm_error("in calling table: no () element found!");
    else{
        if(f->type == table_m) avm_call_functor(f->tableVal);
        else{
            if(f->type == userfunc_m){
                avm_push_table_arg(t);
                avm_callsaveenvironment();
                pc = f->funcVal;
                assert(pc < AVM_ENDING_PC && avm_code[pc]->opcode == funcenter_v);
            }
            else avm_error("in calling table: illegal () element value!");
        }
        /*if(f->type == userfunc_m) {
            avm_push_table_arg(t);
            avm_callsaveenvironment();
            pc = f->funcVal;
            assert(pc < AVM_ENDING_PC && avm_code[pc]->opcode == funcenter_v);
        } else if(f->type == table_m){
            avm_call_functor(t);
        }*/

    }
}

char* avm_tostring(avm_memcell* m) {
    assert(m->type >= 0 && m->type <= undef_m);
    return (*tostringFuncs[m->type])(m);
}

char* number_tostring(avm_memcell* m) {
    string str = to_string(m->numVal);
    str.pop_back();
    str.pop_back();
    str.pop_back();
    char* s = (char*)str.c_str();
    return strdup(s);
}

char* string_tostring(avm_memcell* m) {
    return m->strVal;
}

char* bool_tostring(avm_memcell* m) {

    if(m->boolVal == 0) {
       string s = "false";
       char* str = (char*)s.c_str();
        return strdup(str);
    }
    string s = "true";
    char* str = (char*)s.c_str();
    return strdup(str);
}

char* table_tostring(avm_memcell* m) {
    /*string s = "TABLE";
    char* str = (char*)s.c_str();
    return strdup(str);*/
    string s = "["+m->tableVal->to_print;
    s.pop_back();
    s.pop_back();
    s+="]";
    char* str = (char*)s.c_str();
    return strdup(str);
}

char* userfunc_tostring(avm_memcell* m) {
    string s = "user function " + to_string(m->funcVal); 
    char* str = (char*)s.c_str();
    return strdup(str);
}

char* libfunc_tostring(avm_memcell* m) {
    string name = m->libfuncVal;
    string s = "library function " + name;
    char* str = (char*)s.c_str();
    return strdup(str);
}

char* undef_tostring(avm_memcell* m) {
    string s = "undef";
    char* str = (char*)s.c_str();
    return strdup(str);
}

char* nil_tostring(avm_memcell* m) {
    string s = "nil";
    char* str = (char*)s.c_str();
    return strdup(str);
}

unsigned avm_get_envvalue(unsigned int i){
    assert(stack[i].type == number_m);
    unsigned int val= (unsigned) stack[i].numVal;
    assert(stack[i].numVal == ((double) val));
    return val;
}

//-----------------------------Library Functions------------------------------

library_func_t avm_getlibraryfunc(char* funcname) {
    for(auto n : libfunctions){
        if(strcmp(n.first, funcname) == 0) {
            
            return n.second;
        }
    }

    return NULL;
}

void avm_registerlibfunc(char* id, library_func_t addr){
    libfunctions.insert(libfunctions.end(), pair<char*, library_func_t>(id, addr));
}

unsigned avm_totalactuals(void) {
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

avm_memcell* avm_getactual(unsigned i) {
    assert(i < avm_totalactuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void libfunc_print(void) {
    unsigned n = avm_totalactuals();
    for (unsigned i = 0; i < n; ++i) {
        char* s  = avm_tostring(avm_getactual(i));
        //puts(s);
        cout<<s;
        //free(s);
    }
    if (n>0) cout<<endl;
}

void libfunc_typeof(void) {
    unsigned n = avm_totalactuals();
    if(n != 1) avm_error("one argument (not "+to_string(n)+") expected in \'typeof\'!");
    else {
        avm_memcellclear(&retval);
        retval.type = string_m;
        string str = typeStrings[avm_getactual(0)->type];
        retval.strVal = strdup((char*)str.c_str());
    }
}

void libfunc_totalarguments(void) {
    unsigned int oldtopsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    if (avm_totalactuals() > 0) avm_warning( "Ingored arguments in library function 'totalarguments' call!");
    if(oldtopsp == AVM_STACKSIZE-1) { 
        avm_warning( "library function 'totalarguments' called outside of function!");
        avm_memcellclear(&retval);
        retval.type = nil_m;
    }
    else {
        avm_memcellclear(&retval);
        retval.type = number_m;
        retval.numVal = avm_get_envvalue(oldtopsp + AVM_NUMACTUALS_OFFSET);
    }
}

void libfunc_argument(void) {
    int oldtopsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    unsigned n = avm_totalactuals();
    
    if(n != 1) avm_error("one argument (not "+to_string(n)+") expected in \'argument\'!");
    else {
        if(oldtopsp ==  AVM_STACKSIZE-1) { 
            cout<<n<<endl;
            avm_warning( "library function 'argument' called outside of function!");
            avm_memcellclear(&retval);
            retval.type = nil_m;
        }
        else {
            cout<<n<<endl;
            if ((avm_getactual(0)->type != number_m) ) avm_error( "library function 'argument' called with invalid type argument ("+typeStrings[avm_getactual(0)->type]+")!"); 
            if (floor(avm_getactual(0)->numVal) != ceil(avm_getactual(0)->numVal)) avm_error( "library function 'argument' called with invalid type argument double, argument must be an integer!"); 
            if (avm_get_envvalue(oldtopsp + AVM_NUMACTUALS_OFFSET) <= avm_getactual(0)->numVal) avm_error( "library function 'argument' called with invalid argument, argument number "+to_string(avm_getactual(0)->numVal)+" doesnt exist!"); 
            //cout<<stack[oldtopsp + AVM_NUMACTUALS_OFFSET + 1 + int(avm_getactual(0)->numVal)].type<<endl;
            avm_memcellclear(&retval);
            switch (stack[oldtopsp + AVM_NUMACTUALS_OFFSET + 1 + int(avm_getactual(0)->numVal)].type)
            {
            case number_m: {
                retval.type = number_m;
                retval.numVal = stack[oldtopsp + AVM_NUMACTUALS_OFFSET + 1 + int(avm_getactual(0)->numVal)].numVal;
                break;
            }
            case string_m: {
                retval.type = string_m;
                retval.strVal = strdup(stack[oldtopsp + AVM_NUMACTUALS_OFFSET + 1 + int(avm_getactual(0)->numVal)].strVal);
                break;
            }
            case bool_m: {
                retval.type = bool_m;
                retval.boolVal = stack[oldtopsp + AVM_NUMACTUALS_OFFSET + 1 + int(avm_getactual(0)->numVal)].boolVal;
                break;
            }
            case table_m: {
                retval.type = table_m;
                retval.tableVal = stack[oldtopsp + AVM_NUMACTUALS_OFFSET + 1 + int(avm_getactual(0)->numVal)].tableVal;
                break;
            }
            case userfunc_m: {
                retval.type = userfunc_m;
                retval.funcVal = stack[oldtopsp + AVM_NUMACTUALS_OFFSET + 1 + int(avm_getactual(0)->numVal)].funcVal;
                break;
            } 
            case libfunc_m: {
                retval.type = libfunc_m;
                retval.libfuncVal = strdup(stack[oldtopsp + AVM_NUMACTUALS_OFFSET + 1 + int(avm_getactual(0)->numVal)].libfuncVal);
                break;
            }
            case nil_m: {
                retval.type = nil_m;
                break;
            }
            case undef_m: {
                retval.type = undef_m;
                break;
            }
            default:
                assert(0);
                break;
            }
        }
    }
}

void libfunct_objecttotalmembers(void) {
    unsigned n = avm_totalactuals();
    if(n != 1) avm_error("one argument (not "+to_string(n)+") expected in \'objecttotalmembers\'!");
    else {
        if (avm_getactual(0)->type != table_m) avm_error("library function 'objecttotalmembers' called with invalid type argument ("+typeStrings[avm_getactual(0)->type]+")!");
        else {
            avm_memcellclear(&retval);
            retval.type = number_m;
            retval.numVal = avm_getactual(0)->tableVal->total;
        }
    }
}

void libfunc_strtonum(void) {
    unsigned n = avm_totalactuals();
    if(n != 1) avm_error("one argument (not "+to_string(n)+") expected in \'strtonum\'!");
    else {
        if (avm_getactual(0)->type != string_m) avm_error("library function 'strtonum' called with invalid type argument ("+typeStrings[avm_getactual(0)->type]+")!");
        else {
            avm_memcellclear(&retval);
            if(isNumber(strdup(avm_getactual(0)->strVal)) == 1) {
                retval.type = number_m;
                string s = strdup(avm_getactual(0)->strVal);
                s = s.substr(1,s.length()-2);
                retval.numVal = stod((char*)s.c_str());
            } else if (isNumber(strdup(avm_getactual(0)->strVal)) == -1) { 
                retval.type = number_m;
                string s = strdup(avm_getactual(0)->strVal);
                s = s.substr(2,s.length()-2);
                retval.numVal = stod((char*)s.c_str())*-1;
            }else {
                retval.type = nil_m;
            }
        }
    }
}

void libfunct_sqrt(void) {
    unsigned n = avm_totalactuals();
    if(n != 1) avm_error("one argument (not "+to_string(n)+") expected in \'sqrt\'!");
    else {
        if(avm_getactual(0)->type != number_m) avm_error("library function 'sqrt' called with invalid type argument ("+typeStrings[avm_getactual(0)->type]+")!");
        else {
            avm_memcellclear(&retval);
            if(avm_getactual(0)->numVal < 0) {
                retval.type = nil_m;
            } else {
                retval.type = number_m;
                retval.numVal = sqrt(avm_getactual(0)->numVal);
            }
        }
    }
}

void libfunct_cos(void) {
    unsigned n = avm_totalactuals();
    if(n != 1) avm_error("one argument (not "+to_string(n)+") expected in \'cos\'!");
    else {
        if(avm_getactual(0)->type != number_m) avm_error("library function 'cos' called with invalid type argument ("+typeStrings[avm_getactual(0)->type]+")!");
        else {
            avm_memcellclear(&retval);
            retval.type = number_m;
            retval.numVal = cos((avm_getactual(0)->numVal) * M_PI / 180);    
        }
    }
}

void libfunct_sin(void) {
    unsigned n = avm_totalactuals();
    if(n != 1) avm_error("one argument (not "+to_string(n)+") expected in \'sin\'!");
    else {
        if(avm_getactual(0)->type != number_m) avm_error("library function 'sin' called with invalid type argument ("+typeStrings[avm_getactual(0)->type]+")!");
        else {
            avm_memcellclear(&retval);
            retval.type = number_m;
            retval.numVal = sin((avm_getactual(0)->numVal) * M_PI / 180);    
        }
    }
}

void libfunct_input(void){
    string str;
    const char* inpt;
    cin>> str;
    inpt = str.c_str();
    if(strcmp(inpt, "true")==0) {
        retval.type = bool_m;
        retval.boolVal =true;
    }
    else if(strcmp(inpt, "false")==0){
        retval.type = bool_m;
        retval.boolVal =false;
    }
    else if(strcmp(inpt, "nil")==0) retval.type = nil_m;

    /*isNumber(inpt);
    if(num!=NULL){
        retval.type = number_m;
        retval.numVal = *num;
    }
    else{
        retval.type = string_m;
        strcpy(retval.strVal, inpt);
    }*/
}



int isNumber(const char* s) {
    int start;
    int length = strlen(s);

    if (length>=2 && s[0] == '\"' && s[1] == '\"')
    {
        return 0;
    }
    
    if (length>=3 && s[0] == '\"' && s[1] == '-' && s[2] == '\"')
    {
        return 0;
    }

    if(s[0] == '\"') {
        if (s[1] == '-') start = 2;
        else start = 1;
    }
    else start = 0;
    for(int i = start; i < length-1; i++ ) {
        if(!isdigit(s[i]) && s[i] != '.') {
            return 0;
        }
    }
    if (s[1] == '-') return -1;
    return 1;
}

userfunc* avm_getfuncinfo(unsigned address) {
    assert(avm_code.at(address)->opcode == funcenter_v);
    return constUserFunArr.at(avm_code.at(address)->result->val);
}

double add_impl(double x,double y){return x+y;}
double sub_impl(double x,double y){return x-y;}
double mul_impl(double x,double y){
    if(x == 0 || y == 0) return double(0);
    return x*y;
}
double div_impl(double x,double y){return x/y;}
double mod_impl(double x,double y){return ((unsigned) x)% ((unsigned) y);}

bool jge_impl(double x,double y) {
    if (x>=y) return true;
    return false;
}
bool jgt_impl(double x,double y) {
    if(x>y) return true;
    return false;
}
bool jle_impl(double x,double y) {
    if(x<=y) return true;
    return false;
}
bool jlt_impl(double x,double y) {
    if(x<y) return true;
    return false;
}

bool number_tobool(avm_memcell* m){return m->numVal!=0;}
bool string_tobool(avm_memcell* m){return m->strVal[0]!=0;}
bool bool_tobool(avm_memcell* m){return m->boolVal;}
bool table_tobool(avm_memcell* m){return 1;}
bool userfunc_tobool(avm_memcell* m){return 1;}
bool libfunc_tobool(avm_memcell* m){return 1;}
bool nil_tobool(avm_memcell* m){return 0;}
bool undef_tobool(avm_memcell* m){return 0;}

bool avm_tobool(avm_memcell* m) {
    assert(m->type >= 0 && m->type <= undef_m);
    return (*toboolFuncs[m->type])(m);
}

int lookUpIndex(avm_table* t, avm_memcell* i) {
    if (t->total != 0) {
       // int j=0;
        switch (i->type)
        {
            case string_m: {
               
                for (size_t j = 0; j < t->strtotal; j++)
                {
                    if(strcmp(t->strIndexed[j]->key.strVal,i->strVal) == 0) return j;
                }
                return -1;
                break;
            }
            case number_m: {
               
                for (size_t j = 0; j < t->numtotal; j++)
                {
                    if(t->numIndexed[j]->key.numVal == i->numVal) return j;
                }
                
                return -1;
                break;
            }
            default:
                avm_error("index of array is type: "+convert_memcelltype[i->type]+", must be number_m or string_m");
                break;
            }
    } else {
        return -1; //index not found
    }
    return -1;
}

void moveBuckets(avm_table* t, int index, avm_memcell* i) {
    int total = t->strtotal;
    if (i->type == number_m) total = t->numtotal;

    for (size_t j = index+1; j < total; j++)
    {
        if(i->type == number_m) t->numIndexed[j-1] = t->numIndexed[j];
        else t->strIndexed[j-1] = t->strIndexed[j];
    }

}

void avm_tablesetelem(avm_table* t, avm_memcell* i, avm_memcell* c) {
    switch (i->type)
    {
        case string_m: {
            string s = strdup(i->strVal); //
            s = s.substr(1,s.length()-2); //
            int index = lookUpIndex(t,i);
            if(index != -1) { //index laready exists
                if (c->type == nil_m) {
                    erase_fromprint(t, s);//
                    avm_table_bucket* b = t->strIndexed[index];
                    moveBuckets(t,index,i);
                    free(b);
                    t->total--;
                    t->strtotal--;
                } else {
                    replace_fromprint(t, s, c);//
                    avm_assign(&t->strIndexed[index]->value,c);
                }
            } else {
                t->to_print+="{ "+s+" : ";//
                add_toprint(t,c);//
                t->to_print+=" }, ";//
                t->strIndexed[t->strtotal] = (avm_table_bucket*) malloc(sizeof(avm_table_bucket));
                t->strIndexed[t->strtotal]->key.type = undef_m;
                t->strIndexed[t->strtotal]->value.type = undef_m;
                avm_assign(&t->strIndexed[t->strtotal]->key, i);
                avm_assign(&t->strIndexed[t->strtotal]->value,c);
                //if (t->strtotal>0) t->strIndexed[t->strtotal-1]->next = t->strIndexed[t->strtotal];
                t->strtotal++;
                t->total++;
            } 
            
            break;
        }
        case number_m: {
            string s= number_tostring(i);//
            int index = lookUpIndex(t,i);
            if(index != -1) { //index laready exists
                if (c->type == nil_m) {
                    erase_fromprint(t, s);//
                    avm_table_bucket* b = t->numIndexed[index];
                    moveBuckets(t,index,i);
                    free(b);
                    t->total--;
                    t->numtotal--;
                } else {
                    replace_fromprint(t, s, c);//
                    avm_assign(&t->numIndexed[index]->value,c);
                }
            } else {
                t->to_print+="{ "+s+" : ";//
                add_toprint(t,c);//
                t->to_print+=" }, ";//
                t->numIndexed[t->numtotal] = (avm_table_bucket*) malloc(sizeof(avm_table_bucket));
                
                t->numIndexed[t->numtotal]->key.type = undef_m;
                t->numIndexed[t->numtotal]->value.type = undef_m;
                avm_assign(&t->numIndexed[t->numtotal]->key, i);
                avm_assign(&t->numIndexed[t->numtotal]->value,c);
                //if (t->numtotal>0) t->numIndexed[t->numtotal-1]->next = t->numIndexed[t->strtotal];
                t->numtotal++;
                t->total++;
            } 
            
            break;
        }
        default: {
            avm_error("index of array is type: "+convert_memcelltype[i->type]+", must be number_m or string_m");
            break;
        }
    }
}

void add_toprint(avm_table* t, avm_memcell* c){
    switch(c->type){
        case number_m:{ t->to_print+= (number_tostring(c)); break;}
        case string_m: {
            string s = strdup(c->strVal);
            s = s.substr(1,s.length()-2);
            t->to_print+= s;
            break;}
        case bool_m:{ t->to_print+= (c->boolVal) ? "true" : "false"; break;}
        case table_m:{ 
            t->to_print+= table_tostring(c); break;}
        case userfunc_m: {
            for(int i=0; i<constUserFunArr.size(); i++){
                if(constUserFunArr.at(i)->address == c->funcVal){
                    t->to_print+=constUserFunArr.at(i)->id;
                    break;
                }
            }
            break;
            }
        case libfunc_m:{t->to_print+=c->libfuncVal; break;}
        case nil_m:{ t->to_print+=nil_tostring(c); break;}
        case undef_m: {t->to_print+=undef_tostring(c); break;}
        default: break;
    }
}

void erase_fromprint(avm_table* t, string index){
    size_t i, j, k;
    string replace = "";
    index = "{ "+index;
    i = t->to_print.find(index);

    for(j=i; j<= t->to_print.size(); j++){
        if(t->to_print[j] == ':') break;  
    }
    
    if(t->to_print[j+2] == '['){
        for(k=j+2; k<= t->to_print.size(); k++){
            if(t->to_print[k] == ']') break;  
        }
        k+=2;
    }
    else{
        for(k=j+2; k<=t->to_print.size(); k++) {  
            if(t->to_print[k] == '}') break;
        } 
    }
    
    if(i != string::npos){
        t->to_print.replace(i,k-i+3,replace);
    }
}

void replace_fromprint(avm_table* t, string index, avm_memcell* c){
    size_t i, j,k;
    string key, replace;
    switch(c->type){
        case number_m:{ key= (number_tostring(c)); break;}
        case string_m: {
            string s = strdup(c->strVal);
            s = s.substr(1,s.length()-2);
            key= s;
            break;
        }
        case bool_m:{ key= (c->boolVal) ? "true" : "false"; break;}
        case table_m:{ key= table_tostring(c); break;}
        case userfunc_m: {
            for(int i=0; i<constUserFunArr.size(); i++){
                if(constUserFunArr.at(i)->address == c->funcVal){
                    key=constUserFunArr.at(i)->id;
                    break;
                }
            }
            break;
        }
        case libfunc_m:{key=c->libfuncVal; break;}
        case nil_m:{ key=nil_tostring(c); break;}
        case undef_m: {key=undef_tostring(c); break;}
        default:{ break; }
    }
    replace = index +" : " + key + " ";
    i = t->to_print.find(index);
    for(j=i; j<= t->to_print.size(); j++){
        if(t->to_print[j] == ':') break;  
    }
    
    if(t->to_print[j+2] == '['){
        for(k=j+2; k<= t->to_print.size(); k++){
            if(t->to_print[k] == ']') break;  
        }
        k+=2;
    }
    else{
        for(k=j+2; k<=t->to_print.size(); k++) {  
            if(t->to_print[k] == '}') break;
        } 
    }
    
    if(i != string::npos){
        t->to_print.replace(i,k-i,replace);
    }
}