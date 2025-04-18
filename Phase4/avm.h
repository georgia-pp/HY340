#ifndef AVM_HEADER_H
#define AVM_HEADER_H

/* 
    HY340 Languages and Compilers              Alpha Compiler Virtual Machine

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <cassert>
#include <cmath>
#include "expr.h"
#include "SymbolTable.h"
#include "targetcode.h"
#include "quad.h"

using namespace std;


#define AVM_STACKSIZE 4096
#define AVM_STACKENV_SIZE 4
#define AVM_WIPEOUT(m) memset(&(m),0,sizeof(m))
#define AVM_MAX_INSTRUCTIONS (unsigned) jump_v
#define AVM_ENDING_PC avm_code.size()
#define AVM_NUMACTUALS_OFFSET +4
#define AVM_SAVEDPC_OFFSET +3
#define AVM_SAVEDTOP_OFFSET +2
#define AVM_SAVEDTOPSP_OFFSET +1
#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic
#define execute_jle execute_comparison
#define execute_jge execute_comparison
#define execute_jlt execute_comparison
#define execute_jgt execute_comparison


class avm_memcell;
class avminstr;
typedef void (*execute_func_t)(avminstr*);
typedef void (*memclear_func_t) (avm_memcell*);
typedef void (*memclear_func_t) (avm_memcell*);
typedef char* (*tostring_func_t)(avm_memcell*);
typedef void (*library_func_t) (void);
typedef double (*arithmetic_func_t)(double x,double y); 
typedef bool (*cmp_func)(double x, double y);
typedef bool (*tobool_func_t)(avm_memcell*);

class userfunc{
    public:
    unsigned address;
    unsigned formalsize;
    unsigned localSize;
    string id;
};

class avminstr {
    public:
    vmopcode opcode;
    vmarg* result;
    vmarg* arg1;
    vmarg* arg2;
    unsigned srcLine;
};

class avm_table;
class avm_memcell{
    public:
    avm_memcell_t type;
    double numVal;
    char* strVal;
    bool boolVal;
    avm_table* tableVal;
    unsigned funcVal;
    char* libfuncVal;
};

void avm_initstack(void);

double consts_getnumber(unsigned index);
string consts_getstring(unsigned index);
string libfuncs_getused(unsigned index);
userfunc* userfuncs_getfunc(unsigned index);

avm_memcell* avm_translate_operand(vmarg* arg, avm_memcell* reg);

void avm_memcellclear(avm_memcell* m);
void memclear_string(avm_memcell* m);
void memclear_table(avm_memcell* m);
//-----------------------------------------------------------------------------
avm_table* avm_tablenew(void);
void avm_tabledestroy(avm_table* t);
avm_memcell* avm_tablegetelem(avm_table* table, avm_memcell* index);
void avm_tablesetelem(avm_table* t, avm_memcell* i, avm_memcell* c);

#define AVM_TABLE_HASHSIZE 211
class avm_table_bucket{
    public:
    avm_memcell key;
    avm_memcell value;
    avm_table_bucket* next;
};

class avm_table{
    public:
    unsigned refCounter;
    avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
    avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
    unsigned strtotal;
    unsigned numtotal;
    unsigned total;
    string to_print;
};

void avm_tableincrefcounter(avm_table* t);
void avm_tabledecrefcounter(avm_table* t);
void avm_tablebucketsinit(avm_table_bucket** p);
avm_table* avm_tablenew(void);
void avm_tablebucketsdestroy(avm_table_bucket** p);
void avm_assign(avm_memcell* lv, avm_memcell* rv);
void avm_warning(string str);
void avm_callsaveenvironment();
void avm_calllibfunc(char* id);
void avm_call_functor(avm_table* t);
void avm_push_envvalue (unsigned val);
void avm_dec_top(void);
void avm_push_table_arg(avm_table* t);
unsigned avm_get_envvalue(unsigned int i);
void moveBuckets(avm_table* t, int index, avm_memcell* i);

char* avm_tostring(avm_memcell* m);
char* number_tostring(avm_memcell*);
char* string_tostring(avm_memcell*);
char* bool_tostring(avm_memcell*);
char* table_tostring(avm_memcell*);
char* userfunc_tostring(avm_memcell*);
char* libfunc_tostring(avm_memcell*);
char* undef_tostring(avm_memcell*);
char* nil_tostring(avm_memcell*);

library_func_t avm_getlibraryfunc(char* funcname);
void avm_registerlibfunc(char* id, library_func_t addr);
unsigned avm_totalactuals(void);
avm_memcell* avm_getactual(unsigned i);
userfunc* avm_getfuncinfo(unsigned address); 
int lookUpIndex(avm_table* t, avm_memcell* i);
int isNumber(const char* s);
void add_toprint(avm_table* t, avm_memcell* c);
void erase_fromprint(avm_table* t, string index);
void replace_fromprint(avm_table* t, string index, avm_memcell* c);
//-----------------------Implementation of Library Functions------------------
void libfunc_print(void); 
void libfunc_typeof(void);
void libfunct_input(void);
void libfunc_totalarguments(void);
void libfunc_argument(void);
void libfunct_objecttotalmembers(void);
void libfunc_strtonum(void);
void libfunct_sqrt(void);
void libfunct_cos(void);
void libfunct_sin(void);
//----------------------------------------------------------------------------
double add_impl(double x,double y);
double sub_impl(double x,double y);
double mul_impl(double x,double y);
double div_impl(double x,double y);
double mod_impl(double x,double y);

bool jge_impl(double x,double y);
bool jgt_impl(double x,double y);
bool jle_impl(double x,double y);
bool jlt_impl(double x,double y);

bool number_tobool(avm_memcell* m);
bool string_tobool(avm_memcell* m);
bool bool_tobool(avm_memcell* m);
bool table_tobool(avm_memcell* m);
bool userfunc_tobool(avm_memcell* m);
bool libfunc_tobool(avm_memcell* m);
bool nil_tobool(avm_memcell* m);
bool undef_tobool(avm_memcell* m);

bool avm_tobool(avm_memcell* m);


#endif