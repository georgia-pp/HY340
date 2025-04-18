/* 
    HY340 Languages and Compilers              Alpha Compiler Syntactical Analysis

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

%{
	#include <stdio.h>
    #include <iostream>
    #include <cmath>
    #include "SymbolTable.h"
    #include "quad.h"
    #include "expr.h"

    using namespace std;

    extern int yylex(void);
	extern int yylineno;
	extern char * yytext;
	extern FILE * yyin;
    extern unsigned int functionLocalOffset;

    SymbolTable* symbolTable = new SymbolTable();
    SymbolTableEntry* tmpFunct = NULL;
    int SCOPE = 0, FUNCTNUM = 0;
    unsigned int functCounter = 0;
    int functionCall = 0;
    int tableInstansiation = 0;
    vector<int> offsetStack;
    vector<unsigned int> returnLabel;
    vector <expr*> pairA, pairB;
    vector <expr*> tableitems;
    vector<int> breaklist;
    vector<int> contlist;
    bool loopActive=false;
    bool insideAFunction = 0, RETURNEXPR = 0;
    bool doubleDotEncountered = false; 
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
    class   expr* exprNode2;
    class   forprefix* forNode;
}

%token <stringValue>  ID
%token <intValue>     INTEGER
%token <realValue>    FLOAT
%token <stringValue>  STRINGG
%type  <exprNode2>    lvalue
%type  <exprNode2>    const
%type  <exprNode2>    expr
%type  <exprNode2>    primary
%type  <exprNode2>    term
%type  <exprNode2>    assignexpr
%type  <stringValue>  funcname
%type  <intValue>     funcbody  
%type  <exprNode2>    funcprefix
%type  <exprNode2>    funcdef
%type  <intValue>     ifstmt
%type  <intValue>     ifprefix
%type  <intValue>     elseprefix
%type  <intValue>     whilecond
%type  <intValue>     whilestart
%type  <forNode>      forprefix
%type  <intValue>     M
%type  <intValue>     N
%type  <exprNode2>    tableitem
%type  <exprNode2>    tablemake
%type  <exprNode2>    elist
%type  <exprNode2>    exprs 
%type  <exprNode2>    call
%type  <exprNode2>    member
%type  <stringValue>  methodcall
%type  <stringValue>  callsuffix
   

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

stmts:  stmt /*{resettemp();}*/ stmts  {cout<<"stmt stmts -> stmts"<<endl;}
        | /*empty*/ {cout << "empty -> stmts"<<endl;}
        ;

stmt:   expr SEMICOLON       {cout << "expr SEMICOLON -> stmt"<<endl;
            if ($1->type == boolexpr_e && !$1->evaluated) {
                //$1->sym = newtemp();
                shortCircuitEval($1);
                   
            }
            resettemp();
        }
        | ifstmt             {cout << "ifstmt -> stmt"<<endl;}
        | whilestmt          {cout << "whilestmt -> stmt"<<endl;}
        | forstmt            {cout << "forstmt -> stmt"<<endl;}
        | returnstmt         {cout << "returnstmt -> stmt"<<endl;}
        | BREAK SEMICOLON    {cout << "BREAK SEMICOLON -> stmt"<<endl;
            if(!loopActive) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": break statement only allowed inside loops");
            else {  
                breaklist.push_back(nextquad()+1);
                emit(jump,NULL,NULL,NULL,0,yylineno);
            }
        }
        | CONTINUE SEMICOLON {cout << "CONTINUE SEMICOLON -> stmt"<<endl;
            if(!loopActive) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": continue statement only allowed inside loops");
            else{   
                contlist.push_back(nextquad()+1);
                emit(jump,NULL,NULL,NULL,0,yylineno);
            }
        }
        | block              {cout << "block -> stmt"<<endl;}
        | funcdef            {cout << "funcdef -> stmt"<<endl;}
        | SEMICOLON          {cout << "SEMICOLON -> stmt"<<endl;}
        ;

expr:   assignexpr {cout << "assignexpr -> expr" <<endl; 
            $$ = $1;
        }/*we reduce the oprator op to be in here*/
        | expr ADDITION expr {
            cout << "expr ADDITION expr -> expr"<< endl;
            
            if( !checkarithmetic_type($1,$3) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ($1->type == constnum_e && $3->type == constnum_e) {
                    $$ = newexpr(constnum_e);
                    $$->numConst = $1->numConst + $3->numConst;
                } else {
                    $$ = newexpr(arithexpr_e);
                }
                if (istempexpr($1)) { /*this if was inside the else above and therefore if $1=constnum && $3==constnum then there wound be an assignement to $$->sym and when print goes to print it segmentation fault happens*/
                    $$->sym = $1->sym;
                } else if (istempexpr($3)) {
                    $$->sym = $3->sym;
                } else {
                    $$->sym = newtemp();
                }

                emit(add, $1, $3, $$, 0, yylineno);
        }
        | expr SUBTRACTION expr {
            cout << "expr SUBTRACTION expr -> expr"<< endl;
            
            if( !checkarithmetic_type($1,$3) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ($1->type == constnum_e && $3->type == constnum_e) {
                    $$ = newexpr(constnum_e);
                    $$->numConst = $1->numConst - $3->numConst;
                } else {
                    $$ = newexpr(arithexpr_e);
                }
                if (istempexpr($1)) { 
                    $$->sym = $1->sym;
                } else if (istempexpr($3)) {
                    $$->sym = $3->sym;
                } else {
                    $$->sym = newtemp();
                }
                emit(sub, $1, $3, $$, 0, yylineno);
          
        }
        | expr MULTIPLICATION expr {
            cout << "expr MULTIPLICATION expr -> expr"<< endl;

            if( !checkarithmetic_type($1,$3) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ($1->type == constnum_e && $3->type == constnum_e) {
                    $$ = newexpr(constnum_e);
                    $$->numConst = $1->numConst * $3->numConst;
                } else {
                    $$ = newexpr(arithexpr_e);
                }
                if (istempexpr($1)) {
                    $$->sym = $1->sym;
                } else if (istempexpr($3)) {
                    $$->sym = $3->sym;
                } else {
                    $$->sym = newtemp();
                }
                emit(mul, $1, $3, $$, 0, yylineno);
        }
        | expr DIVISION expr {
            cout << "expr DIVISION expr -> expr"<< endl;

            if( !checkarithmetic_type($1,$3) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ($1->type == constnum_e && $3->type == constnum_e) {
                    $$ = newexpr(constnum_e);
                    $$->numConst = $1->numConst / $3->numConst;
                } else {
                    $$ = newexpr(arithexpr_e);
                }
                if (istempexpr($1)) {
                    $$->sym = $1->sym;
                } else if (istempexpr($3)) {
                    $$->sym = $3->sym;
                } else {
                    $$->sym = newtemp();
                }
                emit(division, $1, $3, $$, 0, yylineno);  
        }
        | expr MODE expr {
            cout << "expr MOD expr -> expr"<< endl;
            
            if( !checkarithmetic_type($1,$3) ) symbolTable->errors.push_back("RUNTIME RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ($1->type == constnum_e && $3->type == constnum_e) {
                    $$ = newexpr(constnum_e);
                    $$->numConst = fmod($1->numConst ,$3->numConst);
                } else {
                    $$ = newexpr(arithexpr_e);
                }
                if (istempexpr($1)) {
                    $$->sym = $1->sym;
                } else if (istempexpr($3)) {
                    $$->sym = $3->sym;
                } else {
                    $$->sym = newtemp();
                }
                emit(mod, $1, $3, $$, 0, yylineno);
        }
        | expr MORETHAN expr {
            cout << "expr MORETHAN expr -> expr"<< endl;
            
            if( !checkarithmetic_type($1,$3) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                $$ = newexpr(boolexpr_e);
                //$$->sym = newtemp();
               
                $$->truelist = nextquad()+1;//because nextquad() returns the position in the vector that the nextwuad is going to be in
                $$->falselist = nextquad()+2;
                emit(if_greater, $1, $3, NULL, 0, yylineno);
                emit(jump, NULL, NULL, NULL, 0, yylineno);
        }
        | expr MOREOREQUAL expr {
            cout << "expr MOREOREQUAL expr -> expr"<< endl;

             if( !checkarithmetic_type($1,$3) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                $$ = newexpr(boolexpr_e);
                
                /*if (istempexpr($1)) {
                    $$->sym = $1->sym;
                } else if (istempexpr($3)) {
                    $$->sym = $3->sym;
                } else {
                    $$->sym = newtemp();
                    cout <<"LINE 280: "<<$$->sym->name<<endl;
                }*/
                
                $$->truelist = nextquad()+1;//because nextquad() returns the position in the vector that the nextwuad is going to be in
                $$->falselist = nextquad()+2;
                emit(if_greatereq, $1, $3, NULL, 0, yylineno);
                emit(jump, NULL, NULL, NULL, 0, yylineno);
        }
        | expr LESSTHAN expr {
            cout << "expr LESSTHAN expr -> expr"<< endl;
            
            if( !checkarithmetic_type($1,$3) ) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                $$ = newexpr(boolexpr_e);
                
                /*if (istempexpr($1)) {
                    $$->sym = $1->sym;
                } else if (istempexpr($3)) {
                    $$->sym = $3->sym;
                } else {
                    $$->sym = newtemp();
                    cout <<"LINE 300: "<<$$->sym->name<<endl;
                }*/
            
                $$->truelist = nextquad()+1;
                $$->falselist = nextquad()+2;
                emit(if_less, $1, $3, NULL, 0, yylineno);
                emit(jump, NULL, NULL, NULL, 0, yylineno);
                
        }
        | expr LESSOREQUAL expr {
            cout << "expr LESSOREQUAL expr -> expr"<< endl;
            
            if( !checkarithmetic_type($1,$3) )symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                $$ = newexpr(boolexpr_e);
                //$$->sym = newtemp();

                $$->truelist = nextquad()+1;//because nextquad() returns the position in the vector that the nextwuad is going to be in
                $$->falselist = nextquad()+2;
                emit(if_lesseq, $1, $3, NULL, 0, yylineno);
                emit(jump, NULL, NULL, NULL, 0, yylineno);
        }
        | expr ISEQUAL {if ($1->type == boolexpr_e && !$1->evaluated) shortCircuitEval($1);} expr {
            cout << "expr ISEQUAL expr -> expr"<< endl;

            if ($4->type == boolexpr_e && !$4->evaluated) {
                shortCircuitEval($4);
            }

            $$ = newexpr(boolexpr_e);
           
            /*  if (istempexpr($1)) {
                    $$->sym = $1->sym;
                } else if (istempexpr($4)) {
                    $$->sym = $4->sym;
                } else {
                    $$->sym = newtemp();
                    cout <<"LINE 338: "<<$$->sym->name<<endl;
                }*/
            

            $$->truelist = nextquad()+1;//because nextquad() returns the position in the vector that the nextwuad is going to be in
            $$->falselist = nextquad()+2;
            emit(if_eq, $1, $4, NULL, 0, yylineno);
            emit(jump, NULL, NULL, NULL, 0, yylineno);
        }
        | expr NOTEQUAL {if ($1->type == boolexpr_e && !$1->evaluated) shortCircuitEval($1);} expr {
            cout << "expr NOTEQUAL expr -> expr"<< endl;
        
            if ($4->type == boolexpr_e && !$4->evaluated) {
                shortCircuitEval($4);
            }

            $$ = newexpr(boolexpr_e);
            //$$->sym = newtemp();

            $$->truelist = nextquad()+1;//because nextquad() returns the position in the vector that the nextwuad is going to be in
            $$->falselist = nextquad()+2;
            emit(if_noteq, $1, $4, NULL, 0, yylineno);
            emit(jump, NULL, NULL, NULL, 0, yylineno);  
        }
        | expr AND {if ($1->type != boolexpr_e) { trueTest($1); }} M expr {
            cout << "expr AND expr -> expr"<< endl;
           
            if ($5->type != boolexpr_e ) { 
                trueTest($5); 
            }

            $$ = newexpr(boolexpr_e);
            /*if (istempexpr($1)) {
                $$->sym = $1->sym;
            } else if (istempexpr($5)) {
                $$->sym = $5->sym;
            } else {
                $$->sym = newtemp();
                cout <<"LINE 280: "<<$$->sym->name<<endl;
            }*/
            //$$->sym = newtemp();

            patchlist($1->truelist, $4);
            $$->truelist = $5->truelist;
            $$->falselist = mergelist($1->falselist, $5->falselist);
        }
        | expr OR {if ($1->type != boolexpr_e) { trueTest($1); }} M expr {
            cout << "expr OR expr -> expr"<< endl;

            if ($5->type != boolexpr_e) { 
                trueTest($5); 
            }

            $$ = newexpr(boolexpr_e);
            /*if (istempexpr($1)) {
                $$->sym = $1->sym;
            } else if (istempexpr($5)) {
                $$->sym = $5->sym;
            } else {
                $$->sym = newtemp();
            }*/

            patchlist($1->falselist,$4);
            $$->truelist = mergelist($1->truelist, $5->truelist);
            $$->falselist = $5->falselist;
        }
        | term {cout << "term -> expr"<< endl; $$ = $1;}
        ;

M: { $$ = nextquad() + 1; }

N: {$$ = nextquad()+1; emit(jump, NULL, NULL, NULL, nextquad()+1, yylineno);}

term:   LEFT_PARENTHESIS expr RIGHT_PARENTHESIS {cout << "LEFT_PARENTHESIS expr RIGHT_PARENTHESIS -> term"<<endl; 
            $$ = $2;
            //if ($2->type == boolexpr_e && !$2->evaluated) shortCircuitEval($2);
        }
        | SUBTRACTION expr {cout << "SUBTRACTION expr -> term"<<endl;
            if (!checkarithmetic_type($2,$2)) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");
                if ($2->type == constnum_e ) {
                    $$ = newexpr(constnum_e);
                    $$->numConst = -1*$2->numConst;
                } else {
                    $$ = newexpr(arithexpr_e);
                }
                if (istempexpr($2)) { /*this if was inside the else above and therefore if $1=constnum && $3==constnum then there wound be an assignement to $$->sym and when print goes to print it segmentation fault happens*/
                    $$->sym = $2->sym;
                } else {
                    $$->sym = newtemp();
                }
                emit(uminus, $2, NULL, $$, 0, yylineno);
        }
        | NOT expr {cout << "NOT expr -> term"<<endl;
            if ($2->type != boolexpr_e) {
                trueTest($2);
                //$$ = newexpr(boolexpr_e);
            } /*else {
                $$ = $2;
            }*/

            $$ = newexpr(boolexpr_e);

            $$->truelist = $2->falselist;
            $$->falselist = $2->truelist;
        }
        | PLUSONE lvalue {cout << "PLUSONE lvalue -> term"<<endl; /*if( $2 != NULL) {if($2->sym->type == LIB_FUNCTION || $2->sym->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$2->sym->name+" is declared as a function, forbidden action ++");} */
            if (!checkarithmetic_type($2,$2)) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");

            if ($2->type == tableitem_e) {
                $$ = emit_iftableitem($2);
                emit(add, $$, newexpr_constnum(1), $$, 0,yylineno);
                emit(tablesetelem, $2->index, $$, $2, 0, yylineno);
            }
            else {
                emit(add, $2, newexpr_constnum(1), $2, 0, yylineno);
                $$ = newexpr(arithexpr_e);
                if (istempexpr($2)) { //dont know if i want to reuse temp here
                    $$->sym = $2->sym;
                } else {
                    $$->sym = newtemp();
                }
                emit(assign, $2, NULL, $$,0,yylineno);
            }
        }
        | lvalue {if( $1 != NULL) { cout << "lvalue PLUSONE -> term"<<endl; /*if($1->sym->type == LIB_FUNCTION || $1->sym->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$1->sym->name+" is declared as a function, forbidden action ++");*/} } PLUSONE {
            if (!checkarithmetic_type($1,$1)) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");

            $$ = newexpr(var_e);
            if (istempexpr($1)) { //dont know if i want to reuse temp here
                $$->sym = $1->sym;
            } else {
                $$->sym = newtemp();
            }

            if ( $1->type == tableitem_e) {
                expr* val = emit_iftableitem($1);
                emit(assign, val, NULL, $$, 0, yylineno);
                emit(add, val, newexpr_constnum(1), val, 0, yylineno);
                emit(tablesetelem, $1->index, val, $1, 0, yylineno);
            } else {
                emit(assign, $1, NULL, $$, 0, yylineno);
                emit(add, $1, newexpr_constnum(1), $1, 0, yylineno);
            }
        }
        | MINUSONE lvalue {if( $2 != NULL) { cout << "MINUSONE lvalue -> term"<<endl; /*if($2->sym->type == LIB_FUNCTION || $2->sym->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$2->sym->name+" is declared as a function, forbidden action --");*/} 
            if (!checkarithmetic_type($2,$2)) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");

            if ($2->type == tableitem_e) {
                $$ = emit_iftableitem($2);
                emit(sub, $$, newexpr_constnum(1), $$, 0,yylineno);
                emit(tablesetelem, $2->index, $$, $2, 0, yylineno);
            }
            else {
                emit(sub, $2, newexpr_constnum(1), $2, 0, yylineno);
                $$ = newexpr(arithexpr_e);
                if (istempexpr($2)) { //dont know if i want to reuse temp here
                    $$->sym = $2->sym;
                } else {
                    $$->sym = newtemp();
                }
                emit(assign, $2, NULL, $$,0,yylineno);
            }
        }
        | lvalue {if( $1 != NULL) { cout << "lvalue MINUSONE -> term"<<endl; /*if($1->sym->type == LIB_FUNCTION || $1->sym->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$1->sym->name+" is declared as a function, forbidden action --");*/} } MINUSONE {
            if (!checkarithmetic_type($1,$1)) symbolTable->errors.push_back("RUNTIME ERROR in line "+to_string(yylineno)+": invalid arithmetic expression");

            $$ = newexpr(var_e);
            if (istempexpr($1)) { //dont know if i want to reuse temp here
                $$->sym = $1->sym;
            } else {
                $$->sym = newtemp();
            }

            if ( $1->type == tableitem_e) {
                expr* val = emit_iftableitem($1);
                emit(assign, val, NULL, $$, 0, yylineno);
                emit(sub, val, newexpr_constnum(1), val, 0, yylineno);
                emit(tablesetelem, $1->index, val, $1, 0, yylineno);
            } else {
                emit(assign, $1, NULL, $$, 0, yylineno);
                emit(sub, $1, newexpr_constnum(1), $1, 0, yylineno);
            }
        }
        | primary { cout << "primary -> term" <<endl; $$ = $1;}
        ;

assignexpr: lvalue {if( $1 != NULL) {if($1->sym->type == LIB_FUNCTION || $1->sym->type == USERFUNCTION) symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$1->sym->name+" is declared as a function, forbidden action =");} } EQUAL expr { cout << "lvalue EQUAL expr -> assignexpr"<<endl;   
                assert($4);
                if ($1->type == tableitem_e) {
                    emit(tablesetelem, $1->index, $4, $1, 0, yylineno);
                    $$ = emit_iftableitem($1);
                    $$->type = assignexpr_e;
                } else {
                    if ($4->type == boolexpr_e && !$4->evaluated) shortCircuitEval($4);
                    emit(assign, $4, NULL, $1,0,yylineno);
                    
                    $$ = newexpr(assignexpr_e);
                    $$->sym = newtemp();
                    /*if (istempexpr($4)) { //dont know if i want to reuse temp here
                        $$->sym = $4->sym;
                    } else {
                        $$->sym = newtemp();
                    }*/
                    
                    emit(assign,$1,NULL,$$,0,yylineno);
                }
            }
            ;

primary:    lvalue {cout << "lvalue -> primary"<<endl; $$ = emit_iftableitem($1);}
            | call {cout << "call -> primary"<<endl; }
            | objectdef {cout << "objectdef -> primary"<<endl;}
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS {cout << "LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS -> primary" <<endl; 
                $$ = newexpr(programfunc_e);
                $$->sym = $2->sym;
            }
            | const {cout << "const -> primary" <<endl; $$ = $1;}
            ;

lvalue:     ID {   cout << "ID -> lvalue"<<endl;
                   if (symbolTable->lookEverywhere($1,SCOPE) == NULL && !RETURNEXPR) {
                        SymbolTableEntry* symbol = new SymbolTableEntry($1, SCOPE ? LOCALVAR : GLOBAL, var_s, SCOPE, yylineno, true);
                        symbolTable->insert(symbol); 
                        $$ = newexpr(var_e);
                        $$->sym = symbol;
                        //incurrscopeoffset();
                    }   
                    else {
                        SymbolTableEntry* tmp = symbolTable->lookEverywhere($1,SCOPE);
                        if (tmp != NULL) {
                            if (tmp->type == USERFUNCTION || tmp->scope == 0) $$ = lvalue_expr(tmp);
                            else {
                                int i;
                                for (i=vec.size()-1; vec.at(i)!=FUNCT && i != 0; i--) {
                                    
                                }
                                
                                if (tmp->scope >= i)
                                    $$ = lvalue_expr(tmp);
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
                        $$ = lvalue_expr(symbolTable->lookUp($2,0));
                    }
                    else {
                        SymbolTableEntry* symbol = new SymbolTableEntry($2, GLOBAL, var_s, SCOPE, yylineno, true);
                        symbolTable->insert(symbol);
                        $$ = lvalue_expr(symbol);
                        //incurrscopeoffset();
                    }
                }
                else {
                    SymbolTableEntry* symbol = new SymbolTableEntry($2, LOCALVAR, var_s, SCOPE, yylineno, true);
                    symbolTable->insert(symbol);
                    $$ = lvalue_expr(symbol);
                    //incurrscopeoffset();
                }
            }
            | DOUBLECOLON ID { cout << "DOUBLECOLON ID -> lvalue"<<endl;

                if(! ($$ = lvalue_expr(symbolTable->lookUp($2, 0)))){
                    symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+$2+" undefined variable/function");
                } 
            }
            | member { cout << "member -> lvalue"<<endl; }
            | tableitem { cout << "tableitem -> lvalue"<<endl; $$ = $1;}
            ;

tableitem:  lvalue DOT ID { 
                cout << "lvalue DOT ID -> member"<<endl;
                $$ = member_item($1, $3);
            }
            | lvalue LEFT_BRACKET expr {if ($3->type == boolexpr_e && !$3->evaluated) shortCircuitEval($3);} RIGHT_BRACKET { 
                cout << "lvalue LEFT_BRACKET expr RIGHT_BRACKET -> member"<<endl;
                $1 = emit_iftableitem($1);
                $$ = newexpr(tableitem_e);
                $$->sym = $1->sym;
                $$->index = $3;
                }
            ;

tablemake:  LEFT_BRACKET {tableInstansiation = 1; tableitems.clear();} elist RIGHT_BRACKET {
                tableInstansiation = 0;
                cout << "LEFT_BRACKET elist RIGHT_BRACKET -> objectdef"<<endl;
                expr* t = newexpr(newtable_e);
                //t->sym = newtemp();
                //t->next = tableitems.at(0);
                emit(tablecreate, NULL, NULL, t, 0, yylineno);
                
                if (!tableitems.empty()) {
                    int flag = 0;
                    for (int j = 0; j < tableitems.size() && flag == 0; j++) {
                        if (istempexpr(tableitems.at(j))) {
                            flag = 1;
                            t->sym = tableitems.at(j)->sym;
                        } 
                    }

                    if (flag == 0) t->sym = newtemp();

                    t->next = tableitems.at(0);
                    emit(tablesetelem, newexpr_constnum(0), tableitems[0], t, 0, yylineno);
                    for (int i = 1; i < tableitems.size(); i++) {
                        emit(tablesetelem, newexpr_constnum(i), tableitems.at(i), t, 0, yylineno);
                        tableitems.at(i-1)->next = tableitems.at(i);
                    }
                } else {
                    t->sym = newtemp();
                }
                tableitems.clear();
                $$ = t;
            }
            | LEFT_BRACKET indexed RIGHT_BRACKET {
                cout << "LEFT_BRACKET indexed RIGHT_BRACKET -> objectdef"<<endl;
                expr* t = newexpr(newtable_e);
                t->sym = newtemp();
                emit(tablecreate, NULL, NULL, t, 0, yylineno);
                for(int i=0; i<pairA.size(); i++)
                    emit(tablesetelem, pairA.at(i), pairB.at(i), t, 0, yylineno);
                pairA.clear();
                pairB.clear();
                $$ = t;
            }
            ;

member:     call DOT ID { cout << "call DOT ID -> member"<<endl;
                $$ = member_item($1, $3);
            }
            | call LEFT_BRACKET expr{if ($3->type == boolexpr_e && !$3->evaluated) shortCircuitEval($3);} RIGHT_BRACKET { cout << "call LEFT_BRACKET expr RIGHT_BRACKET -> member"<<endl;
                $1 = emit_iftableitem($1);
                $$ = newexpr(tableitem_e);
                $$->sym = $1->sym;
                $$->index = $3;
            }
            ;
            
call:       call {functionCall = 1;} LEFT_PARENTHESIS {tableitems.clear();} elist RIGHT_PARENTHESIS { cout << "call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS -> call" << endl; functionCall = 0;
                $1 = emit_iftableitem($1);
                for (int i = tableitems.size()-1; i>=0; i--) {
                    emit(param,tableitems.at(i),NULL,NULL,0,yylineno);
                }
                tableitems.clear();
                expr* e = newexpr(var_e);
                e->sym = newtemp();
                $$ = e;
                emit(call,$1,NULL,NULL,0,yylineno);
                emit(getretval,NULL,NULL,e,0,yylineno);
            }
            | lvalue {functionCall = 1;} callsuffix {cout << "lvalue callsuffix -> call"<<endl;
              expr* lvalueName  = $1; 
              if (doubleDotEncountered) $1 = member_item($1, $3);
              $1 = emit_iftableitem($1);
        
              for (int i = tableitems.size()-1; i>=0; i--) {
                emit(param,tableitems.at(i),NULL,NULL,0,yylineno);
              }
              tableitems.clear(); 

              if (doubleDotEncountered) {
                emit(param, lvalueName, NULL, NULL, 0, yylineno);  
                doubleDotEncountered = false;
              }

              expr* e = newexpr($1->type);
              e->sym = newtemp();
              $$ = e;
              emit(call,$1,NULL,NULL,0,yylineno);
              emit(getretval,NULL,NULL,e,0,yylineno);
              functionCall = 0;
            }
            | LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS {functionCall = 1; tableitems.clear();} elist RIGHT_PARENTHESIS {
                for (int i = tableitems.size()-1; i>=0; i--) {
                    emit(param,tableitems.at(i),NULL,NULL,0,yylineno);
                }
                tableitems.clear();
                cout << "LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS -> call"<<endl; functionCall = 0;
            }//i had put in the first LEFT_PARENTHESIS insted of LEFT i had put RIGHT
            ;

callsuffix: normcall { cout << "normvall -> callsuffix" <<endl;}
            | methodcall {cout << "methodcall -> callsuffix" <<endl; doubleDotEncountered = true; $$  = $1; }
            ;

normcall:   LEFT_PARENTHESIS{tableitems.clear();} elist RIGHT_PARENTHESIS {cout << "LEFT_PARENTHESIS elist RIGHT_PARENTHESIS -> normcall" <<endl;
    
            }
            ;

methodcall: DOUBLEDOT ID LEFT_PARENTHESIS {tableitems.clear();} elist RIGHT_PARENTHESIS {cout << "DOUBLEDOT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS -> methodcall"<<endl;
               $$ = $2;
            }
            ;

elist:      expr {if ($1->type == boolexpr_e && !$1->evaluated) shortCircuitEval($1);} exprs { cout << "expr exprs -> elist"<<endl;
                tableitems.insert(tableitems.begin(), $1);
                //if (functionCall) emit(param,$1,NULL,NULL,0,yylineno);
            }
            | /*empty*/ {cout << "empty -> elist"<<endl; $$ = NULL; }
            ;

exprs:      COMMA expr {if ($2->type == boolexpr_e && !$2->evaluated) shortCircuitEval($2);} exprs { cout << "COMMA expr exprs -> exprs"<<endl;
                tableitems.insert(tableitems.begin(), $2);
                //if (functionCall) emit(param,$2,NULL,NULL,0,yylineno);
            }
            | /*empty*/
            ;

objectdef:  tablemake
            ;

indexed:    indexedelem indexedelems {cout << "indexedelem indexedelems -> indexed"<<endl;} //there was an empty line here that was causing a reduce/reduce error
            ;

indexedelems:   COMMA indexedelem indexedelems {cout << "COMMA indexedelem indexedelems -> indexedelems"<<endl;}
                | /*empty*/ {cout << "empty -> indexedelems" <<endl;}
                ;

indexedelem:    LEFT_CURLY_BRACKET expr {if ($2->type == boolexpr_e && !$2->evaluated) shortCircuitEval($2);} COLON expr {if ($5->type == boolexpr_e && !$5->evaluated) shortCircuitEval($5);} RIGHT_CURLY_BRACKET {cout << "LEFT_CURLY_BRACKET expr COLON expr RIGHT_CURLY_BRACKET -> indexedelem"<<endl;                    
                    pairA.push_back($2);
                    pairB.push_back($5);
                }
                ;

block:          LEFT_CURLY_BRACKET { //enterscopespace(); resetscopespace(); 
                    if (!insideAFunction) { 
                        SCOPE++; 
                        vec.push_back(BLOCK); 
                    } else {
                        insideAFunction = false;
                    } 
                } 
                stmts RIGHT_CURLY_BRACKET { 
                    if (vec.back() == BLOCK) { 
                        //exitscopespace();
                        symbolTable->hide(SCOPE);
                        SCOPE--;
                        vec.pop_back();
                    } /*else if (vec.back() == FUNCT ) {
                        exitscopespace(); 
                        exitscopespace();
                    } */
                    cout << "LEFT_CURLY_BRACKET stmts RIGHT_CURLY_BRACKET -> block"<<endl;
                }
                ;

funcdef:            funcprefix funcargs funcbody {
                                                    $$=$1; 
                                                    $$->sym->localstotal = $3;
                                                    if(returnLabel.back()){patchlabel(returnLabel.back()+1,nextquad()+1);}
                                                    emit(funcend, NULL, NULL, $1,0,yylineno);
                                                    patchlabel($$->sym->funcAddr-1,nextquad()+1); //patchlabel($$->sym->funcAddr,nextquad()+1);
                                                    returnLabel.pop_back();
                                                    functCounter--;
                                                    if(!contlist.empty() && !breaklist.empty()){
                                                        if(contlist.back()!=-10 || breaklist.back()!=-10)  symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": breaklist or contlist failed");
                                                        else{
                                                            loopActive=true;
                                                            contlist.pop_back();
                                                            breaklist.pop_back();
                                                        }
                                                    }
                    }
                                        
funcprefix:          FUNCTION funcname{
                            if($2) symbolTable->insert(tmpFunct = new SymbolTableEntry($2, USERFUNCTION, programfunc_s, SCOPE, yylineno, true));
                            else symbolTable->insert(tmpFunct= new SymbolTableEntry("_f"+to_string(FUNCTNUM++), USERFUNCTION, programfunc_s,SCOPE, yylineno, true));
                            $$= lvalue_expr(tmpFunct);
                            emit(jump, NULL, NULL, NULL,0,yylineno);
                            tmpFunct->funcAddr = nextquad()+1; //tmpFunct->funcAddr = nextquad()
                            emit(funcstart, NULL, NULL, $$,0,yylineno);
                            enterscopespace(); 
                            resetformalargspace(); 
                            if(loopActive) {
                                breaklist.push_back(-10);
                                contlist.push_back(-10);
                                loopActive=false;
                            }
                    }

funcargs:          LEFT_PARENTHESIS {insideAFunction = true;  
                                    SCOPE++; 
                                    vec.push_back(FUNCT);
                                    }
                    idlist RIGHT_PARENTHESIS {  
                                        functCounter++;
                                        returnLabel.push_back(0);
                                        if(functCounter>1){ offsetStack.push_back(functionLocalOffset); }
                                        enterscopespace(); 
                                        resetfunclocalspace();
                                        }


funcbody:           block{  vec.pop_back(); 
                            symbolTable->hide(SCOPE); 
                            SCOPE--; 
                            tmpFunct = NULL;
                            $$ = currscopeoffset(); 
                            exitscopespace();
                            exitscopespace();
                            if(functCounter>1) {
                                    functionLocalOffset= offsetStack.back();
                                    offsetStack.pop_back();
                             }
                        }


funcname:           ID {$$=$1; }
                    | /*empty*/ {$$ = NULL;}

const:          INTEGER {cout <<"INTEGER -> const"<<endl;
                    $$ = newexpr(constnum_e);
                    $$->numConst= $1;
                } 
                | FLOAT{cout <<"FLOAT -> const"<<endl;
                    $$ = newexpr(constnum_e);
                    $$->numConst= $1;
                } 
                | STRINGG{cout <<"STRINGG -> const"<<endl;
                    $$ = newexpr(conststring_e);
                    $$->strConst= $1;
                } 
                | NILL{cout <<"NILL -> const"<<endl;
                    $$ = newexpr(nil_e);
                    
                } 
                | TRUE{cout <<"TRUE -> const"<<endl;
                    $$ = newexpr(constbool_e);
                    $$->boolConst= true;
                } 
                | FALSE {cout <<"FALSE -> const"<<endl;
                    $$ = newexpr(constbool_e);
                    $$->boolConst= false;
                } ;

idlist:         ID { SymbolTableEntry* tmparg; symbolTable->insert(tmparg = new SymbolTableEntry($1, FORMAL, var_s, SCOPE, yylineno, true)); if (tmpFunct != NULL){ tmpFunct->insertArg(tmparg); } /*incurrscopeoffset();*/} ids {cout <<"ID ids -> idlist"<<endl;}
                | /*empty*/ {cout <<"empty -> idlist"<<endl;}
                ;

ids:            COMMA ID { SymbolTableEntry* tmparg; symbolTable->insert(tmparg = new SymbolTableEntry($2, FORMAL, var_s, SCOPE, yylineno, true)); if (tmpFunct != NULL){ tmpFunct->insertArg(tmparg); } /*incurrscopeoffset();*/}ids {cout << "COMMA ID ids -> ids"<<endl;}
                | /*empty*/ {cout <<"empty -> ids"<<endl;}
                ;

ifstmt:         ifprefix stmt {
                    cout <<"IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt -> ifstmt"<<endl; 
                    patchlabel($1, nextquad()+1);
                   // patchlist($2->breaklist, nextquad()+1);
                    //patchlist($2->contlist, $1);
                }
                | ifprefix stmt elseprefix stmt{
                    cout <<"IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt ELSE stmt-> ifstmt"<<endl;
                    patchlabel($1, $3 + 1);
                    patchlabel($3, nextquad()+1);
                }
                ;

ifprefix:       IF LEFT_PARENTHESIS expr {if ($3->type == boolexpr_e && !$3->evaluated) shortCircuitEval($3); } RIGHT_PARENTHESIS {
                    emit(if_eq, $3, newexpr_constbool(1), NULL, nextquad()+3, yylineno); 
                    $$ = nextquad() +1; 
                    emit(jump, NULL, NULL, NULL, nextquad()+1, yylineno);
                }
                ;

elseprefix:     ELSE{
                    $$ = nextquad() + 1;
                    emit(jump, NULL, NULL, NULL, nextquad()+1, yylineno);
                }
                ;

whilestmt:      whilestart whilecond stmt {
                    cout <<"WHILE LEFT_PARENTHESIS expr RIGHT_PARENTHESIS stmt -> whilestmt"<<endl;
                    emit(jump, NULL, NULL, NULL, $1, yylineno);
                    patchlabel($2, nextquad()+1);
                    loopActive = false;
                    while(breaklist.back()!=-1){
                        patchlabel(breaklist.back(), nextquad()+1);
                        breaklist.pop_back();
                    }
                    breaklist.pop_back();
                    while(contlist.back()!=-1){
                        patchlabel(contlist.back(), $1);
                        contlist.pop_back();
                    }
                    contlist.pop_back();
                    if(!breaklist.empty()){ loopActive = true;}
                }
                ;

whilestart:     WHILE{ $$ = nextquad()+1; 
                    loopActive= true; 
                    breaklist.push_back(-1); 
                    contlist.push_back(-1);
                };

whilecond:      LEFT_PARENTHESIS expr {if ($2->type == boolexpr_e && !$2->evaluated) shortCircuitEval($2); } RIGHT_PARENTHESIS{
                    if ($2->type == boolexpr_e && !$2->evaluated) shortCircuitEval($2);
    
                    emit(if_eq, $2, newexpr_constbool(1), NULL, nextquad()+3, yylineno);
                    $$ = nextquad()+1;
                    emit(jump, NULL, NULL, NULL, nextquad()+1, yylineno);
                }
                ;

forstmt:        forprefix N {tableitems.clear();} elist RIGHT_PARENTHESIS N stmt N {
                    cout <<"FOR LEFT_PARENTHESIS elist SEMICOLON expr SEMICOLON elist RIGHT_PARENTHESIS stmt  -> forstmt"<<endl;
                    patchlabel($1->enter, $6 + 1); 
                    patchlabel($2, nextquad()+1);
                    
                    patchlabel($6, $1->test); 
                    patchlabel($8, $2 +1);
                    loopActive= false;
                    while(breaklist.back()!=-1){
                        patchlabel(breaklist.back(), nextquad()+1);
                        breaklist.pop_back();
                    }
                    breaklist.pop_back();
                    while(contlist.back()!=-1){
                        patchlabel(contlist.back(), $2+1);
                        contlist.pop_back();
                    }
                    contlist.pop_back();
                    if(!breaklist.empty()){ loopActive = true;}
                }
                ;

forprefix:      FOR LEFT_PARENTHESIS {tableitems.clear();} elist SEMICOLON M expr {if ($7->type == boolexpr_e && !$7->evaluated) shortCircuitEval($7); } SEMICOLON {
                    $$ = new forprefix();
                    $$->test = $6;
                    $$->enter = nextquad()+1;
                    
                    emit(if_eq, $7, newexpr_constbool(1), NULL, nextquad()+4, yylineno);
                    breaklist.push_back(-1); 
                    contlist.push_back(-1);
                    loopActive=true; 
                }
                ;


returnstmt:     RETURN { RETURNEXPR = true; } expr {if ($3->type == boolexpr_e && !$3->evaluated) shortCircuitEval($3); } SEMICOLON {  RETURNEXPR = false; 
                                                                if(functCounter){
                                                                    emit(ret,NULL,NULL,$3,0,yylineno);
                                                                    returnLabel.at(functCounter-1)= nextquad();
                                                                    emit(jump,NULL,NULL,NULL,0,yylineno);
                                                                } else  symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+"RETURN statement allowed inside functions only");
                                                                cout << "REUTRN expr SEMICOLON -> returnstmt"<<endl;}
                | RETURN SEMICOLON {if(functCounter){
                                        emit(ret,NULL,NULL,NULL,0,yylineno); 
                                        returnLabel.at(functCounter-1)= nextquad();
                                        emit(jump,NULL,NULL,NULL,0,yylineno);
                                    } else symbolTable->errors.push_back("ERROR in line "+to_string(yylineno)+": "+"RETURN statement allowed inside functions only");
                                    cout << "RETURN SEMICOLON -> returnstmt"<<endl;}


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
    if (symbolTable->errors.empty()) printQuads();
    return 0;
}

