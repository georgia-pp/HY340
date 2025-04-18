#include "targetcode.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

/* 
    HY340 Languages and Compilers              Alpha Compiler Target Code Generation

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

vector<instruction*> instructions;
vector<incomplete_jump*> incomplete_jumps;
vector<string> constStringArr;
vector<double> constDoubleArr;
vector<string> constLibFubcArr;
vector<SymbolTableEntry*> constUserFuncArr;
vector<SymbolTableEntry*> funcstack;
int CURRENT_FUNCTION = -1;
#define totalStringConsts (constStringArr.size())
#define totalNumConsts (constDoubleArr.size())
#define totalUserFuncs (constUserFuncArr.size())
#define totalNamedLibfuncs (constLibFubcArr.size())
#define NEXT_INSTRUCTION (instructions.size())
#define INCOMPLETE_JUMPS_TOTAL (incomplete_jumps.size())

#define MAGICNUMBER 340200501U;

extern vector<quad> quads;
extern vector<quad*> quadptrs;
extern SymbolTable* symbolTable;

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

unsigned consts_newstring(string s) {
    for (size_t i = 0; i < constStringArr.size(); i++)
    {
        if (constStringArr.at(i) == s) return i;
    }
    assert(0);//
}

unsigned consts_newnumber(double d) {
    for (size_t i = 0; i < constDoubleArr.size(); i++)
    {
        if (constDoubleArr.at(i) == d) return i;
    }
    assert(0);//
}

unsigned libfuncs_newused(string s) {
    for (size_t i = 0; i < constLibFubcArr.size(); i++)
    {
        if (constLibFubcArr.at(i) == s) return i;
    }
    assert(0);//
}

unsigned userfuncs_newfunc(SymbolTableEntry* sym) {
    for (size_t i = 0; i < constUserFuncArr.size(); i++)
    {
        if (constUserFuncArr.at(i) == sym) return i;
        //if (constUserFuncArr.at(i)->name == sym->name) return i; //added for bug where a function in a function couldnt be called
    }
    assert(0);//
}

void add_incomplete_jump (unsigned instrNo, unsigned iaddress) {
    incomplete_jump* incmp_jump = new incomplete_jump();
    incmp_jump->instrNo = instrNo;
    incmp_jump->iaddress = iaddress;
    incomplete_jumps.push_back(incmp_jump);
}

void patch_incomplete_jumps() {
    for (int i = 0; i < incomplete_jumps.size(); i++) 
    {
        incomplete_jump* x = incomplete_jumps.at(i);
        if (x->iaddress == quads.size()) {
            
            instructions[x->instrNo]->result.type = label_a;
            instructions[x->instrNo]->result.val = quads.size();
        }
        else {
            
            instructions[x->instrNo]->result.type = label_a;
            instructions[x->instrNo]->result.val = quads[x->iaddress].taddress;
        }   
    }  
}

void emit_instruction(instruction * t){
    instruction* tmp = new instruction();
    tmp->opcode = t->opcode;
    tmp->result = t->result;
    tmp->arg1 = t->arg1;
    tmp->arg2 = t->arg2;
    tmp->srcLine = t->srcLine;
    instructions.push_back(tmp);
}

void reset_operand(vmarg* arg) {
    arg->type = empty_a;
}

int currprocessedquad(quad* quadd) {  
    int i = 0;
    for (i = 0; i<quads.size(); i++) {
        if (&quads[i] == quadd) return i;
    }
    assert(0); //quad not found
}


unsigned nextinstructionlabel() {
    return NEXT_INSTRUCTION;
}

void make_operand (expr* e, vmarg* arg){
    if (e != NULL) {
        switch(e->type){
            case var_e: {
               assert(e->sym);
                arg->val = e->sym->offset;
                switch (e->sym->space){
                    case programvar: arg->type = global_a; break;
                    case functionlocal: arg->type = local_a; break;
                    case formalarg: arg->type = formal_a; break;
                    default: assert(0);
                }
                break;
            }

            case assignexpr_e: {
                assert(e->sym);
                arg->val = e->sym->offset;
                switch (e->sym->space){
                    case programvar: arg->type = global_a; break;
                    case functionlocal: arg->type = local_a; break;
                    case formalarg: arg->type = formal_a; break;
                    default: assert(0);
                }
                break;
                
            }

            case tableitem_e: {
                assert(e->sym);
                arg->val = e->sym->offset;
                switch (e->sym->space){
                    case programvar: arg->type = global_a; break;
                    case functionlocal: arg->type = local_a; break;
                    case formalarg: arg->type = formal_a; break;
                    default: assert(0);
                }
                break;
            }
            case arithexpr_e: {
                assert(e->sym);
                arg->val = e->sym->offset;
                switch (e->sym->space){
                    case programvar: arg->type = global_a; break;
                    case functionlocal: arg->type = local_a; break;
                    case formalarg: arg->type = formal_a; break;
                    default: assert(0);
                }
                break;
            }
            case boolexpr_e: {
                assert(e->sym);
                arg->val = e->sym->offset;
                switch (e->sym->space){
                    case programvar: arg->type = global_a; break;
                    case functionlocal: arg->type = local_a; break;
                    case formalarg: arg->type = formal_a; break;
                    default: assert(0);
                }
                break;
            }
            case newtable_e: {
                assert(e->sym);
                arg->val = e->sym->offset;
                switch (e->sym->space){
                    case programvar: arg->type = global_a; break;
                    case functionlocal: arg->type = local_a; break;
                    case formalarg: arg->type = formal_a; break;
                    default: assert(0);
                }
                break;
            }
            case constbool_e: {
                arg->val = e->boolConst;
                arg->type = bool_a; break;
            }
            case conststring_e: {
                arg->val = consts_newstring(e->strConst);
                arg->type = string_a; break;
            }

            case constnum_e: {
                if (e->sym != NULL && e->sym->name != "") { //because instead of the name of the temp that hold the p.x 2+4 it would show 6
                    arg->val = e->sym->offset;
                    switch (e->sym->space){
                    case programvar: arg->type = global_a; break;
                    case functionlocal: arg->type = local_a; break;
                    case formalarg: arg->type = formal_a; break;
                    default: assert(0);
                    }
                } else {
                    arg->val = consts_newnumber(e->numConst);
                    arg->type = number_a; 
                }
                break;
            }

            case nil_e: arg->type = nil_a; break;

            /* Functions */
            case programfunc_e: {
                arg->type = userfunc_a;
                //arg->val = e->sym->funcAddr;
                arg->val = userfuncs_newfunc(e->sym);
                break;
            }

            case libraryfunc_e: {
                arg->type = libfunc_a;
                arg->val = libfuncs_newused(e->sym->name);
                break;
            }

            default: assert(0);
        }
    }
}

void make_numberoperand(vmarg* arg, double val){
    arg->val = consts_newnumber(val);
    arg->type = number_a;
}

void make_booloperand(vmarg* arg, bool val){
    arg->val=val;
    arg->type= bool_a;
}

void make_retvaloperand(vmarg* arg){
    arg->type = retval_a;
}

void generate(vmopcode op, quad* quad){
    instruction* t = new instruction();
    t->opcode = op;
    t->srcLine = quad->line;
    
    make_operand(quad->arg1, &t->arg1);
    make_operand(quad->arg2, &t->arg2);
    make_operand(quad->result, &t->result);
    quad->taddress = nextinstructionlabel();
    emit_instruction(t);
}

void generate_ADD(quad* quad){ generate(add_v, quad);}
void generate_SUB(quad* quad){ generate(sub_v, quad);}
void generate_MUL(quad* quad){ generate(mul_v, quad);}
void generate_DIV(quad* quad){ generate(div_v, quad);}
void generate_MOD(quad* quad){ generate(mod_v, quad);}
void generate_NEWTABLE(quad* quad){ generate(newtable_v, quad);}
void generate_TABLEGETELEM(quad* quad){ generate(tablegetelem_v, quad);}
void generate_TABLESETELEM(quad* quad){ generate(tablesetelem_v, quad);}
void generate_ASSIGN(quad* quad){ generate(assign_v, quad);}
void generate_NOP(quad* quad){ instruction* t; t->opcode=nop_v; emit_instruction(t);}
void generate_UMINUS(quad* quad) {
    quad->arg2 = newexpr(constnum_e);
    quad->arg2->numConst = -1;
    generate_MUL(quad);
    /*instruction* t = new instruction();
    t->opcode = uminus_v;
    t->srcLine = quad->line;
    make_operand(quad->arg1, &t->arg1);
    make_operand(quad->result, &t->result);
    quad->taddress = nextinstructionlabel();
    emit_instruction(t);*/
    //quad->arg2 = newexpr_constnum(-1); 
    //generate(mul_v,quad);
}


void generate_relational(vmopcode op, quad* quad){
    instruction* t = new instruction();
    t->opcode = op;
    t->srcLine = quad->line;
    
    make_operand(quad->arg1, &t->arg1);
    make_operand(quad->arg2, &t->arg2);

    t->result.type = label_a;
    if(quad->label-1 < currprocessedquad(quad)) {
        t->result.val = quads[quad->label-1].taddress;
    }
    else 
        add_incomplete_jump(nextinstructionlabel(), quad->label-1);
    quad->taddress = nextinstructionlabel();
    emit_instruction(t);
}
void generate_JUMP(quad* quad){ generate_relational(jump_v,quad);}
void generate_EQ(quad* quad){ generate_relational(jeq_v,quad);}
void generate_NOTEQ(quad* quad){ generate_relational(jne_v,quad);}
void generate_GREATER(quad* quad){ generate_relational(jgt_v,quad);}
void generate_GREATEREQ(quad* quad){ generate_relational(jge_v,quad);}
void generate_LESS(quad* quad){ generate_relational(jlt_v,quad);}
void generate_LESSEQ(quad* quad){ generate_relational(jle_v,quad);}

void generate_NOT(quad* quad){ 
    quad->taddress = nextinstructionlabel();
    instruction* t = new instruction();
    t->opcode = jeq_v;
    t->srcLine = quad->line;
    make_operand(quad->arg1, &t->arg1);
    make_booloperand(&t->arg2, false);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+3;
    emit_instruction(t);
    
    t->opcode = assign_v;
    make_booloperand(&t->arg1, false);
    reset_operand(&t->arg2);
    make_operand(quad->result, &t->result);
    emit_instruction(t);

    t->opcode = jump_v;
    reset_operand(&t->arg1);
    reset_operand(&t->arg2);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+2;
    emit_instruction(t);
    
    t->opcode = assign_v;
    make_booloperand(&t->arg1, true);
    reset_operand(&t->arg2);
    make_operand(quad->result, &t->result);
    emit_instruction(t);
}

void generate_OR(quad* quad){ 
    assert(0);
    quad->taddress = nextinstructionlabel();
    instruction* t = new instruction();
    t->opcode = jeq_v;
    t->srcLine = quad->line;
    make_operand(quad->arg1, &t->arg1);
    make_booloperand(&t->arg2, true);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+4;
    emit_instruction(t);

    make_operand(quad->arg2, &t->arg1);
    t->result.val = nextinstructionlabel()+3;
    emit_instruction(t);

    t->opcode = assign_v;
    make_booloperand(&t->arg1, true);
    reset_operand(&t->arg2);
    make_operand(quad->result, &t->result);
    emit_instruction(t);

    t->opcode = jump_v;
    reset_operand(&t->arg1);
    reset_operand(&t->arg2);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+2;
    emit_instruction(t);
    
    t->opcode = assign_v;
    make_booloperand(&t->arg1, true);
    reset_operand(&t->arg2);
    make_operand(quad->result, &t->result);
    emit_instruction(t);
}

void generate_AND(quad* quad){ 
    assert(0);
    quad->taddress = nextinstructionlabel();
    instruction* t = new instruction();
    t->opcode = jeq_v;
    t->srcLine = quad->line;
    make_operand(quad->arg1, &t->arg1);
    make_booloperand(&t->arg2, true);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+4;
    emit_instruction(t);

    make_operand(quad->arg2, &t->arg1);
    t->result.val = nextinstructionlabel()+3;
    emit_instruction(t);

    t->opcode = assign_v;
    make_booloperand(&t->arg1, true);
    reset_operand(&t->arg2);
    make_operand(quad->result, &t->result);
    emit_instruction(t);

    t->opcode = jump_v;
    reset_operand(&t->arg1);
    reset_operand(&t->arg2);
    t->result.type = label_a;
    t->result.val = nextinstructionlabel()+2;
    emit_instruction(t);
    
    t->opcode = assign_v;
    make_booloperand(&t->arg1, true);
    reset_operand(&t->arg2);
    make_operand(quad->result, &t->result);
    emit_instruction(t);
}

void generate_PARAM(quad* quad){
    quad->taddress = nextinstructionlabel();
    instruction* t = new instruction();
    t->opcode = pusharg_v;
    t->srcLine = quad->line;
    make_operand(quad->arg1, &t->arg1);
    emit_instruction(t);
}

void generate_CALL(quad* quad){
    quad->taddress = nextinstructionlabel();
    instruction* t = new instruction();
    t->opcode = call_v;
    t->srcLine = quad->line;

   /* for (size_t i = 0; i < constUserFuncArr.size(); i++)
    {
        if(quad->arg1->sym->name == constUserFuncArr.at(i)->name) { //added for bug where a functio inside a function could be called
            quad->arg1->type = programfunc_e;
        }
    }*/
    
    make_operand(quad->arg1, &t->arg1);
    emit_instruction(t);
}

void generate_GETRETVAL(quad* quad){
    quad->taddress = nextinstructionlabel();
    instruction* t = new instruction();

    t->opcode = assign_v;
    t->srcLine = quad->line;
    make_operand(quad->result, &t->result);
    make_retvaloperand(&t->arg1);
    emit_instruction(t);
}

void generate_FUNCSTART(quad* quad){
    SymbolTableEntry* f;
    f = quad->result->sym;
    f->funcAddr = nextinstructionlabel();
    quad->taddress = nextinstructionlabel();
    funcstack.push_back(f);

    instruction* t = new instruction();
    t->opcode = funcenter_v;
    t->srcLine = quad->line;
    make_operand(quad->result, &t->result);
    emit_instruction(t);
}

void generate_RETURN(quad* quad) {
    quad->taddress = nextinstructionlabel();
    instruction* t = new instruction();
    t->opcode = assign_v;
    t->srcLine = quad->line;
   
    make_retvaloperand(&t->result);
    make_operand(quad->result, &t->arg1);

    emit_instruction(t);

    SymbolTableEntry* f;
    f = funcstack.at(funcstack.size()-1);
}

void generate_FUNCEND(quad* quad) {
   SymbolTableEntry* f = funcstack.at(funcstack.size()-1);
    
   quad->taddress = nextinstructionlabel();
   instruction* t = new instruction();
   t->opcode = funcexit_v;
   t->srcLine = quad->line;
   make_operand(quad->result, &t->result);
   emit_instruction(t);
}

typedef void (*generator_func_t) (quad*);

generator_func_t generators[] = {
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV,
    generate_MOD,
    generate_UMINUS,
    generate_AND,
    generate_OR,
    generate_NOT,
    generate_EQ,
    generate_NOTEQ,
    generate_LESSEQ,
    generate_GREATEREQ,
    generate_LESS,
    generate_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RETURN,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_NEWTABLE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    //generate_NOP,
    generate_JUMP,
};

void generate_targetcode(void) {
    for (unsigned i = 0; i<quads.size(); i++) {
        (*generators[quads[i].op])(&quads[i]);
    }
    patch_incomplete_jumps(); 
}

void findConsts(){
    for (size_t i = 0; i < quads.size(); i++)
    {
        
        if (quads[i].arg1 != NULL) {
            switch (quads[i].arg1->type)
            {
            case conststring_e: {
                auto it0 = find(constStringArr.begin(), constStringArr.end(), quads[i].arg1->strConst);
                if (it0 == constStringArr.end()) constStringArr.push_back(quads[i].arg1->strConst);
                break;
            }
            case constnum_e: {
                if (quads.at(i).arg1->sym == NULL || quads.at(i).arg1->sym->name == "" ) {
                    auto it1 = find(constDoubleArr.begin(), constDoubleArr.end(), quads[i].arg1->numConst);
                    if (it1 == constDoubleArr.end()) constDoubleArr.push_back(quads[i].arg1->numConst);
                }
                break;
            }
            case libraryfunc_e: {
                auto it2 = find(constLibFubcArr.begin(), constLibFubcArr.end(), quads[i].arg1->sym->name);
                if (it2 == constLibFubcArr.end()) constLibFubcArr.push_back(quads[i].arg1->sym->name);
                break;
            }
            case programfunc_e: {
                auto it3 = find(constUserFuncArr.begin(), constUserFuncArr.end(), quads[i].arg1->sym);
                if (it3 == constUserFuncArr.end()) constUserFuncArr.push_back(quads[i].arg1->sym);
                break;
            }
            default:
                break;
            }
        }

        if (quads[i].arg2 != NULL) {
            switch (quads[i].arg2->type)
            {
            case conststring_e: {
                auto it4 = find(constStringArr.begin(), constStringArr.end(), quads[i].arg2->strConst);
                if (it4 == constStringArr.end()) constStringArr.push_back(quads[i].arg2->strConst);
                break;
            }
            case constnum_e: {
                if (quads.at(i).arg2->sym == NULL || quads.at(i).arg2->sym->name == "" ) {
                    auto it5 = find(constDoubleArr.begin(), constDoubleArr.end(), quads[i].arg2->numConst);
                    if (it5 == constDoubleArr.end()) constDoubleArr.push_back(quads[i].arg2->numConst);
                }
                break;
            }
            case libraryfunc_e: {
                auto it6 = find(constLibFubcArr.begin(), constLibFubcArr.end(), quads[i].arg2->sym->name);
                if (it6 == constLibFubcArr.end()) constLibFubcArr.push_back(quads[i].arg2->sym->name);
                break;
            }
            case programfunc_e: {
                auto it7 = find(constUserFuncArr.begin(), constUserFuncArr.end(), quads[i].arg2->sym);
                if (it7 == constUserFuncArr.end()) constUserFuncArr.push_back(quads[i].arg2->sym);
                break;
            }
            default:
                break;
            }
        }

        if (quads[i].result != NULL) {
            switch (quads[i].result->type) {
            case conststring_e: {
                auto it8 = find(constStringArr.begin(), constStringArr.end(), quads[i].result->strConst);
                if (it8 == constStringArr.end()) constStringArr.push_back(quads[i].result->strConst);
                break;
            }
            case constnum_e: {
                if (quads.at(i).result->sym == NULL || quads.at(i).result->sym->name == "" ) {
                    auto it9 = find(constDoubleArr.begin(), constDoubleArr.end(), quads[i].result->numConst);
                    if (it9 == constDoubleArr.end()) constDoubleArr.push_back(quads[i].result->numConst);
                }
                break;
            }
            case libraryfunc_e: {
                auto it10 = find(constLibFubcArr.begin(), constLibFubcArr.end(), quads[i].result->sym->name);
                if (it10 == constLibFubcArr.end()) constLibFubcArr.push_back(quads[i].result->sym->name);
                break; 
            }
            case programfunc_e: {
                auto it11 = find(constUserFuncArr.begin(), constUserFuncArr.end(), quads[i].result->sym);
                if (it11 == constUserFuncArr.end()) constUserFuncArr.push_back(quads[i].result->sym);
                break;
            }
            default:
                break;
            }
        }

        if (quads[i].op == uminus) {
            auto itt = find(constDoubleArr.begin(), constDoubleArr.end(), -1);
            if (itt == constDoubleArr.end()) constDoubleArr.push_back(-1);
        }
    }
    
}

void printConstArrays(ofstream& MyFile) {
    MyFile <<endl<<"-------------------------------------CONST TABLES-------------------------------------"<<endl<<endl;
    MyFile << "-----------------------CONST STRING ARRAY-----------------------"<<endl;
    for (size_t i = 0; i <constStringArr.size() ; i++)
    {
        MyFile<<i<<":  "<<constStringArr.at(i)<<endl;
    }
    MyFile << "----------------------------------------------------------------"<<endl;
    MyFile<<endl;
    
    MyFile << "-----------------------CONST NUMBER ARRAY-----------------------"<<endl;
    for (size_t i = 0; i <constDoubleArr.size() ; i++)
    {
        MyFile<<i<<":  "<<constDoubleArr.at(i)<<endl;
    }
    MyFile << "----------------------------------------------------------------"<<endl;
    MyFile<<endl;

    MyFile << "--------------------CONST USERFUNCTION ARRAY--------------------"<<endl;
    for (size_t i = 0; i <constUserFuncArr.size() ; i++)
    {
        MyFile<<i<<":  address "<<constUserFuncArr.at(i)->funcAddr<<", local size "<<constUserFuncArr.at(i)->localstotal<<", id \""<<constUserFuncArr.at(i)->name<<"\""<<endl;
    }
    MyFile << "----------------------------------------------------------------"<<endl;
    MyFile<<endl;

    MyFile << "---------------------CONST LIBFUNCTION ARRAY--------------------"<<endl;
    for (size_t i = 0; i <constLibFubcArr.size() ; i++)
    {
        MyFile<<i<<":   \""<<constLibFubcArr.at(i)<<"\""<<endl;
    }
    MyFile << "----------------------------------------------------------------"<<endl;
    MyFile<<endl;
}

void printArgument(ofstream& MyFile,vmarg arg) {
    if (arg.type != empty_a) {
        switch (arg.type)
        {
            case global_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val<<":";
                for (const auto &n : symbolTable->scope_table)
                {
                    for (int i = 0; i < n.second.size(); i++)
                    {
                        if (n.second.at(i)->offset == arg.val && n.second.at(i)->space == programvar && n.second.at(i)->type_t == var_s) MyFile<< n.second.at(i)->name;
                    }
                }
                break;
            }

            case number_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val<<":"<<constDoubleArr[arg.val];
                break;
            }

            case string_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val<<":"<<constStringArr[arg.val];
                break;
            }

            case userfunc_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val<<":"<<constUserFuncArr[arg.val]->name;
                break;
            }

            case libfunc_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val<<":"<<constLibFubcArr[arg.val];
                break;
            }

            case label_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val;//need work with patch and in general
                break;
            }

            case retval_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<")";
                break;
            }

            case formal_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val<<":"<<funcstack.at(CURRENT_FUNCTION)->list_arg.at(arg.val)->name;    
                break;
            }

            case local_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val;
                SymbolTableEntry* sym;
                sym = funcstack.at(CURRENT_FUNCTION);
                for( const auto& n : symbolTable->scope_table){
                    for (int i = 0; i < n.second.size(); i++) {
                        if ((sym->scope == n.first-1) && (n.second.at(i)->type_t == var_s) && (n.second.at(i)->space == functionlocal) && (n.second.at(i)->offset == arg.val)) {
                            MyFile<<":"<<n.second.at(i)->name;
                            break;
                        }
                    }
                }
                break;
            }

            case bool_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), ";//need work with patch and in general
                if (arg.val == 0) MyFile << "\'false\'";
                else MyFile << "\'true\'";
                break;
            }

            case nil_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), nil";//need work with patch and in general
                break;
            } 
            default:
                break;
        }
    } else {
        //MyFile <<"\t\t\t\t\t";
    }
}

void printTargetCodeArg(ofstream& MyFile,vmarg arg) {
    if (arg.type != empty_a) {
        switch (arg.type)
        {
            case global_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val;
            }

            case number_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val;
                break;
            }

            case string_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val;
                break;
            }

            case userfunc_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val;
                break;
            }

            case libfunc_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val;
                break;
            }

            case label_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val;//need work with patch and in general
                break;
            }

            case retval_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<")";
                break;
            }

            case formal_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val;    
                break;
            }

            case local_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val;
                break;
            }

            case bool_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), "<<arg.val;//need work with patch and in general
                break;
            }

            case nil_a: {
                MyFile << arg.type<<"("<<convert_vmargenum[arg.type]<<"), nil";//need work with patch and in general
                break;
            } 
            default:
                break;
        }
    } else {
        //MyFile <<"\t\t\t\t\t";
    }
}



void printInstructions() {
   /* cout<<endl;
    cout<<"\033[1;31m"<<"**********************          ERRORS          **********************"<<endl;
    for(int i=0; i<symbolTable->errors.size(); i++) {
        cerr<<symbolTable->errors.at(i)<<endl;
    }*/
    ofstream MyFile("TargetCode.txt");
    printConstArrays(MyFile);
    MyFile<<endl<<endl;
    MyFile<<"instr#\topcode  \t\tresult\t\t\t\t\targ1\t\t\t\t\targ2\t\t\t\t\tline"<<endl;
    MyFile<<"--------------------------------------------------------------------------------------"<<endl;

    int i=0;
    for(i=0; i<instructions.size(); i++){
        MyFile<<i<<":\t\t"<<convert_vmopcodeenum[instructions.at(i)->opcode];
       
        for (int j = (convert_vmopcodeenum[instructions.at(i)->opcode]).size(); j < 16; j++) {
            MyFile <<" ";
        }
      
       if (instructions.at(i)->opcode == funcexit_v) {
            //funcstack.pop_back(); //end of a function encountered
            funcstack.erase(funcstack.begin()+ CURRENT_FUNCTION);
            CURRENT_FUNCTION--;
        }
       if (instructions.at(i)->opcode == funcenter_v) CURRENT_FUNCTION++; //end of a function encountered
       
       printArgument(MyFile, instructions.at(i)->result);
       MyFile <<"\t\t";
       
       printArgument(MyFile, instructions.at(i)->arg1);
       MyFile <<"\t\t";
       
       printArgument(MyFile, instructions.at(i)->arg2);
       MyFile<<"\t\t"<<instructions.at(i)->srcLine<<endl;
       
    }

    MyFile<<"--------------------------------------------------------------------------------------"<<endl;
    MyFile<<endl;
}

void generateBinaryFile() {
    //ofstream BinFile("TargetCode.abc",ios::out | ios::binary);
    int i;
    string str;
    int tmpnum;
    ofstream BinFile("TargetCode.abc",ios::out | ios::binary);
    if(!BinFile) {
      cout << "Cannot open file!" << endl;
      exit(1);
    }
    // Magicnumber
    unsigned int magicnum= MAGICNUMBER; 
    BinFile.write((char*)&magicnum, 4);
    // totalGlobals
    unsigned int totalGlobals= symbolTable->globalCounter; 
    BinFile.write((char*)&totalGlobals, 4);
    // strings 
    tmpnum= constStringArr.size();
    BinFile.write((char*)&tmpnum, 4);
    for(i=0; i<constStringArr.size(); i++) {
        str =constStringArr.at(i);
        int size= str.size()+1;
        BinFile.write((char*)&size, 4);
        BinFile.write((char*)str.c_str(), size);
    }
    //numbers
    tmpnum= constDoubleArr.size();
    BinFile.write((char*)&tmpnum, 4);
    for(i=0; i<constDoubleArr.size(); i++) {
        double num = constDoubleArr.at(i);
        BinFile.write((char*)&num, 8);
    }
    //userfuncs
    tmpnum= constUserFuncArr.size();
    BinFile.write((char*)&tmpnum, 4);
    for(i=0; i<constUserFuncArr.size(); i++) {
        SymbolTableEntry* e = constUserFuncArr.at(i);
        int formals = e->list_arg.size();
        int locals = e->localstotal;
        int address = e->funcAddr;
        string name = e->name;
        int size= name.size()+1;
        BinFile.write((char*)&address, 4);
        BinFile.write((char*)&formals, 4);
        BinFile.write((char*)&locals, 4);
        BinFile.write((char*)&size, 4);
        BinFile.write((char*)name.c_str(), size);
    }
    //library functions
    tmpnum= constLibFubcArr.size();
    BinFile.write((char*)&tmpnum, 4);
    for(i=0; i<constLibFubcArr.size(); i++) {
        str =constLibFubcArr.at(i);
        int size= str.size()+1;
        BinFile.write((char*)&size, 4);
        BinFile.write((char*)str.c_str(), size);
    }

    tmpnum= instructions.size();
    BinFile.write((char*)&tmpnum, 4);
    for(i=0; i<instructions.size(); i++) {
        instruction* instr = instructions.at(i);
        vmarg_t type;
        unsigned val;
        int opcode = (int) instr->opcode;
        
        // Opcode
        BinFile.write((char*)&opcode, 1);
        // Result
        type = instr->result.type;
        val = instr->result.val;
        BinFile.write((char*)&type, 1);
        BinFile.write((char*)&val, 4);
        // Arg1
        type = instr->arg1.type;
        val = instr->arg1.val;
        BinFile.write((char*)&type, 1);
        BinFile.write((char*)&val, 4);
        // Arg2
        type = instr->arg2.type;
        val = instr->arg2.val;
        BinFile.write((char*)&type, 1);
        BinFile.write((char*)&val, 4);
        // srcLine
        BinFile.write((char*)&instr->srcLine, 4);
    }

    BinFile.close();
}
