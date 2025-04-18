#include "avmcpu.h"

/* 
    HY340 Languages and Compilers              Alpha Compiler Virtual Machine

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

bool executionFinished = false;
unsigned pc = 0;
unsigned currLine = 0;

extern execute_func_t executeFuncs[];
extern memclear_func_t memclearFuncs[];
extern cmp_func comparisonFuncs[];
extern string typeStrings[];
extern avm_memcell ax, bx, cx;
extern avm_memcell retval;
extern unsigned top, topsp;
extern unsigned int totalActuals;
extern avm_memcell stack[AVM_STACKSIZE];
extern vector<avminstr*> avm_code;
extern string convert_vmopcodeenum[];
extern string convert_memcelltype[];
extern arithmetic_func_t arithmeticFuncs[];
extern void avm_error(string str);
extern void avm_warning(string str);

void execute_cycle(void) {
    if (executionFinished) {
        return;
    }
    else if (pc == AVM_ENDING_PC) {
        executionFinished = 1;
        return;
    } else {
        assert(pc < AVM_ENDING_PC);
        avminstr* instr = avm_code.at(pc);
        assert(instr->opcode >= 0 && instr->opcode <= AVM_MAX_INSTRUCTIONS);
        
        if (instr->srcLine) currLine = instr->srcLine;
        unsigned oldPC = pc;
        //cout<<" OPCODE: "<<convert_vmopcodeenum[instr->opcode]<<endl;
        (*executeFuncs[instr->opcode])(instr);
        if (pc == oldPC) ++pc;
    }
    
}

void execute_assign (avminstr* instr){
    avm_memcell* lv = avm_translate_operand(instr->result,(avm_memcell*) 0);
    avm_memcell* rv = avm_translate_operand(instr->arg1, &ax);

    assert(lv && (&stack[AVM_STACKSIZE-1] >= lv && lv > &stack[top] || lv ==&retval));
    assert(rv);
    avm_assign(lv,rv);
}

void execute_call(avminstr* instr){
    avm_memcell* func = avm_translate_operand(instr->arg1,&ax);
    assert(func);
    switch(func->type){
        case userfunc_m:{
            avm_callsaveenvironment();
            pc= func->funcVal;
            assert(pc< AVM_ENDING_PC);
            assert(avm_code[pc]->opcode ==funcenter_v);
            break;
        }
        case string_m: avm_calllibfunc(func->strVal); break;
        case libfunc_m: avm_calllibfunc(func->libfuncVal); break;
        case table_m: avm_call_functor(func->tableVal); break;
        default:{
            char* s = avm_tostring(func);
            string str = s;
            avm_error("call: can not bind \'"+str+"\' to function! line: "+to_string(instr->srcLine));
            free(s);
            executionFinished =true;
        }
    }
}

void execute_pusharg (avminstr* instr){
    avm_memcell* arg = avm_translate_operand(instr->arg1, &ax);
    assert(arg);

    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();

}

void execute_newtable (avminstr* instr){
    avm_memcell* lv = avm_translate_operand(instr->result, (avm_memcell*)0);
    assert(lv && (&stack[AVM_STACKSIZE-1] >= lv && lv > &stack[top] || lv ==&retval));

    avm_memcellclear(lv);

    lv->type = table_m;
    lv->tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->tableVal);
}

void execute_tablegetelem (avminstr* instr){
    avm_memcell* lv = avm_translate_operand(instr->result, (avm_memcell*)0);
    avm_memcell* t = avm_translate_operand(instr->arg1, (avm_memcell*)0);
    avm_memcell* i = avm_translate_operand(instr->arg2, &ax);

    assert(lv && (&stack[AVM_STACKSIZE-1] >= lv && lv > &stack[top] || lv ==&retval));
    assert(t && (&stack[AVM_STACKSIZE-1] >= t && lv > &stack[top]));
    assert(i);

    avm_memcellclear(lv);
    lv->type = nil_m;
    if (t->type != table_m) {
        avm_error("illegal use of type "+convert_memcelltype[t->type]+" as table! line: "+to_string(instr->srcLine));
    }
    else {
        avm_memcell* content = avm_tablegetelem(t->tableVal, i);
        if(content) avm_assign(lv,content);
        else {
            char* ts = avm_tostring(t);
            char* is = avm_tostring(i);
            string tss = ts;
            string iss = is;
            avm_warning(tss+"["+iss+"] not found!");
            free(ts);
            free(is);
        }
    }
}

void execute_tablesetelem(avminstr* instr){
    avm_memcell* t = avm_translate_operand(instr->result, (avm_memcell*) 0);
    avm_memcell* i = avm_translate_operand(instr->arg1, &ax);
    avm_memcell* c = avm_translate_operand(instr->arg2, &bx);

    assert(t && &stack[AVM_STACKSIZE-1] >= t && t > &stack[top]);
    assert(i && c);

    if(t->type != table_m)
        avm_error("illegal use of type "+typeStrings[t->type]+" as table!, line: "+to_string(instr->srcLine));
    else {
        avm_tablesetelem(t->tableVal, i, c);
    }
}


void execute_funcenter(avminstr* instr){
    avm_memcell* func = avm_translate_operand(instr->result, &ax);
    assert(func);
    assert(pc == func->funcVal);
    totalActuals=0;
    userfunc* functInfo = avm_getfuncinfo(pc);
    topsp =top;
    top= top - functInfo->localSize;
}

void execute_funcexit(avminstr* unused){
    unsigned oldTop = top;
    top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    while(++oldTop <= top) avm_memcellclear(&stack[oldTop]);
}

void execute_arithmetic(avminstr* instr){
    avm_memcell* lv= avm_translate_operand(instr->result,(avm_memcell*)0 );
    avm_memcell* rv1= avm_translate_operand(instr->arg1,&ax);
    avm_memcell* rv2= avm_translate_operand(instr->arg2,&bx );
    
    assert(lv && (&stack[AVM_STACKSIZE-1]>= lv && lv > &stack[top] || lv==&retval));
    assert(rv1 && rv2);
    if(rv1->type != number_m || rv2->type != number_m){
        avm_error("not a number in arithmetic! line: "+to_string(instr->srcLine));
        executionFinished=1;
    }
    else{
        arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
        avm_memcellclear(lv);
        lv->type = number_m;
        lv->numVal = (*op)(rv1->numVal,rv2->numVal);
    }
}

void execute_comparison(avminstr* instr) {
    
    avm_memcell* rv1= avm_translate_operand(instr->arg1,&ax);
    avm_memcell* rv2= avm_translate_operand(instr->arg2,&bx );

    assert(rv1 && rv2);
    if(rv1->type != number_m || rv2->type != number_m){
        avm_error("not a number in comparison! line: "+instr->srcLine);
        executionFinished=1;
    }
    else{
        cmp_func op = comparisonFuncs[instr->opcode - jle_v];
        bool result = (*op)(rv1->numVal, rv2->numVal);
        if(!executionFinished && result) pc = instr->result->val;
       
    }
}

void execute_jeq(avminstr* instr){
    assert(instr->result->type == label_a);

    avm_memcell* rv1 = avm_translate_operand(instr->arg1,&ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2,&bx);
    bool result = false;
    if(rv1->type == undef_m || rv2->type == undef_m)
        avm_error("\'undef\' involved in equality! line: "+instr->srcLine);
    else if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) == avm_tobool(rv2));
    else if (rv1->type == nil_m || rv2->type == nil_m)
        result = rv1->type ==nil_m &&  rv2->type ==nil_m;
    else if (rv1->type != rv2->type) {
        string s1 = typeStrings[rv1->type];
        string s2 = typeStrings[rv2->type];

        avm_error(s1+" == "+s2+" is illegal, line: "+to_string(instr->srcLine));
    }
    else if (rv1->type == rv2->type){
        switch(rv1->type) {
            case number_m: {
                //if (rv1->numVal == rv2->numVal) result = true;
                //else result = false;
                result = rv1->numVal == rv2->numVal;
                break;
            }
            case string_m: {
                result = strcmp(rv1->strVal, rv2->strVal) == 0;
                break;
            }
            case bool_m: {
                result = (avm_tobool(rv1) == avm_tobool(rv2));
                break;
            }
            case table_m: {
                result = (avm_tobool(rv1) == avm_tobool(rv2));
                break;
            }
            case userfunc_m: {
                result = rv1->funcVal == rv2->funcVal;
                break;
            }
            case libfunc_m: {
                result = strcmp(rv1->libfuncVal,rv2->libfuncVal) == 0;
                break;
            }
            default: {assert(0); break;}
        }
    } else assert(0);

    if(!executionFinished && result) pc= instr->result->val;
}

void execute_jne(avminstr* instr){
    assert(instr->result->type == label_a);
    avm_memcell* rv1 = avm_translate_operand(instr->arg1,&ax);
    avm_memcell* rv2 = avm_translate_operand(instr->arg2,&bx);
    bool result = false;
    if(rv1->type == undef_m || rv2->type == undef_m)
        avm_error("\'undef\' involved in equality! line: "+to_string(instr->srcLine));
    else if (rv1->type == bool_m || rv2->type == bool_m)
        result = (avm_tobool(rv1) != avm_tobool(rv2));
    else if (rv1->type == nil_m || rv2->type == nil_m)
        result = (rv1->type ==nil_m &&  rv2->type !=nil_m) || (rv1->type !=nil_m &&  rv2->type ==nil_m);
    else if (rv1->type != rv2->type) {
        string s1 = typeStrings[rv1->type];
        string s2 = typeStrings[rv2->type];

        avm_error(s1+" != "+s2+" is illegal, line: "+to_string(instr->srcLine));
    }
    else if (rv1->type == rv2->type){
        switch(rv1->type) {
            case number_m: {result = rv1->numVal != rv2->numVal; break;}
            case string_m: {result = strcmp(rv1->strVal, rv2->strVal) != 0; break;}
            case bool_m: {result = (avm_tobool(rv1) != avm_tobool(rv2)); break;}
            case table_m: {result = (avm_tobool(rv1) != avm_tobool(rv2)); break;}
            case userfunc_m: {result = rv1->funcVal != rv2->funcVal; break;}
            case libfunc_m: {result = strcmp(rv1->libfuncVal,rv2->libfuncVal) != 0; break;}
        }
    } else assert(0);

    if(!executionFinished && result) pc= instr->result->val;
}

void execute_jump (avminstr* instr){
    assert(instr->result->type == label_a);
    if(!executionFinished) pc = instr->result->val;
}
/*void execute_jle (avminstr* instr){}
void execute_jge (avminstr* instr){}
void execute_jlt (avminstr* instr){}
void execute_jgt (avminstr* instr){}*/

/*void execute_add (avminstr*) {}
void execute_sub (avminstr*) {}
void execute_mul (avminstr*){}
void execute_div (avminstr*){}
void execute_mod (avminstr*){}*/
void execute_uminus (avminstr*){ }

void execute_and (avminstr*){}
void execute_or (avminstr*){}
void execute_not (avminstr*){}
void execute_nop (avminstr*){}