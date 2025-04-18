#ifndef TARGETCODE_HEADER_H
#define TARGETCODE_HEADER_H

/* 
    HY340 Languages and Compilers              Alpha Compiler Target Code Generation

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

#include <iostream>
#include <vector>
#include "expr.h"
#include "SymbolTable.h"
#include "quad.h"

using namespace std;

enum vmarg_t{
    label_a=0,
    global_a=1,
    formal_a=2,
    local_a=3,
    number_a=4,
    string_a=5,
    bool_a=6,
    nil_a=7,
    userfunc_a=8,
    libfunc_a=9,
    retval_a=10,
    empty_a=11
};

enum vmopcode {
    assign_v,       add_v,          sub_v,
    mul_v,          div_v,          mod_v,
    uminus_v,       and_v,          or_v,
    not_v,          jeq_v,          jne_v,
    jle_v,          jge_v,          jlt_v,
    jgt_v,          call_v,         pusharg_v,
    funcenter_v,    funcexit_v,     newtable_v,
    tablegetelem_v, tablesetelem_v, nop_v, jump_v
};

enum avm_memcell_t {
    number_m = 0,
    string_m = 1,
    bool_m = 2,
    table_m = 3,
    userfunc_m = 4,
    libfunc_m = 5,
    nil_m = 6,
    undef_m = 7
};

class incomplete_jump {
    public:
    unsigned instrNo;
    unsigned iaddress;
    //incomplete_jump* next;
};

class vmarg{
    public:
    vmarg_t type = empty_a;
    unsigned val;
};

class instruction {
    public:
    vmopcode opcode;
    vmarg result;
    vmarg arg1;
    vmarg arg2;
    unsigned srcLine;
};




void emit_instruction(instruction * t);
void reset_operand(vmarg* arg);
int currprocessedquad(quad* quad);
unsigned nextinstructionlabel();
unsigned consts_newstring (string s);
unsigned consts_newnumber (double n);
unsigned libfuncs_newused (string s);
unsigned userfuncs_newfunc(SymbolTableEntry* sym);

void make_operand (expr* e, vmarg* arg);
void make_numberoperand(vmarg* arg, double val);
void make_booloperand(vmarg* arg, bool val);
void make_retvaloperand(vmarg* arg);

void generate(vmopcode op, quad* quad);
void generate_ADD(quad* quad);
void generate_SUB(quad* quad);
void generate_MUL(quad* quad);
void generate_DIV(quad* quad);
void generate_MOD(quad* quad);
void generate_NEWTABLE(quad* quad);
void generate_TABLEGETELEM(quad* quad);
void generate_TABLESETELEM(quad* quad);
void generate_ASSIGN(quad* quad);
void generate_NOP(quad* quad);

void generate_relational(vmopcode op, quad* quad);
void generate_JUMP(quad* quad);
void generate_EQ(quad* quad);
void generate_NOTEQ(quad* quad);
void generate_GREATER(quad* quad);
void generate_GREATEREQ(quad* quad);
void generate_LESS(quad* quad);
void generate_LESSEQ(quad* quad);
void generate_NOT(quad* quad);
void generate_OR(quad* quad);
void generate_AND(quad* quad);
void generate_PARAM(quad* quad);
void generate_CALL(quad* quad);
void generate_GETRETVAL(quad* quad);
void generate_FUNCSTART(quad* quad);
void generate_RETURN(quad* quad);

void add_incomplete_jump (unsigned instrNo, unsigned iaddress);
void patch_incomplete_jumps();

void generate_targetcode(void);
void findConsts();
void printConstArrays(ofstream& MyFile);
void printArgument(ofstream& MyFile,vmarg arg);
void printInstructions();
void generateBinaryFile();
#endif