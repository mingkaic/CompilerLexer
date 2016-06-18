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

#include "decafast.cc"

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
%type <ast> extern_param extern_type method_type type
%type <ast> field_list method_list 
%type <ast> field_decl id_list constant

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
    | T_EXTERN T_FUNC T_ID T_LPAREN T_RPAREN method_type T_SEMICOLON extern_list {
        string* id = $3;
        terminalAST* methodT = (terminalAST*) $6;
        ExternAST* ext = new ExternAST(*id, methodT, NULL);
        delete id;
        $$ = ext;
    }
    | T_EXTERN T_FUNC T_ID T_LPAREN extern_param T_RPAREN method_type T_SEMICOLON extern_list {
        string* id = $3;
        terminalAST* methodT = (terminalAST*) $7;
        decafStmtList* ex_list = (decafStmtList*) $5;
        ExternAST* ext = new ExternAST(*id, methodT, ex_list);
        delete id;
        $$ = ext;
    }
    ;

extern_param: extern_type T_COMMA extern_param { // one to many
        decafStmtList* ex_list = (decafStmtList*) $3;
        // assert that ex_list != NULL
        ex_list->push_front($1);
        $$ = ex_list;
    } 
    | extern_type {
        decafStmtList* ex_list = new decafStmtList();
        ex_list->push_back($1);
        $$ = ex_list;
    }
    ;

extern_type: T_STRINGTYPE { $$ = new vardefAST("StringType"); }
    | method_type { $$ = new vardefAST($1); }
    ;

method_type: T_VOID { $$ = new terminalAST("VoidType"); }
    | type { $$ = $1; }
    ;

type: T_INTTYPE { $$ = new terminalAST("IntType"); }
    | T_BOOLTYPE { $$ = new terminalAST("BoolType"); }
    ;

decafpackage: T_PACKAGE T_ID T_LCB field_list method_list T_RCB {
        decafStmtList* fields = (decafStmtList*) $4;
        decafStmtList* stmts = NULL; // (decafStmtList*) $5;
        $$ = new PackageAST(*$2, fields, stmts); 
        delete $2; 
    }
    ;

field_list: /* empty */ { $$ = new decafStmtList(); } // zero or more
    | field_decl field_list {
        decafStmtList* fields = (decafStmtList*) $2;
        fields->push_front($1);
        $$ = fields;
    } 
    ;

field_decl: T_VAR id_list type T_SEMICOLON {
        decafStmtList* res = new decafStmtList();
        temporaryAST* ids = (temporaryAST*) $2;
        terminalAST* t = (terminalAST*) $3;
        for (list<string*>::iterator it = ids->types.begin(); it != ids->types.end(); it++) {
            res->push_back(new FieldDecl(**it, new terminalAST(*t)));
        }
        delete t;
        delete ids;
        $$ = res;
    }
    | T_VAR T_ID type T_SEMICOLON { 
        // for some reason, bison has problems with single ID id_list followed by type
        $$ = new FieldDecl(*$2, $3);
    }
    | T_VAR id_list T_LSB T_INTCONSTANT T_RSB type T_SEMICOLON { 
        decafStmtList* res = new decafStmtList();
        temporaryAST* ids = (temporaryAST*) $2;
        terminalAST* t = (terminalAST*) $6;
        for (list<string*>::iterator it = ids->types.begin(); it != ids->types.end(); it++) {
            res->push_back(new FieldDecl(**it, new terminalAST(*t), *$4));
        }
        delete t;
        delete ids;
        $$ = res;
    }
    | T_VAR T_ID type T_ASSIGN constant T_SEMICOLON { 
        decafStmtList* res = new decafStmtList();
        res->push_back(new FieldDecl(*$2, $3, (constantAST*) $5));
        delete $2;
        $$ = res;
    }
    ;

id_list: T_ID {
        temporaryAST* res = new temporaryAST(); 
        res->types.push_back($1);
        $$ = res;
    }
    | id_list T_COMMA T_ID { // one or more
        temporaryAST* res = (temporaryAST*) $1;
        res->types.push_back($3);
        $$ = res;
    }
    ;

constant: T_INTCONSTANT { $$ = new constantAST("NumberExpr", *$1); delete $1; }
    | T_CHARCONSTANT { $$ = new constantAST("CharacterExpr", *$1); delete $1; }
    | T_TRUE { $$ = new constantAST("BoolExpr", "true"); }
    | T_FALSE { $$ = new constantAST("BoolExpr", "false"); }
    ;

method_list: /* empty */ { $$ = new decafStmtList(); } // zero or more
    | T_FUNC T_ID T_LPAREN T_RPAREN method_type block method_list {}
    | T_FUNC T_ID T_LPAREN param_list T_RPAREN method_type block method_list {}
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

assign: lvalue T_ASSIGN expr {}
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

