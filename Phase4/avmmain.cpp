#include <iostream>
#include <fstream>
#include "avm.h"
#include "avmcpu.h"

#define MAGICNUMBER 340200501U
using namespace std;

/* 
    HY340 Languages and Compilers              Alpha Compiler Virtual Machine

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

extern vector<double> constNumArr;
extern vector<string> constStrArr;
extern vector<string> constLibFunArr;
extern vector<userfunc*> constUserFunArr;
extern vector<avminstr*> avm_code;
extern vector<string> warnings;
extern vector<string> errors;
extern string convert_vmargenum[12];
extern string convert_vmopcodeenum[25];
extern int GLOBAL_NUM;
extern bool executionFinished;
extern avm_memcell stack[AVM_STACKSIZE];
extern unsigned top;


void decodeBinaryFile(string file) {
    ifstream rf(file, ios::out | ios::binary);
    if(!rf) {
      cerr <<"\033[1;31m"<< "ERROR: Cannot open file!" <<"\033[0m"<<endl;
      exit(1); 
    }

    int val;
    uint8_t type;
    int totals; //reads the totals for stringarr, numarr, userfuncarr, libfuncarr, instructions
    int magicnum; //reads magicnumber
    int size;
    string str;
    double number;
    int address;
    int localsize;
    int formalsize;
    string id;

//-------------see if the file we are reading from is an alpha binary file------------
    rf.read((char*)&magicnum, 4);
    if (magicnum != MAGICNUMBER) {
        cerr<<"\033[1;31m"<<"ERROR: file "<<file<<" is not an alpha binary file"<<"\033[0m"<<endl;
        exit(1);
    }
    //cout<<"MAGICNUM: "<<magicnum<<endl;

//-------------Number of total Globals------------------------------------------------
    rf.read((char*)&totals, 4);
    GLOBAL_NUM = totals;
    //cout<<"GLOBAL#: "<<GLOBAL_NUM<<endl;;
//-------------Read total num of const strings in conststringarr----------------------
    rf.read((char*)&totals, 4);
    //cout<<"STRING TOTALS: "<<totals<<endl;
    for (size_t i = 0; i < totals; i++)
    {   
        rf.read((char*)&size, 4);
        char str1[size];
        rf.read(str1,size);
        str = str1;
        constStrArr.push_back(str);
        //cout <<"CONST STRING SIZE nullterm: "<< size<<", str: "<<constStrArr[i]<<endl;//the string in the vector is not nullterminated
    }
    
//-------------Read total num of const nums in constNumArr----------------------
    rf.read((char*)&totals, 4);
    //cout<<"NUMBER TOTALS: "<<totals<<endl;
    for (size_t i = 0; i < totals; i++)
    {   
        rf.read((char*)&number,8);
        constNumArr.push_back(number);
        //cout <<"CONST NUMBER: "<<constNumArr[i]<<endl;
    }

//-------------Read total num of user Functions in constUserFunArr----------------------
    rf.read((char*)&totals, 4);
    //cout<<"USER FUNC TOTALS: "<<totals<<endl;
    for (size_t i = 0; i < totals; i++)
    {   
        rf.read((char*)&address,4);
        rf.read((char*)&formalsize,4);
        rf.read((char*)&localsize,4);
        rf.read((char*)&size, 4);
        char str1[size];
        rf.read(str1,size);
        id = str1;
        userfunc *funct = new userfunc();
        funct->address = address;
        funct->formalsize = formalsize;
        funct->localSize = localsize;
        funct->id = id;
        constUserFunArr.push_back(funct);
        //cout <<"USER FUNCT: addr "<<constUserFunArr[i]->address<<", formalsize "<<constUserFunArr[i]->formalsize<<", localsize "<<constUserFunArr[i]->localSize<<", id "<<constUserFunArr[i]->id<<endl;
    }
//-------------Read total num of lib Functions in constLibFunArr----------------------
    rf.read((char*)&totals, 4);
    //cout<<"LIB FUNCT TOTALS: "<<totals<<endl;
    for (size_t i = 0; i < totals; i++)
    {   
        rf.read((char*)&size, 4);
        char str1[size];
        rf.read(str1,size);
        str = str1;
        constLibFunArr.push_back(str);
        //cout <<"CONST LIB FUNCT: size(null term)"<< size<<", name: "<<constLibFunArr[i]<<endl;//the string in the vector is not nullterminated
    }

//-------------Read Instructions--------------------------------------------------------
    rf.read((char*)&totals, 4);
    //cout<<"INSTRUCTION TOTALS: "<<totals<<endl;
    for (size_t i = 0; i < totals; i++)
    {   
        uint8_t op;
        avminstr* instr = new avminstr();
        rf.read((char*)&op,1);
        instr->opcode = (vmopcode)op;
        // Result
        rf.read((char*)&type,1);
        instr->result = new vmarg();
        instr->result->type = (vmarg_t)type;
        rf.read((char*)&val,4);
        instr->result->val = val;
        // Arg1
        rf.read((char*)&type,1);
        instr->arg1 = new vmarg();
        instr->arg1->type = (vmarg_t)type;
        rf.read((char*)&val,4);
        instr->arg1->val = val;
        // Arg2
        rf.read((char*)&type,1);
        instr->arg2 = new vmarg();
        instr->arg2->type = (vmarg_t)type;
        rf.read((char*)&val,4);
        instr->arg2->val = val;
        // srcLine
        rf.read((char*)&val,4);
        instr->srcLine = val;
        avm_code.push_back(instr);

       /* cout <<"INSTR NUMBER "<<i<<": opcode "<<convert_vmopcodeenum[avm_code.at(i)->opcode];
          cout<<"      Result: ";
        if (avm_code.at(i)->result->type == empty_a) cout<<"      ";
        else cout << convert_vmargenum[avm_code.at(i)->result->type] << " "<<avm_code.at(i)->result->val;
        cout<<"      arg1: ";
        if (avm_code.at(i)->arg1->type == empty_a) cout<<"      ";
        else cout << convert_vmargenum[avm_code.at(i)->arg1->type] << " "<<avm_code.at(i)->arg1->val;
        cout<<"      arg2: ";
        if (avm_code.at(i)->arg2->type == empty_a) cout<<"      ";
        else cout << convert_vmargenum[avm_code.at(i)->arg2->type] << " "<<avm_code.at(i)->arg2->val;
        cout<<" srcLine: "<<avm_code.at(i)->srcLine<<endl;*/
    }
}

void print_warrnings_errors() {
    for (size_t i = 0; i < warnings.size(); i++)
    {
        cout <<"\033[1;35m"<< warnings.at(i)<<"\033[0m"<<endl;
    }

    for (size_t i = 0; i < errors.size(); i++)
    {
        cout <<"\033[1;31m"<<errors.at(i)<<"\033[0m"<<endl;
    }
}

void registerlibfunctions() {
    string libfun = "print";
    avm_registerlibfunc(strdup((char*)libfun.c_str()), libfunc_print);
    libfun = "typeof";
    avm_registerlibfunc(strdup((char*)libfun.c_str()), libfunc_typeof);
    libfun = "input";
    avm_registerlibfunc(strdup((char*)libfun.c_str()), libfunct_input);
    libfun = "totalarguments";
    avm_registerlibfunc(strdup((char*)libfun.c_str()), libfunc_totalarguments);
    libfun = "argument";
    avm_registerlibfunc(strdup((char*)libfun.c_str()), libfunc_argument);
    libfun = "objecttotalmembers";
    avm_registerlibfunc(strdup((char*)libfun.c_str()), libfunct_objecttotalmembers);
    libfun = "strtonum";
    avm_registerlibfunc(strdup((char*)libfun.c_str()),libfunc_strtonum);
    libfun = "sqrt";
    avm_registerlibfunc(strdup((char*)libfun.c_str()),libfunct_sqrt);
    libfun = "cos";
    avm_registerlibfunc(strdup((char*)libfun.c_str()),libfunct_cos);
    libfun = "sin";
    avm_registerlibfunc(strdup((char*)libfun.c_str()),libfunct_sin);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr<<"\033[1;31m"<<"Format: ./a.out <binary file> "<<"\033[0m"<<endl;
        exit(1);
    } 

    decodeBinaryFile(argv[1]);
    avm_initstack();
    registerlibfunctions(); 
    
    while(!executionFinished) {
        execute_cycle();
    }

    print_warrnings_errors();
}