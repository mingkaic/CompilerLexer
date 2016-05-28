
%{

#include <iostream>
#include <cstdlib>

using namespace std;

%}

%%
  /*
    Pattern definitions for all tokens 
  */
&&							   { return 1; }
=							   { return 2; }
bool						   { return 3; }
break						   { return 4; }
,							   { return 5; }
\/							   { return 6; }
\.							   { return 7; }
else						   { return 8; }
==							   { return 9; }
extern						   { return 10; }
false						   { return 11; }
for							   { return 12; }
func						   { return 13; }
>=							   { return 14; }
>							   { return 15; }
if							   { return 16; }
int							   { return 17; }
\{							   { return 18; }
\<\<						   { return 19; }
\<=							   { return 20; }
\(							   { return 21; }
\[							   { return 22; }
\<							   { return 23; }
-							   { return 24; }
%							   { return 25; }
\*							   { return 26; }
!=							   { return 27; }
!							   { return 28; }
null						   { return 29; }
\|\|						   { return 30; }
package						   { return 31; }
\+							   { return 32; }
\}							   { return 33; }
return						   { return 34; }
\>\>						   { return 35; }
\)							   { return 36; }
\]							   { return 37; }
;							   { return 38; }
string						   { return 39; }
true						   { return 40; }
var							   { return 41; }
void						   { return 42; }
while						   { return 43; }
\'([^\\]|\\[nrtvfab\\\'"])\'   { return 44; } // T_CHARCONSTANT
\/\/.*\n						   { return 45; } // T_COMMENT
[a-zA-Z\_][a-zA-Z\_0-9]*		   { return 46; } // T_ID
[0-9]+|0[xX][0-9a-fA-F]+		   { return 47; } // T_INTCONSTANT
\"([^\\\"\n]|\\[abtnvfr\\'\"])*\"  { return 48; } // T_STRINGCONSTANT
[\t\r\a\v\b ]+				   { return 49; } // T_WHITESPACE (without newline)
[\t\r\a\v\b\n ]+			   { return 50; }
(\'\')						   { cerr << "Error: unexpected character literal in input" << endl; return -1; } // char errors
(\\[^nrtvfab\\\'"])|(\\)	   { cerr << "Error: unexpected escape character in input" << endl; return -1; } // escape char errors
(0[xX])						   { cerr << "Error: unexpected hexidecimal in input" << endl; return -1; } // 

%%

int main () {
  int token;
  string lexeme;
  while ((token = yylex())) {
    if (token > 0) {
      lexeme.assign(yytext);
	  switch(token) {
		case 1: cout << "T_AND " << lexeme << endl; break;
		case 2: cout << "T_ASSIGN " << lexeme << endl; break;
		case 3: cout << "T_BOOLTYPE " << lexeme << endl; break;
		case 4: cout << "T_BREAK " << lexeme << endl; break;
		case 5: cout << "T_COMMA " << lexeme << endl; break;
		case 6: cout << "T_DIV " << lexeme << endl; break;
		case 7: cout << "T_DOT " << lexeme << endl; break;
		case 8: cout << "T_ELSE " << lexeme << endl; break;
		case 9: cout << "T_EQ " << lexeme << endl; break;
		case 10: cout << "T_EXTERN " << lexeme << endl; break;
		case 11: cout << "T_FALSE " << lexeme << endl; break;
		case 12: cout << "T_FOR " << lexeme << endl; break;
		case 13: cout << "T_FUNC " << lexeme << endl; break;
		case 14: cout << "T_GEQ " << lexeme << endl; break;
		case 15: cout << "T_GT " << lexeme << endl; break;
		case 16: cout << "T_IF " << lexeme << endl; break;
		case 17: cout << "T_INTTYPE " << lexeme << endl; break;
		case 18: cout << "T_LCB " << lexeme << endl; break;
		case 19: cout << "T_LEFTSHIFT " << lexeme << endl; break;
		case 20: cout << "T_LEQ " << lexeme << endl; break;
		case 21: cout << "T_LPAREN " << lexeme << endl; break;
		case 22: cout << "T_LSB " << lexeme << endl; break;
		case 23: cout << "T_LT " << lexeme << endl; break;
		case 24: cout << "T_MINUS " << lexeme << endl; break;
		case 25: cout << "T_MOD " << lexeme << endl; break;
		case 26: cout << "T_MULT " << lexeme << endl; break;
		case 27: cout << "T_NEQ " << lexeme << endl; break;
		case 28: cout << "T_NOT " << lexeme << endl; break;
		case 29: cout << "T_NULL " << lexeme << endl; break;
		case 30: cout << "T_OR " << lexeme << endl; break;
		case 31: cout << "T_PACKAGE " << lexeme << endl; break;
		case 32: cout << "T_PLUS " << lexeme << endl; break;
		case 33: cout << "T_RCB " << lexeme << endl; break;
		case 34: cout << "T_RETURN " << lexeme << endl; break;
		case 35: cout << "T_RIGHTSHIFT " << lexeme << endl; break;
		case 36: cout << "T_RPAREN " << lexeme << endl; break;
		case 37: cout << "T_RSB " << lexeme << endl; break;
		case 38: cout << "T_SEMICOLON " << lexeme << endl; break;
		case 39: cout << "T_STRINGTYPE " << lexeme << endl; break;
		case 40: cout << "T_TRUE " << lexeme << endl; break;
		case 41: cout << "T_VAR " << lexeme << endl; break;
		case 42: cout << "T_VOID " << lexeme << endl; break;
		case 43: cout << "T_WHILE " << lexeme << endl; break;
		case 44: cout << "T_CHARCONSTANT " << lexeme << endl; break;
		case 45: 
			lexeme.pop_back();
			cout << "T_COMMENT " << lexeme << "\\n" << endl; 
		break;
		case 46: cout << "T_ID " << lexeme << endl; break;
		case 47: cout << "T_INTCONSTANT " << lexeme << endl; break;
		case 48: cout << "T_STRINGCONSTANT " << lexeme << endl; break;
		case 49: cout << "T_WHITESPACE " << lexeme << endl; break;
		case 50: 
			cout << "T_WHITESPACE ";
			for (size_t i = 0; i < lexeme.size(); i++) {
				if (lexeme[i] == '\n') {
					cout << "\\n"; 
				}
			}
			cout << endl; 
			break;
		default: exit(EXIT_FAILURE);
	  }
    } else {
      if (token < 0) {
		exit(EXIT_FAILURE);
      }
    }
  }
  exit(EXIT_SUCCESS);
}

