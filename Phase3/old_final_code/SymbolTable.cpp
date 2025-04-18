/* 
    HY340 Languages and Compilers              Alpha Compiler Syntactical Analysis

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

#include "SymbolTable.h"
#include "quad.h"
#define stringify( name ) #name
extern  SymbolTable* symbolTable;
extern  vector<quad> quads;
extern  unsigned total;
extern bool RETURNEXPR;
unsigned int programVarOffset     = 0;
unsigned int functionLocalOffset  = 0;
unsigned int formalArgOffset      = 0;
unsigned int scopeSpaceCounter    = 1;

scopespace_t currscopespace(void){
    if(scopeSpaceCounter == 1) {
        return programvar;
    }
    else
        if (scopeSpaceCounter % 2 == 0)
            return formalarg;
        else
            return functionlocal;
}

unsigned currscopeoffset(void){
    switch(currscopespace()){
        case programvar: return programVarOffset;
        case functionlocal: return functionLocalOffset;
        case formalarg: return formalArgOffset;

        default: assert(0);
    }
}

void incurrscopeoffset(void){
    switch(currscopespace()){
        case programvar:  ++programVarOffset; break;
        case functionlocal: ++functionLocalOffset; break;
        case formalarg: ++formalArgOffset; break;
        default: assert(0);
    }
}

void enterscopespace(void){
    ++scopeSpaceCounter;
}

void exitscopespace(void){
    assert(scopeSpaceCounter>1);
    --scopeSpaceCounter;
}

void resetformalargspace(){formalArgOffset=0;}
void resetfunclocalspace(){ functionLocalOffset  = 0;}

void resetscopespace(void) {
    switch(currscopespace()){
        case programvar:  assert(0); break;
        case functionlocal: --functionLocalOffset; break;
        case formalarg: --formalArgOffset; break;
        default: assert(0);
    }
}


string convert_enum[] =
{
    stringify( GLOBAL ),
    stringify( LOCALVAR ),
    stringify( USERFUNCTION ),
    stringify( LIB_FUNCTION ),
    stringify( FORMAL )
};

string convert_enum2[] =
{
    stringify(assign),
    stringify(add),
    stringify(sub), 
    stringify(mul),
    stringify(division), 
    stringify(mod),
    stringify(uminus), 
    stringify(and_op), 
    stringify(or_op), 
    stringify(not_op), 
    stringify(if_eq), 
    stringify(if_noteq),
    stringify(if_lesseq), 
    stringify(if_greatereq), 
    stringify(if_less),
    stringify(if_greater), 
    stringify(call), 
    stringify(param), 
    stringify(ret), 
    stringify(getretval),
    stringify(funcstart), 
    stringify(funcend), 
    stringify(tablecreate),
    stringify(tablegetelem), 
    stringify(tablesetelem),
    stringify(jump)
};

void SymbolTableEntry::hide() {this->active = 0;}

void SymbolTableEntry::insertArg(SymbolTableEntry* arg) { 
    list_arg.push_back(arg);
}

bool SymbolTable::isLibFunct(string name){
    if(name == "print" || name == "input"
       || name == "objectmemberkeys" || name == "objecttotalmembers"
       || name == "objectcopy" || name == "totalarguments"
       || name == "arguments" || name == "typeof"
       || name == "strtonum" || name == "sqrt" || name == "cos"
       || name == "sin") return true;

    else return false;
} 

SymbolTableEntry::SymbolTableEntry(string name, Symbol type, symbol_t type_t, unsigned int scope, unsigned int line, bool active) {
    this->name = name;
    this->type = type;
    this->scope = scope;
    this->line = line;
    this->active = active;
    this->type_t = type_t;
    this->funcAddr = 0;
    this->localstotal = 0;
    if (type == USERFUNCTION || type  == LIB_FUNCTION) { //dont know if right
        this->offset = 0;
        
    } else {
        this->offset = currscopeoffset();
        this->space = currscopespace();
        incurrscopeoffset();
    }
    
    //incurrscopeoffset();

}

void SymbolTable::insertLibFunct() {
    this->insert("print",LIB_FUNCTION,libraryfunc_s,0,0);
    this->insert("input",LIB_FUNCTION,libraryfunc_s,0,0);
    this->insert("objectmemberkeys",LIB_FUNCTION,libraryfunc_s,0,0);
    this->insert("objecttotalmembers",LIB_FUNCTION,libraryfunc_s,0,0);
    this->insert("objectcopy",LIB_FUNCTION,libraryfunc_s,0,0);
    this->insert("totalarguments",LIB_FUNCTION,libraryfunc_s,0,0);
    this->insert("argument",LIB_FUNCTION,libraryfunc_s,0,0);
    this->insert("typeof",LIB_FUNCTION,libraryfunc_s,0,0);
    this->insert("strtonum",LIB_FUNCTION,libraryfunc_s,0,0);
    this->insert("sqrt",LIB_FUNCTION,libraryfunc_s,0,0);
    this->insert("cos",LIB_FUNCTION,libraryfunc_s,0,0);
    this->insert("sin",LIB_FUNCTION,libraryfunc_s,0,0);
}

SymbolTable::SymbolTable() {
    insertLibFunct();
}

/* ONLY TO INSERT LIBRARY FUNCTIONS */
void SymbolTable::insert(string name, Symbol type, symbol_t type_t, unsigned int scope, unsigned int line){
    SymbolTableEntry *tmp= new SymbolTableEntry();

    tmp->name=name;
    tmp->type=type;
    tmp->scope=scope;
    tmp->line=line;
    tmp->active=true;
    tmp->type_t = type_t;
    tmp->funcAddr = 0;
    tmp->localstotal = 0;
    if (type == USERFUNCTION || type == LIB_FUNCTION) {
        tmp->offset = 0;
    } else {
        tmp->offset = currscopeoffset();
        tmp->space = currscopespace();
        incurrscopeoffset();
    }
    //tmp->space = currscopespace();
    //incurrscopeoffset();

    scope_table[scope].push_back(tmp);
    auto tmp1 = hash_table.insert(hash_table.end(), pair<string, SymbolTableEntry *>(name, tmp));
}

void SymbolTable::insert(SymbolTableEntry* var){
    if( lookUp(var) ){
        scope_table[var->scope].push_back(var);
        auto tmp1 = hash_table.insert(hash_table.end(), pair<string, SymbolTableEntry *>(var->name, var));
    }
}

bool SymbolTable::lookUp(SymbolTableEntry* key){
    switch (key->type){
    case GLOBAL:
                if(lookUp(key->name, 0) == NULL)
                    return true;
                else
                    return false;
                break;
    
    case LOCALVAR: 
                if(lookUp(key->name, key->scope) == NULL)
                    return true;
                else 
                    return false;
                break;

    case USERFUNCTION: 
                if (isLibFunct(key->name)) {
                    symbolTable->errors.push_back("ERROR in line "+to_string( key->line )+": "+key->name+" collision with library function");
                    return false;
                }

                if(lookUp(key->name, key->scope) != NULL){
                    symbolTable->errors.push_back("ERROR in line "+to_string( key->line )+": "+key->name+" already exist as variable/function");
                    return false;
                }
                else
                    return true;
                break;

    case FORMAL: 
                if (isLibFunct(key->name) ){
                    symbolTable->errors.push_back("ERROR in line "+to_string( key->line )+": "+key->name+" formal argument collision with library function");
                    return false;
                }

                if(lookUp(key->name, key->scope) != NULL){
                    symbolTable->errors.push_back("ERROR in line "+to_string( key->line )+": "+key->name+" formal argument already exist");
                    return false;
                }
                else {
                    return true;
                }
                break;

    default:
        break;
    }
    return false;
}

SymbolTableEntry* SymbolTable::lookUp(string name, int scope) {
    vector<SymbolTableEntry*> tmp;
    for(auto n : scope_table){
        if(n.first == scope) {tmp=n.second; break;}
    }
    for(int i=0; i<tmp.size(); i++){
        if(tmp.at(i)->name == name && tmp.at(i)->active) return tmp.at(i);
    }

    return NULL;
}

SymbolTableEntry* SymbolTable::lookEverywhere(string key, int currScope){
    for(int i=currScope; i>=0; i--){
        for(auto tmp : hash_table){
            if(tmp.first == key && tmp.second->scope == i && tmp.second->active)
                return tmp.second;
        }
    }
    return NULL;
}

void SymbolTable::hide(int scope) {
    for(auto n : scope_table){
        if(n.first == scope){
            for(int i=0; i<n.second.size(); i++)
                n.second.at(i)->hide();
        }
    }
}

void SymbolTable::displayHash(){
    cout<<endl;
    cout<<"\033[1;31m"<<"**********************          ERRORS          **********************"<<endl;
    for(int i=0; i<errors.size(); i++) {
        cerr<<errors.at(i)<<endl;
    }
    cout<<endl;

    for( const auto& n : scope_table){
        cout<<"\033[1;35m"<<"**********************\t\tSCOPE "<<n.first<<"\t\t**********************"<<"\033[0m"<<endl;
        for (int i = 0; i < n.second.size(); i++) {
            cout<<"\""<<n.second.at(i)->name 
            << "\"\t\t["<<convert_enum[n.second.at(i)->type] 
            << "]\t\t(line "<<n.second.at(i)->offset //->line
            <<")\t(scope "<< n.first<<")"<<endl;
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<"quad#\topcode  \t\tresult\t\targ1\t\targ2\t\tlabel"<<endl;
    cout<<"--------------------------------------------------------------------------------------"<<endl;
    int i=0;
    for(i=0; i<quads.size(); i++){
        cout<<i+1<<":\t"<<convert_enum2[quads.at(i).op];
        for (int j = (convert_enum2[quads.at(i).op]).size(); j < 24; j++) cout <<" ";
       
        if (quads.at(i).result != NULL) {
            if (quads.at(i).result->sym != NULL && quads.at(i).result->sym->name != "") cout << quads.at(i).result->sym->name;
            else {
                switch (quads.at(i).result->type) {
                    case constnum_e: cout << quads.at(i).result->numConst; break;
                    case constbool_e: cout << boolalpha <<"\'"<<quads.at(i).result->boolConst<<"\'"; break;
                    case conststring_e: cout << quads.at(i).result->strConst; break;
                    case nil_e: cout << "nil"; break;
                    default: cout << quads.at(i).result->sym->name;
                }
            }
        } else { }
        cout<<"\t\t";
        
        if(quads.at(i).arg1 != NULL) {

            if (quads.at(i).arg1->sym != NULL && quads.at(i).arg1->sym->name != "") cout<<quads.at(i).arg1->sym->name;
            else {
                switch (quads.at(i).arg1->type) {
                case constnum_e: cout << quads.at(i).arg1->numConst; break;
                case constbool_e: cout << boolalpha <<"\'"<<quads.at(i).arg1->boolConst<<"\'"; break;
                case conststring_e: cout << quads.at(i).arg1->strConst; break;
                case nil_e: cout << "nil"; break;
                default: cout << quads.at(i).arg1->sym->name;
                }
            }
        } else { }
        cout<<"\t\t";
        
        if (quads.at(i).arg2 != NULL) {
            if (quads.at(i).arg2->sym != NULL && quads.at(i).arg2->sym->name != "") cout<<quads.at(i).arg2->sym->name;
            else {
                switch(quads.at(i).arg2->type){
                case constnum_e: cout<<quads.at(i).arg2->numConst; break;
                case constbool_e: cout<<boolalpha<<"\'"<<quads.at(i).arg2->boolConst<<"\'"; break;
                case conststring_e: cout<<quads.at(i).arg2->strConst; break;
                case nil_e: cout << "nil"; break;
                default: cout<<quads.at(i).arg2->sym->name;
                }
            }
        } else { }

        cout<<"\t\t"<<quads.at(i).label<<endl;
    }

    cout<<"--------------------------------------------------------------------------------------"<<endl;
    cout<<endl;
}