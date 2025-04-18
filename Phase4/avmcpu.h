#ifndef AVM_CPU_H
#define AVM_CPU_H

/* 
    HY340 Languages and Compilers              Alpha Compiler Virtual Machine

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

#include <iostream>
#include "avm.h"

void execute_cycle (void);

void execute_comparison(avminstr* instr);
void execute_arithmetic(avminstr* instr);

void execute_assign (avminstr*);
void execute_add (avminstr*);
void execute_sub (avminstr*);
void execute_mul (avminstr*);
void execute_div (avminstr*);
void execute_mod (avminstr*);
void execute_uminus (avminstr*);
void execute_and (avminstr*);
void execute_or (avminstr*);
void execute_not (avminstr*);
void execute_jeq (avminstr*);
void execute_jne (avminstr*);
void execute_jle (avminstr*);
void execute_jge (avminstr*);
void execute_jlt (avminstr*);
void execute_jgt (avminstr*);
void execute_call (avminstr*);
void execute_pusharg (avminstr*);
void execute_funcenter (avminstr*);
void execute_funcexit (avminstr*);
void execute_newtable (avminstr*);
void execute_tablegetelem (avminstr*);
void execute_tablesetelem (avminstr*);
void execute_nop (avminstr*);
void execute_jump (avminstr*);

#endif