%{

/* 
    HY340 Languages and Compilers              Alpha Compiler Lexical Analysis

    Artemisia Stamataki csd4742
    Georgia Papaioannou csd4781
    Ioannis Mytakis     csd4257
*/

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <iterator>
#include <regex>
#include <string.h>
#include <assert.h>
#define YY_DECL int alpha_yylex(void* yylval)

using namespace std;

struct alpha_token_t;
alpha_token_t *TokenList = NULL; 
vector<string> ERROR_WARRNING;
int TokenNum = 0, max_comment = 0, comment_nesting = 0, first_comment, lineA, lineB;
vector<int> line_start, line_end;
string string_buff;

struct alpha_token_t {
  unsigned int     numline;
  unsigned int     numToken;
  string       content;
  string       type;
  string       category;
  struct alpha_token_t *next;
};

void print_Token_List() {
    alpha_token_t *token = TokenList;

    while(token != NULL) {

        if (token->type == "IDENT") {
            cout << token->numline << ": #" << token->numToken <<"    \""<<token->content<<"\"   " <<token->type<<"        \""<< token->category<<"\"";
        
        } else if (token->type == "STRING") {
            cout << token->numline << ": #" << token->numToken <<"    "<<token->content<<"   " <<token->type<<"        "<< token->category;
       
        } else if (token->category == "LINE_COMMENT") {
            cout << token->numline << ": #" << token->numToken <<"    \"\"   " <<token->type<<"        "<< token->category;

        } else if (token->category == "BLOCK_COMMENT" || token->category == "NESTED_COMMENT" || token->category == "MULTILINE_COMMENT") {
            cout << token->numline << ": #" << token->numToken <<"    \""<<token->numline<<" - "<<token->content<<"\"   " <<token->type<<"        "<< token->category;
            
        } else {
            cout << token->numline << ": #" << token->numToken <<"    \""<<token->content<<"\"   " <<token->type<<"        "<< token->category;
        }

        if (token->type == "COMMENT" || token->type == "OPERATOR" || token->type == "KEYWORD" || token->type == "PUNCTUATION") cout << "   <-enumerated"<< endl;
        if (token->type == "IDENT" || token->type == "STRING") cout << "   <-char*"<< endl;
        if (token->type == "CONST_INT") cout << "   <-integer"<< endl;
        if (token->type == "CONST_REAL") cout << "   <-float" << endl;

        token = token->next;
    }
}

alpha_token_t *create_Alpha_Token(string content, string type, string category, unsigned int numToken, unsigned int numLine) {
    alpha_token_t *token = new alpha_token_t;

    assert(token != NULL);
    token->content = content;
    token->type = type;
    token->category = category;
    token->numToken = numToken;
    token->numline = numLine;
    token->next = NULL;
    
    return token;
}

void insert_Alpha_Token(alpha_token_t **head, alpha_token_t *token) {
    assert(token != NULL);

    if (*head == NULL) {
        *head = token;
    } else {
        alpha_token_t *lastToken = *head;
        while (lastToken->next != NULL) {
            lastToken = lastToken->next;
        }
        lastToken->next = token;  
    }
}

%}

%option yylineno
%option noyywrap

if					"if"
else				"else"
while				"while"
for					"for"
return				"return"
break				"break"
continue			"continue"
and					"and"
not					"not"
or					"or"
local				"local"
true				"true"
false				"false"
nill				"NULL"
function			"function"
equal				"="
addition			"+"
subtraction			"-"
multiplication		"*"
division			"/"
mode				"%"
isEqual				"=="
notEqual			"!="
plusOne				"++"
minusOne			"--"
moreThan			">"
lessThan			"<"
moreORequal			">="
lessORequal			"<="
integer				[0-9]+
float				[0-9]+"."[0-9]+ 
left_curly_bracket	"{"
right_curly_bracket	"}"
left_bracket	   	"["
right_bracket		"]"
left_parenthesis	"("
right_parenthesis	")"
semicolon			";"
comma				","
colon				":"
doubleColon			"::"
dot					"."
doubleDot			".."
name				[A-Za-z][A-Za-z_0-9]*             
comment1			"//".*
whitespace			[ \t\n]

%x COMMENT  
%x STRING
 
%%

{if}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "IF", ++TokenNum, yylineno) ); }
{else}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "ELSE", ++TokenNum, yylineno) ); }
{while}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "WHILE", ++TokenNum, yylineno) ); }
{for}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "FOR", ++TokenNum, yylineno) ); }
{return}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "RETURN", ++TokenNum, yylineno) ); }
{break}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "BREAK", ++TokenNum, yylineno) ); }
{continue}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "CONTINUE", ++TokenNum, yylineno) ); }
{and}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "AND", ++TokenNum, yylineno) ); }
{not}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "NOT", ++TokenNum, yylineno) ); }
{or}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "OR", ++TokenNum, yylineno) ); }
{local}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "LOCAL", ++TokenNum, yylineno) ); }
{true}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "TRUE", ++TokenNum, yylineno) ); }
{false}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "FALSE", ++TokenNum, yylineno) ); }
{nill}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "NULL", ++TokenNum, yylineno) ); }
{function}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "KEYWORD", "FUNCTION", ++TokenNum, yylineno) ); }	
{equal}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "EQUAL", ++TokenNum, yylineno) ); }
{addition}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "PLUS", ++TokenNum, yylineno) ); }
{subtraction}			{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "MINUS", ++TokenNum, yylineno) ); }
{multiplication}		{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "MUL", ++TokenNum, yylineno) ); }
{division}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "DIV", ++TokenNum, yylineno) ); }
{mode}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "MOD", ++TokenNum, yylineno) ); }
{isEqual}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "EQUAL_EQUAL", ++TokenNum, yylineno) ); }
{notEqual}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "NOT_EQUAL", ++TokenNum, yylineno) ); }
{plusOne}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "PLUS_PLUS", ++TokenNum, yylineno) ); }
{minusOne}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "MINUS_MINUS", ++TokenNum, yylineno) ); }
{moreThan}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "GREATER", ++TokenNum, yylineno) ); }
{lessThan}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "LESS", ++TokenNum, yylineno) ); }
{moreORequal}			{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "GREATER_EQUAL", ++TokenNum, yylineno) ); }
{lessORequal}			{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "OPERATOR", "LESS_EQUAL", ++TokenNum, yylineno) ); }
{integer}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "CONST_INT", yytext, ++TokenNum, yylineno) ); }
{float}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "CONST_REAL", yytext, ++TokenNum, yylineno) ); }
{left_curly_bracket}	{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "LEFT_CURLY_BRACE", ++TokenNum, yylineno) ); }
{right_curly_bracket} 	{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "RIGHT_CURLY_BRACE", ++TokenNum, yylineno) ); }
{left_bracket}			{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "LEFT_BRACE", ++TokenNum, yylineno) ); }
{right_bracket}			{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "RIGHT_BRACE", ++TokenNum, yylineno) ); }
{left_parenthesis}		{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "LEFT_PARENTHESIS", ++TokenNum, yylineno) ); }
{right_parenthesis}		{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "RIGHT_PARENTHESIS", ++TokenNum, yylineno) ); }
{semicolon}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "SEMICOLON", ++TokenNum, yylineno) ); }
{comma}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "COMMA", ++TokenNum, yylineno) ); }
{colon}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "COLON", ++TokenNum, yylineno) ); }
{doubleColon}			{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "DOUBLE_COLON", ++TokenNum, yylineno) ); }
{dot}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "DOT", ++TokenNum, yylineno) ); }
{doubleDot}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "PUNCTUATION", "DOUBLE_DOT", ++TokenNum, yylineno) ); }
{name}					{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "IDENT", yytext, ++TokenNum, yylineno) ); }
{comment1}				{ insert_Alpha_Token(&TokenList, create_Alpha_Token(yytext, "COMMENT", "LINE_COMMENT", ++TokenNum, yylineno) ); }
{whitespace}			{}


"/*"             { BEGIN(COMMENT); lineA=yylineno; max_comment=1;}
<COMMENT>{
  "/*"           { line_start.push_back(yylineno); ++comment_nesting; ++max_comment; }

  "*"+"/"        { if (comment_nesting) {
                    --comment_nesting;  
                    if (comment_nesting > 1) {
                        line_end.insert(line_end.begin(), yylineno);
                    } else {
                        line_end.push_back(yylineno);
                    }
                   }
                   else{ BEGIN(INITIAL); 
                   lineB=yylineno; 
                   if(max_comment==1) {
                        insert_Alpha_Token(&TokenList, create_Alpha_Token(to_string(lineB), "COMMENT", "BLOCK_COMMENT", ++TokenNum, lineA) );
                    } else if(max_comment>1) {
                        for (int i = 0; i < max_comment-1; i++) insert_Alpha_Token(&TokenList, create_Alpha_Token(to_string(line_end.at(i)), "COMMENT", "NESTED_COMMENT", ++TokenNum, line_start.at(i)) );
                        insert_Alpha_Token(&TokenList, create_Alpha_Token(to_string(lineB), "COMMENT", "BLOCK_COMMENT", ++TokenNum, lineA) );
                    } 
                    line_start.clear();
                    line_end.clear();
                } 
            }

    .            {}
  \n             ;

 <<EOF>>       { ERROR_WARRNING.push_back("ERROR: comment in line: " + to_string(lineA) + " doesnt close"); return 0; }
}

"\""             { BEGIN(STRING); lineA=yylineno; string_buff="\"";}
<STRING>{
  "\""           { BEGIN(INITIAL); string_buff=string_buff+"\""; insert_Alpha_Token(&TokenList, create_Alpha_Token(string_buff, "STRING", string_buff, ++TokenNum, lineA) ); }
   
   "\\"[^(n|t|"\\")] {string_buff=string_buff+yytext; ERROR_WARRNING.push_back("WARRNING: string in line: "+ to_string(lineA)+" contains invalid escape character '"+ yytext[1]+"' ");}
   "\\n"        {string_buff=string_buff+'\n';};
   "\\t"        {string_buff=string_buff+'\t';};
   "\\\\"       {string_buff=string_buff+'\\';}
   "\\\""       {string_buff=string_buff+'\"';}

    
  .             {string_buff = string_buff+yytext;}
  \n            {string_buff=string_buff+ '\n';};
  <<EOF>>       { ERROR_WARRNING.push_back("ERROR: string in line: "+ to_string(lineA)+" doesn't close"); return 0; }
}

.		{ ERROR_WARRNING.push_back("ERROR: character '"+ string(yytext) +"' in line: "+ to_string(yylineno) +" is undefined"); }

%%

int main(int argc, char **argv){

	if(argc>1) {
		if(!(yyin=fopen(argv[1], "r"))){
			fprintf(stderr, "Cannot read file: %s\n", argv[1]);
			return 1;
		}
	}
	else {
		yyin=stdin;
    }
    
	alpha_yylex(TokenList); 

    if (TokenList != NULL) cout << "--------------------------      Lexical Analysis      --------------------------" << endl << endl;
    print_Token_List();

    for (vector<string>::iterator it = ERROR_WARRNING.begin() ; it != ERROR_WARRNING.end(); ++it) {
        cout << *it << endl;
    }

	return 0;
}