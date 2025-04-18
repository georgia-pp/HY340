#include <iostream>
#include "expr.h"


expr* lvalue_expr(SymbolTableEntry* sym){
   // assert(sym);
    expr* e = new expr();
    memset(e, 0, sizeof(expr)); 
    if (sym != NULL) {
    e->next = NULL;
    e->sym = sym;

    switch(sym->type_t){
        case var_s:         e->type = var_e; break;
        case programfunc_s: e->type = programfunc_e; break;
        case libraryfunc_s: e->type = libraryfunc_e; break;
        default: assert(0);
    }
    }
    return e;
}

expr* member_item(expr* lv, string name){
    lv = emit_iftableitem(lv);
    expr* ti = newexpr(tableitem_e);
    ti->sym = lv->sym;
    ti->index = newexpr_conststring('\"'+name+'\"');
    return ti;
}


expr*  newexpr(expr_t t){
    expr* e = new expr();
    memset(e, 0, sizeof(expr));
    e->type = t;
    return e;
}

expr*  newexpr_conststring(string s){
    expr* e = newexpr(conststring_e);
    e->strConst = s;
    return e;
}

expr* newexpr_constnum(double i) {
    expr* e = newexpr(constnum_e);
    e->numConst = i;
    return e;
}

expr*  emit_iftableitem(expr* e){
    if(e->type != tableitem_e)
        return e;
    else{
        expr* result = newexpr(var_e); //dont know if i want to reuse temp var here
        result->sym = newtemp();
        emit(tablegetelem, e, e->index, result,0,0);
        return result;
    }
}

expr* make_call (expr* lv, expr* reversed_elist) {
    expr* func = emit_iftableitem(lv);
    while (reversed_elist) {
        emit(param, reversed_elist, NULL, NULL,0,yylineno);
        reversed_elist = reversed_elist->next;
    }
    emit(call, func,NULL, NULL,0,yylineno);
    expr* result = newexpr(var_e);
    result->sym = newtemp();
    emit(getretval, NULL, NULL, result,0,yylineno);
    return result;
}

bool checkarithmetic_type(expr* expr1, expr* expr2){
    assert(expr1 && expr2);
    if((expr1->type != programfunc_e && expr1->type != libraryfunc_e && expr1->type != boolexpr_e && expr1->type != newtable_e && expr1->type != constbool_e && expr1->type != conststring_e && expr1->type != nil_e )
        && (expr2->type != programfunc_e && expr2->type != libraryfunc_e && expr2->type != boolexpr_e && expr2->type != newtable_e && expr2->type != constbool_e && expr2->type != conststring_e && expr2->type != nil_e ))
        return true;
    else 
        return false;
}