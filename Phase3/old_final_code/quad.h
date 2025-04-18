#ifndef QUAD_HEADER_H
#define QUAD_HEADER_H

#include <iostream>
#include <vector>
#include <cstring> //for memcpy
#include <assert.h>
#include <fstream>
#include "expr.h"
#include "SymbolTable.h"
extern SymbolTable* symbolTable;
extern int yylineno;
extern int SCOPE;

enum iopcode{
    assign, add, sub, mul, division, mod,
    uminus, and_op, or_op, not_op, if_eq, if_noteq,
    if_lesseq, if_greatereq, if_less,
    if_greater, call, param, ret, getretval,
    funcstart, funcend, tablecreate,
    tablegetelem, tablesetelem, jump
};

class expr;

class quad {
    public:
    iopcode op;
    expr* result;
    expr* arg1;
    expr* arg2;
    unsigned label;
    unsigned line;
};


void emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line); 
unsigned int nextquad (void);
void patchlabel(unsigned quadNo, unsigned label);
void patchlist (int list, int label);
int mergelist(int l1, int l2);

void trueTest(expr* expr1);
void shortCircuitEval(expr* expr1);
void printQuads(void);
expr* newexpr_constbool (bool b);
bool check_defined(expr* expr);
expr* operator_exist_return_arg2(iopcode op, expr* expr);
//--------------Temporary Variables------------------
void resettemp();
string newtempname();
bool istempname(string s);
bool istempexpr(expr* e);
SymbolTableEntry* newtemp();

#endif