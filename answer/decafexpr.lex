%{

#include "decafexpr-defs.h"
#include "decafexpr.tab.h"
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

int line = 1;
int pos = 0;
static string lexeme;

void yyerror(string s) {
	cerr << "Error: " << s << "\nLexical error: line " << line << ", position " << pos+1 << endl;
}

%}

%%
  /*
    Pattern definitions for all tokens 
  */
&&							   { lexeme.assign(yytext); pos += lexeme.size(); return T_AND; }
=							   { lexeme.assign(yytext); pos += lexeme.size(); return T_ASSIGN; }
bool						   { lexeme.assign(yytext); pos += lexeme.size(); return T_BOOLTYPE; }
break						   { lexeme.assign(yytext); pos += lexeme.size(); return T_BREAK; }
,							   { lexeme.assign(yytext); pos += lexeme.size(); return T_COMMA; }
continue					   { lexeme.assign(yytext); pos += lexeme.size(); return T_CONTINUE; }
\/							   { lexeme.assign(yytext); pos += lexeme.size(); return T_DIV; }
\.							   { lexeme.assign(yytext); pos += lexeme.size(); return T_DOT; }
else						   { lexeme.assign(yytext); pos += lexeme.size(); return T_ELSE; }
==							   { lexeme.assign(yytext); pos += lexeme.size(); return T_EQ; }
extern						   { lexeme.assign(yytext); pos += lexeme.size(); return T_EXTERN; }
false						   { lexeme.assign(yytext); pos += lexeme.size(); return T_FALSE; }
for							   { lexeme.assign(yytext); pos += lexeme.size(); return T_FOR; }
func						   { lexeme.assign(yytext); pos += lexeme.size(); return T_FUNC; }
>=							   { lexeme.assign(yytext); pos += lexeme.size(); return T_GEQ; }
>							   { lexeme.assign(yytext); pos += lexeme.size(); return T_GT; }
if							   { lexeme.assign(yytext); pos += lexeme.size(); return T_IF; }
int							   { lexeme.assign(yytext); pos += lexeme.size(); return T_INTTYPE; }
\{							   { lexeme.assign(yytext); pos += lexeme.size(); return T_LCB; }
\<\<						   { lexeme.assign(yytext); pos += lexeme.size(); return T_LEFTSHIFT; }
\<=							   { lexeme.assign(yytext); pos += lexeme.size(); return T_LEQ; }
\(							   { lexeme.assign(yytext); pos += lexeme.size(); return T_LPAREN; }
\[							   { lexeme.assign(yytext); pos += lexeme.size(); return T_LSB; }
\<							   { lexeme.assign(yytext); pos += lexeme.size(); return T_LT; }
-							   { lexeme.assign(yytext); pos += lexeme.size(); return T_MINUS; }
%							   { lexeme.assign(yytext); pos += lexeme.size(); return T_MOD; }
\*							   { lexeme.assign(yytext); pos += lexeme.size(); return T_MULT; }
!=							   { lexeme.assign(yytext); pos += lexeme.size(); return T_NEQ; }
!							   { lexeme.assign(yytext); pos += lexeme.size(); return T_NOT; }
null						   { lexeme.assign(yytext); pos += lexeme.size(); return T_NULL; }
\|\|						   { lexeme.assign(yytext); pos += lexeme.size(); return T_OR; }
package						   { lexeme.assign(yytext); pos += lexeme.size(); return T_PACKAGE; }
\+							   { lexeme.assign(yytext); pos += lexeme.size(); return T_PLUS; }
\}							   { lexeme.assign(yytext); pos += lexeme.size(); return T_RCB; }
return						   { lexeme.assign(yytext); pos += lexeme.size(); return T_RETURN; }
\>\>						   { lexeme.assign(yytext); pos += lexeme.size(); return T_RIGHTSHIFT; }
\)							   { lexeme.assign(yytext); pos += lexeme.size(); return T_RPAREN; }
\]							   { lexeme.assign(yytext); pos += lexeme.size(); return T_RSB; }
;							   { lexeme.assign(yytext); pos += lexeme.size(); return T_SEMICOLON; }
string						   { lexeme.assign(yytext); pos += lexeme.size(); return T_STRINGTYPE; }
true						   { lexeme.assign(yytext); pos += lexeme.size(); return T_TRUE; }
var							   { lexeme.assign(yytext); pos += lexeme.size(); return T_VAR; }
void						   { lexeme.assign(yytext); pos += lexeme.size(); return T_VOID; }
while						   { lexeme.assign(yytext); pos += lexeme.size(); return T_WHILE; }
\'([^\\]|\\[nrtvfab\\\'"])\'	   { yylval.sval = new string(yytext); pos += yylval.sval->size(); return T_CHARCONSTANT; }
[a-zA-Z\_][a-zA-Z\_0-9]*		   { yylval.sval = new string(yytext); pos += yylval.sval->size(); return T_ID; }
[0-9]+|0[xX][0-9a-fA-F]+		   { yylval.sval = new string(yytext); pos += yylval.sval->size(); return T_INTCONSTANT; } 
\"([^\\\"\n]|\\[abtnvfr\\'\"])*\"  { yylval.sval = new string(yytext); pos += yylval.sval->size(); return T_STRINGCONSTANT; }
\/\/.*\n						   { line++; pos = 0; } // T_COMMENT ignore
[\t\r\a\v\b ]+					   { lexeme.assign(yytext); pos += lexeme.size(); } // T_WHITESPACE ignore
[\t\r\a\v\b\n ]+				   { line++; pos = 0; } // T_WHITESPACE with newline ignore
\\[^nrtvfab\\\'"]|\\		   	   { yyerror("unknown escape sequence in string constant"); return -1; }
\"[^\\\"]*\n[^\\\"]*\"			   { yyerror("newline in string constant"); return -1; }
\"[^\\\"\n]*					   { yyerror("string constant is missing closing delimiter"); return -1; }
\'[^\\][^\\\']+\'				   { yyerror("char constant length is greater than one"); return -1; }
\'[^\\][^\\\']+				   	   { yyerror("unterminated char constant"); return -1; }
\'\'			   				   { yyerror("char constant has zero width"); return -1; }
(0[xX])|(\"\\[abtnvfr\\'\"]*)	   { yyerror("unexpected character in input"); return -1; }

%%
