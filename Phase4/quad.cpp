#include "quad.h"
#include "SymbolTable.h"
using namespace std;

vector<quad> quads;
vector<quad*> quadptrs;
unsigned total = 0;
unsigned int currQuad = 0;
extern SymbolTable* symbolTable;
extern string convert_enum2[];
#define CURR_SIZE (quads.size())

void emit(iopcode op, expr* arg1, expr* arg2, expr* result, unsigned label, unsigned line){
    quad *p = new quad();
    p->op = op;
    p->arg1 = arg1;
    p->arg2 = arg2;
    p->result = result;
    p->label = label;
    p->line = line;    
    quads.push_back(*p);   
    quadptrs.push_back(&quads[quads.size()-1]);  
    currQuad++;
    total++; 
}

unsigned int nextquad (void) { return CURR_SIZE; }

expr* newexpr_constbool (bool b) {
    expr* e = newexpr(constbool_e);
    e->boolConst = b;
    return e;
}

void patchlabel(unsigned quadNo, unsigned label){
    if(quadNo <= currQuad )
        quads[quadNo-1].label = label;
}

void patchlist (int list, int label) {
    //cout <<"PATCHHHH"<<list<<endl;
    while (list) {
      //  cout <<"LIST"<<list<<endl;
        int next = quads[list-1].label;
        quads[list-1].label = label;
        list = next;
    }
}

int mergelist(int l1, int l2)
{   
    if (!l1)
        return l2;
    else if (!l2)
        return l1;
    else
    {
        int i = l1-1;
        
        while (quads[i].label) {
            i = quads[i].label-1;
          
           // cout << i<<endl;

        }
        quads[i].label = l2;
        return l1;
    }
}

void trueTest(expr* expr1) {
    expr1->truelist = nextquad() + 1;
    expr1->falselist = nextquad() + 2;
    emit(if_eq,expr1,newexpr_constbool(1),NULL,0,yylineno);
    emit(jump,NULL,NULL,NULL,0,yylineno);
}

void shortCircuitEval(expr* expr1) {
    expr1->evaluated = true;
   // expr1 = newexpr(boolexpr_e);
    expr1->sym = newtemp();

    
    patchlist(expr1->truelist, nextquad()+1);
    patchlist(expr1->falselist, nextquad() + 3);
    
    emit(assign, newexpr_constbool(true), NULL, expr1, 0, yylineno);
    emit(jump, NULL, NULL, NULL, nextquad() + 3, yylineno);
    emit(assign, newexpr_constbool(false), NULL, expr1, 0, yylineno);
    
}

bool check_defined(expr* expr){

    if (expr->type  == var_e ) {

        for (int i = 0; i < quads.size(); i++)
        {   
            if (quads.at(i).result != NULL &&  quads.at(i).arg1 != NULL) {
                if (quads.at(i).op == assign && (quads.at(i).result == expr || quads.at(i).result->sym->name == expr->sym->name) && quads.at(i).arg1->type != var_e)
                {
                    return true;
                }
            }
        }
    }
    else {
        return true;
    }
    return false;
}

void printQuads(void) {
    ofstream MyFile("quads.txt");
    MyFile<<"quad#\topcode  \t\tresult\t\targ1\t\targ2\t\tlabel"<<endl;
    MyFile<<"--------------------------------------------------------------------------------------"<<endl;
    int i=0;
    for(i=0; i<quads.size(); i++){
        MyFile<<i+1<<":\t\t"<<convert_enum2[quads.at(i).op];
        for (int j = (convert_enum2[quads.at(i).op]).size(); j < 16; j++) MyFile <<" ";
       
        if (quads.at(i).result != NULL) {
                switch (quads.at(i).result->type) {
                case constnum_e: MyFile << quads.at(i).result->numConst; break;
                case constbool_e: MyFile << boolalpha <<"\'"<<quads.at(i).result->boolConst<<"\'"; break;
                case conststring_e: MyFile << quads.at(i).result->strConst; break;
                case nil_e: MyFile << "nil"; break;
                default: MyFile << quads.at(i).result->sym->name;
            }
        } else { }
        MyFile<<"\t\t\t";
        
        if(quads.at(i).arg1 != NULL) {
            if (quads.at(i).arg1->sym != NULL && quads.at(i).arg1->sym->name != "") MyFile<<quads.at(i).arg1->sym->name;
            else {
                switch (quads.at(i).arg1->type) {
                case constnum_e: MyFile << quads.at(i).arg1->numConst; break;
                case constbool_e: MyFile << boolalpha <<"\'"<<quads.at(i).arg1->boolConst<<"\'"; break;
                case conststring_e: MyFile << quads.at(i).arg1->strConst; break;
                case nil_e: MyFile << "nil"; break;
                default: MyFile << quads.at(i).arg1->sym->name;
                }
            }
        } else { }
        MyFile<<"\t\t\t";
        
        if (quads.at(i).arg2 != NULL) {
            if (quads.at(i).arg2->sym != NULL && quads.at(i).arg2->sym->name != "") MyFile<<quads.at(i).arg2->sym->name;
            else {
                switch(quads.at(i).arg2->type){
                case constnum_e: MyFile<<quads.at(i).arg2->numConst; break;
                case constbool_e: MyFile<<boolalpha<<"\'"<<quads.at(i).arg2->boolConst<<"\'"; break;
                case conststring_e: MyFile<<quads.at(i).arg2->strConst; break;
                case nil_e: MyFile << "nil"; break;
                default: MyFile<<quads.at(i).arg2->sym->name;
                }
            }
        } else { }

        MyFile<<"\t\t\t"<<quads.at(i).label<<endl;
    }

    MyFile<<"--------------------------------------------------------------------------------------"<<endl;
    MyFile<<endl;
}

expr* operator_exist_return_arg2(iopcode op, expr* expr){
    for(int i=0; i<quads.size(); i++){
        if(quads.at(i).op == op && quads.at(i).result == expr)
            return quads.at(i).arg2;
    }
    return NULL;
}

expr* operator_exist_return_arg1(iopcode op, expr* expr){
    for(int i=0; i<quads.size(); i++){
        if(quads.at(i).op == op && quads.at(i).result == expr)
            return quads.at(i).arg1;
    }
    return NULL;
}



//---------------------------------------Temporary Variables-----------------------------------------------------

int tempcounter = 0;

void resettemp() { //must always be called με την αναγωγη ενος statement
    tempcounter = 0; 
} 

string newtempname() { 
    return "_t" + to_string(tempcounter); 
}

SymbolTableEntry* newtemp() {
    string name = newtempname();
    SymbolTableEntry* sym = symbolTable->lookUp(name, SCOPE);
    
    if (sym == NULL) {
        SymbolTableEntry* tmp = new SymbolTableEntry(name, SCOPE ? LOCALVAR : GLOBAL, var_s, SCOPE, 0);
        symbolTable->insert(tmp);
        tempcounter++;
        return tmp;
    }
    else {
        tempcounter++;
        return sym;
    }
}

bool istempname(string s) {
    return s[0] == '_';
}
bool istempexpr(expr* e) {
    return e->sym && istempname(e->sym->name);
}