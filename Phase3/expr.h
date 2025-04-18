#ifndef EXPR_HEADER_H
#define EXPR_HEADER_H

#include <iostream>
#include <cstring> 
#include "SymbolTable.h"
#include "quad.h"
using namespace std;

enum expr_t {
    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,

    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,

    constnum_e,
    constbool_e,
    conststring_e,

    nil_e
};

class expr {
    public:
    expr_t      type;
    SymbolTableEntry*   sym;
    expr*       index;
    double      numConst;
    string      strConst;
    bool        boolConst;
    expr*       next = NULL;
    int         truelist;
    int         falselist;
    bool        evaluated = false; //if the expression has gone throught the function shortCircuitEval() or not;
};

class forprefix {
    public:
    int test;
    int enter;
};

expr* lvalue_expr(SymbolTableEntry* sym);
expr* member_item(expr* lv, string name);
expr* newexpr(expr_t t);
expr* newexpr_conststring(string s);
expr* newexpr_constnum(double i);
expr* emit_iftableitem(expr* e);
expr* make_call (expr* lv, expr* reversed_elist);
bool checkarithmetic_type(expr* expr1, expr* expr2);
#endif