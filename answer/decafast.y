%{
#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include "decafast-defs.h"

int yylex(void);
int yyerror(char *); 

// print AST?
bool printAST = true;

#include "default.cc"

using namespace std;

%}

%union{
    class decafAST *ast;
    std::string *sval;
 }

%token T_AND
%token T_ASSIGN
%token T_BOOLTYPE
%token T_BREAK
%token T_COMMA
%token T_CONTINUE
%token T_DIV
%token T_DOT
%token T_ELSE
%token T_EQ
%token T_EXTERN
%token T_FALSE
%token T_FOR
%token T_FUNC
%token T_GEQ
%token T_GT
%token T_IF
%token T_INTTYPE
%token T_LCB
%token T_LEFTSHIFT
%token T_LEQ
%token T_LPAREN
%token T_LSB
%token T_LT
%token T_MINUS
%token T_MOD
%token T_MULT
%token T_NEQ
%token T_NOT
%token T_NULL
%token T_OR
%token T_PACKAGE
%token T_PLUS
%token T_RCB
%token T_RETURN
%token T_RIGHTSHIFT
%token T_RPAREN
%token T_RSB
%token T_SEMICOLON
%token T_STRINGTYPE
%token T_TRUE
%token T_VAR
%token T_VOID
%token T_WHILE
%token <sval> T_ID
%token <sval> T_CHARCONSTANT
%token <sval> T_INTCONSTANT
%token <sval> T_STRINGCONSTANT

%type <ast> extern_list decafpackage

%%

start: program

program: extern_list decafpackage
    { 
    ProgramAST *prog = new ProgramAST((decafStmtList *)$1, (PackageAST *)$2); 
		if (printAST) {
			cout << getString(prog) << endl;
		}
    delete prog;
    }

extern_list: /* empty */ { decafStmtList *slist = new decafStmtList(); $$ = slist; }
    | T_EXTERN T_FUNC T_ID T_LPAREN extern_param T_RPAREN method_type T_SEMICOLON extern_list {

    }
    ;

extern_param: /* empty */ {}
    | extern_type T_COMMA extern_param {} // many
    | extern_type {} // one
    ;

extern_type: T_STRINGTYPE {}
    | method_type {}
    ;

method_type: T_VOID {}
    | type {}
    ;

type: T_INTTYPE {}
    | T_BOOLTYPE {}
    ;

decafpackage: T_PACKAGE T_ID T_LCB field_list method_list T_RCB 
    { $$ = new PackageAST(*$2, new decafStmtList(), new decafStmtList()); delete $2; }
    ;

field_list: /* empty */ {} // zero or more
    | field_decl field_list {} 
    ;

field_decl: T_VAR id_list type T_SEMICOLON {}
    | T_VAR id_list arraytype T_SEMICOLON {}
    | T_VAR T_ID type T_EQ constant T_SEMICOLON {}
    ;

id_list: T_ID T_COMMA id_list {} // one or more
    | T_ID {}
    ;

arraytype: T_LSB T_INTCONSTANT T_RSB type {}
    ;

constant: T_INTCONSTANT {}
    | T_CHARCONSTANT {}
    | T_TRUE {}
    | T_FALSE {}
    ;

method_list: /* empty */ {} // zero or more
    | T_FUNC T_ID T_LPAREN T_RPAREN method_type block method_list
    | T_FUNC T_ID T_LPAREN param_list T_RPAREN method_type block method_list
    ;

param_list: T_ID type T_COMMA param_list{} // one or more
    | T_ID type {}
    ;

block: T_LCB var_list statement_list T_RCB
    ;

var_list: /* empty */ {} // zero or more
    | T_VAR id_list type T_SEMICOLON var_list {}
    ;

statement_list: /* empty */ {} // zero or more
    | statement statement_list {}
    ;

statement: block {}
    | assign T_SEMICOLON {}
    | method_call T_SEMICOLON {}
    | T_IF T_LPAREN expr T_RPAREN block {}
    | T_IF T_LPAREN expr T_RPAREN block T_ELSE block {}
    | T_WHILE T_LPAREN expr T_RPAREN block {}
    | T_FOR T_LPAREN assign_list T_SEMICOLON expr T_SEMICOLON assign_list T_RPAREN block {}
    | T_RETURN T_SEMICOLON {}
    | T_RETURN T_LPAREN T_RPAREN T_SEMICOLON {}
    | T_RETURN T_LPAREN expr T_RPAREN T_SEMICOLON {}
    | T_BREAK T_SEMICOLON {}
    | T_CONTINUE T_SEMICOLON {}
    ;

assign_list: assign T_COMMA assign_list {} // one or more
    | assign {}
    ;

assign: lvalue T_EQ expr {}
    ;

lvalue: T_ID T_LSB expr T_RSB {}
    | T_ID {}
    ;

method_call: T_ID T_LPAREN T_RPAREN {}
    | T_ID T_LPAREN method_arg_list T_RPAREN {}
    ;

method_arg_list: method_arg T_COMMA method_arg_list {}
    | method_arg {}
    ;

method_arg: expr | T_STRINGCONSTANT {}
    ;

expr: T_ID {}
    | method_call {}
    | constant {}
    | expr bin_op expr {}
    | un_op expr {}
    | T_LPAREN expr T_RPAREN {}
    | T_ID T_LSB expr T_RSB {}
    ;

bin_op: arithmetic_op {}
    | bool_op {}
    ;

arithmetic_op: T_PLUS {}
    | T_MINUS {}
    | T_MULT {}
    | T_DIV {}
    | T_LEFTSHIFT {}
    | T_RIGHTSHIFT {}
    | T_MOD {}
    ;

bool_op: T_EQ {}
    | T_NEQ {}
    | T_LT {}
    | T_LEQ {}
    | T_GT {}
    | T_GEQ {}
    | T_AND {}
    | T_OR {}
    ;

un_op: T_NOT {}
    | T_MINUS {}
    ;

%%

int main() {
  // parse the input and create the abstract syntax tree
  int retval = yyparse();
  return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

