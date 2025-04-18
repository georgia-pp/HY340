/* 
    HY340 Languages and Compilers              Alpha Compiler Syntactical Analysis

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

%{
	#include <stdio.h>
    #include <iostream>
    #include "SymbolTable.h"
    using namespace std;

    extern int yylex(void);
	extern int yylineno;
	extern char * yytext;
	extern FILE * yyin;

    SymbolTable* symbolTable = new SymbolTable();
    SymbolTableEntry* tmpFunct = NULL;
    int SCOPE = 0, FUNCTNUM = 0;
    bool insideAFunction = 0, RETURNEXPR = 0;
    enum Type{FUNCT, BLOCK, ZERO};
    vector<Type> vec;
    extern string error;

    int yyerror (string yaccProvidedMessage);    
%}

%start program

%union {
    char*   stringValue;
    int     intValue;
    double  realValue;
    class   SymbolTableEntry* exprNode;
}

%token <stringValue> ID
%token <intValue>    INTEGER
%token <realValue>   FLOAT
%token <stringValue> STRINGG
%type  <exprNode>    lvalue


%token IF 
%token ELSE
%token WHILE
%token FOR
%token RETURN 
%token BREAK
%token CONTINUE
%token AND
%token NOT
%token OR
%token LOCAL
%token TRUE
%token FALSE
%token NILL
%token FUNCTION
%token EQUAL
%token ADDITION
%token SUBTRACTION
%token MULTIPLICATION
%token DIVISION
%token MODE
%token ISEQUAL
%token NOTEQUAL
%token PLUSONE
%token MINUSONE
%token MORETHAN
%token LESSTHAN
%token MOREOREQUAL
%token LESSOREQUAL
%token LEFT_CURLY_BRACKET
%token RIGHT_CURLY_BRACKET
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token LEFT_PARENTHESIS
%token RIGHT_PARENTHESIS
%token SEMICOLON
%token COMMA
%token COLON
%token DOUBLECOLON
%token DOT
%token DOUBLEDOT


%right EQUAL
%left  OR
%left  AND 
%nonassoc ISEQUAL NOTEQUAL
%nonassoc MORETHAN MOREOREQUAL LESSTHAN LESSOREQUAL
%left  ADDITION SUBTRACTION
%left  MULTIPLICATION DIVISION MODE
%right NOT PLUSONE MINUSONE 
%left  DOT DOUBLEDOT
%left  LEFT_BRACKET RIGHT_BRACKET
%left  LEFT_PARENTHESIS RIGHT_PARENTHESIS

%%
program:    stmts {cout<<"stmts -> program"<<endl;}//there was another empty line here causing a reduce/reduce error
            ;

stmts:  stmt stmts  {cout<<"stmt stmts -> stmts"<<endl;}
        | /*empty*/ {cout << "empty -> stmts"<<endl;}
        ;

stmt:   expr SEMICOLON       {cout << "expr SEMICOLON -> stmt"<<endl;}
        | ifstmt             {cout << "ifstmt -> stmt"<<endl;}
        | whilestmt          {cout << "whilestmt -> stmt"<<endl;}
        | forstmt            {cout << "forstmt -> stmt"<<endl;}
        | returnstmt         {cout << "returnstmt -> stmt"<<endl;}
        | BREAK SEMICOLON    {cout << "BREAK SEMICOLON -> stmt"<<endl;}
        | CONTINUE SEMICOLON {cout << "CONTINUE SEMICOLON -> stmt"<<endl;}
        | block              {cout << "block -> stmt"<<endl;}
        | funcdef            {cout << "funcdef -> stmt"<<endl;}
        | SEMICOLON          {cout << "SEMICOLON -> stmt"<<endl;}
        ;

expr:   assignexpr {cout << "assignexpr -> expr" <<endl;}/*we reduce the oprator op to be in here*/
        | expr ADDITION expr {cout << "expr ADDITION expr -> expr"<< endl;}
        | expr SUBTRACTION expr {cout << "expr SUBTRACTION expr -> expr"<< endl;}
        | expr MULTIPLICATION expr {cout << "expr MULTIPLICATION expr -> expr"<< endl;}
        | expr DIVISION expr {cout << "expr MULTIPLICATION expr -> expr"<< endl;}
        | expr MODE expr {cout << "expr MULTIPLICATION expr -> expr"<< endl;}
        | expr MORETHAN expr {cout << "expr MULTIPLICATION expr -> expr"<< endl;}
        | expr MOREOREQUAL expr {cout << "expr MULTIPLICATION expr -> expr"<< endl;}
        | expr LESSTHAN expr {cout << "expr MULTIPLICATION expr -> expr"<< endl;}
        | expr LESSOREQUAL expr {cout << "expr MULTIPLICATION expr -> expr"<< endl;}
        | expr ISEQUAL expr {cout << "expr MULTIPLICATION expr -> expr"<< endl;}
        | expr NOTEQUAL expr {cout << "expr MULTIPLICATION expr -> expr"<< endl;}
        | expr AND expr {cout << "expr MULTIPLICATION expr -> expr"<< endl;}
        | expr OR expr {cout << "expr MULTIPLICATION expr -> expr"<< endl;}
        | term {cout << "term -> expr"<< endl;}
        ;

term:   LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {cout << "LEFT_PARENTHESIS expr RIGHT_PARENTHESIS -> term"<<endl;}
        | SUBTRACTION expr {cout << "SUBTRACTION expr -> term"<<endl;}
        | NOT expr {cout << "NOT expr -> term"<<endl;}
        | PLUSONE lvalue {cout << "PLUSONE lvalue -> term"<<endl; if( $2 != NULL) {if($2->type == LIB_FUNCTION || $2->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$2->name+" is declared as a function, forbidden action ++");} }
        | lvalue {if( $1 != NULL) { cout << "lvalue PLUSONE -> term"<<endl; if($1->type == LIB_FUNCTION || $1->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$1->name+" is declared as a function, forbidden action ++");} } PLUSONE
        | MINUSONE lvalue {if( $2 != NULL) { cout << "MINUSONE lvalue -> term"<<endl; if($2->type == LIB_FUNCTION || $2->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$2->name+" is declared as a function, forbidden action --");} }
        | lvalue {if( $1 != NULL) { cout << "lvalue MINUSONE -> term"<<endl; if($1->type == LIB_FUNCTION || $1->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$1->name+" is declared as a function, forbidden action --");} } MINUSONE
        | primary { cout << "primary -> term" <<endl;}
        ;

assignexpr: lvalue {if( $1 != NULL) {if($1->type == LIB_FUNCTION || $1->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$1->name+" is declared as a function, forbidden action =");} } EQUAL expr {cout << "lvalue EQUAL expr -> assignexpr"<<endl;}
            ;

primary:    lvalue {cout << "lvalue -> primary"<<endl; }
            | call {cout << "call -> primary"<<endl; }
            | objectdef {cout << "objectdef -> primary"<<endl;}
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS {cout << "LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS -> primary" <<endl; }
            | const {cout << "const -> primary" <<endl;}
            ;

lvalue:     ID {   cout << "ID -> lvalue"<<endl;
                   if (symbolTable->lookEverywhere($1,SCOPE) == NULL && !RETURNEXPR) {
                        symbolTable->insert( $$ = new SymbolTableEntry($1, SCOPE ? LOCALVAR : GLOBAL, SCOPE, yylineno, true)); 
                    }   
                    else {
                        SymbolTableEntry* tmp = symbolTable->lookEverywhere($1,SCOPE);
                        if (tmp != NULL) {
                            if (tmp->type == USERFUNCTION || tmp->scope == 0) $$ = tmp;
                            else {
                                int i;
                                for (i=vec.size()-1; vec.at(i)!=FUNCT && i != 0; i--) {
                                    
                                }
                                
                                if (tmp->scope >= i) $$ = tmp;
                                else {$$ = NULL; symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$1+" cannot be accessed");}
                            }
                        } else {
                            if (RETURNEXPR) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$1+" has not been declared");
                            $$ = NULL;
                        }
                    } 
                }
            | LOCAL ID { cout << "LOCAL ID -> lvalue"<<endl; 
                $$ = NULL; 
                if( symbolTable->isLibFunct($2) && SCOPE != 0) {
                    symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$2+": collision with library function");
                }
                else if (SCOPE == 0) {
                    if (symbolTable->isLibFunct($2) ) {
                        $$ = symbolTable->lookUp($2,0);
                    }
                    else {
                        symbolTable->insert( $$ = new SymbolTableEntry($2, GLOBAL, SCOPE, yylineno, true));
                    }
                }
                else 
                    symbolTable->insert($$ = new SymbolTableEntry($2, LOCALVAR, SCOPE, yylineno, true));
            }
            | DOUBLECOLON ID { cout << "DOUBLECOLON ID -> lvalue"<<endl;
                if(! ($$ = symbolTable->lookUp($2, 0))){
                    symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$2+" undefined variable/function");
                } 
            }
            | member { cout << "member -> lvalue"<<endl; }
            ;

member:     lvalue DOT ID { cout << "lvalue DOT ID -> member"<<endl;}
            | lvalue LEFT_BRACKET expr RIGHT_BRACKET { cout << "lvalue LEFT_BRACKET expr RIGHT_BRACKET -> member"<<endl;}
            | call DOT ID { cout << "call DOT ID -> member"<<endl;}
            | call LEFT_BRACKET expr RIGHT_BRACKET { cout << "call LEFT_BRACKET expr RIGHT_BRACKET -> member"<<endl;}
            ;
            
call:       call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS { cout << "call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS -> call" << endl;}
            | lvalue callsuffix {cout << "lvalue callsuffix -> call"<<endl;} 
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {cout << "LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS -> call"<<endl;}//i had put in the first LEFT_PARENTHESIS insted of LEFT i had put RIGHT
            ;

callsuffix: normcall { cout << "normvall -> callsuffix" <<endl;}
            | methodcall {cout << "methodcall -> callsuffix" <<endl;}
            ;

normcall:   LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {cout << "LEFT_PARENTHESIS elist RIGHT_PARENTHESIS -> normcall" <<endl;}
            ;

methodcall: DOUBLEDOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {cout << "DOUBLEDOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS -> methodcall"<<endl;}
            ;

elist:      expr exprs {cout << "expr exprs -> elist"<<endl;}
            | /*empty*/ {cout << "empty -> elist"<<endl;}
            ;

exprs:      COMMA expr exprs {cout << "COMMA expr exprs -> exprs"<<endl;}
            | /*empty*/
            ;

objectdef:  LEFT_BRACKET elist RIGHT_BRACKET {cout << "LEFT_BRACKET elist RIGHT_BRACKET -> objectdef"<<endl;}
            | LEFT_BRACKET indexed RIGHT_BRACKET {cout << "LEFT_BRACKET indexed RIGHT_BRACKET -> objectdef"<<endl;}//removed an extra line | LEFT_BRACKET /*empty*/ RIGHT_BRACKET because it is already included in elist
            ;

indexed:    indexedelem indexedelems {cout << "indexedelem indexedelems -> indexed"<<endl;} //there was an empty line here that was causing a reduce/reduce error
            ;

indexedelems:   COMMA indexedelem indexedelems {cout << "COMMA indexedelem indexedelems -> indexedelems"<<endl;}
                | /*empty*/ {cout << "empty -> indexedelems" <<endl;}
                ;

indexedelem:    LEFT_CURLY_BRACKET expr COLON expr RIGHT_CURLY_BRACKET {cout << "LEFT_CURLY_BRACKET expr COLON expr RIGHT_CURLY_BRACKET -> indexedelem"<<endl;}
                ;

block:          LEFT_CURLY_BRACKET {if (!insideAFunction) { SCOPE++; vec.push_back(BLOCK); } else {insideAFunction = false;} } stmts RIGHT_CURLY_BRACKET { if (vec.back() == BLOCK) {symbolTable->hide(SCOPE); SCOPE--; vec.pop_back();} cout << "LEFT_CURLY_BRACKET stmts RIGHT_CURLY_BRACKET -> block"<<endl;}
                ;

funcdef:        FUNCTION ID {symbolTable->insert(tmpFunct = new SymbolTableEntry($2, USERFUNCTION, SCOPE, yylineno, true));} LEFT_PARENTHESIS {insideAFunction = true;  SCOPE++; vec.push_back(FUNCT);} idlist RIGHT_PARENTHESIS block {vec.pop_back(); symbolTable->hide(SCOPE); SCOPE--; tmpFunct = NULL; cout << "FUNCTION ID LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block -> funcdef"<<endl;}
                | FUNCTION {symbolTable->insert(tmpFunct = new SymbolTableEntry("_f"+to_string(FUNCTNUM), USERFUNCTION, SCOPE, yylineno, true));} LEFT_PARENTHESIS {FUNCTNUM++; insideAFunction = true; SCOPE++; vec.push_back(FUNCT);} idlist RIGHT_PARENTHESIS block {vec.pop_back();  symbolTable->hide(SCOPE); SCOPE--; tmpFunct = NULL; cout << "FUNCTION LEFT_PARENTHESIS idlist RIGHT_PARENTHESIS block -> funcdef"<<endl;}
                ;

const:          INTEGER {cout <<"INTEGER -> const"<<endl;} | FLOAT{cout <<"FLOAT -> const"<<endl;} | STRINGG{cout <<"STRINGG -> const"<<endl;} | NILL{cout <<"NILL -> const"<<endl;} | TRUE{cout <<"TRUE -> const"<<endl;} | FALSE {cout <<"FALSE -> const"<<endl;} ;

idlist:         ID { SymbolTableEntry* tmparg; symbolTable->insert(tmparg = new SymbolTableEntry($1, FORMAL, SCOPE, yylineno, true)); if (tmpFunct != NULL){ tmpFunct->insertArg(tmparg); }} ids {cout <<"ID ids -> idlist"<<endl;}
                | /*empty*/ {cout <<"empty -> idlist"<<endl;}
                ;

ids:            COMMA ID { SymbolTableEntry* tmparg; symbolTable->insert(tmparg = new SymbolTableEntry($2, FORMAL, SCOPE, yylineno, true)); if (tmpFunct != NULL){ tmpFunct->insertArg(tmparg); }}ids {cout << "COMMA ID ids -> ids"<<endl;}
                | /*empty*/ {cout <<"empty -> ids"<<endl;}
                ;

ifstmt:         IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt {cout <<"IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt -> ifstmt"<<endl;}
                | IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt {cout <<"IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt -> ifstmt"<<endl;}
                ;

whilestmt:      WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt {cout <<"WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt -> whilestmt"<<endl;}
                ;

forstmt:        FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt {cout <<"FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt  -> forstmt"<<endl;}
                ;

returnstmt:     RETURN { RETURNEXPR = true; } expr SEMICOLON { RETURNEXPR = false; cout << "REUTRN expr SEMICOLON -> returnstmt"<<endl;}
                | RETURN SEMICOLON {cout << "RETURN SEMICOLON -> returnstmt"<<endl;}
                ;

%%

int yyerror (string yaccProvideMessage){
	symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": token \""+ yytext +"\" "+yaccProvideMessage.c_str());
    return 0;
}

int main(int argc, char **argv) {
    if(argc > 1) {
        vec.push_back(ZERO);
        if(!(yyin = fopen(argv[1],"r"))) {
            fprintf(stderr, "Cannot read file: %s\n", argv[1]);
            return 1;
        }
    }
    else {
        yyin = stdin;
    }

    yyparse();
    symbolTable->displayHash();
    return 0;
}

