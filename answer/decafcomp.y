%{
#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include "decafcomp-defs.h"

int yylex(void);
int yyerror(char *);

using namespace std;

// this global variable contains all the generated code
static llvm::LLVMContext &Context = llvm::getGlobalContext();
static llvm::Module *TheModule;

// this is the method used to construct the LLVM intermediate code (IR)
static llvm::IRBuilder<> Builder(llvm::getGlobalContext());

// the calls to getGlobalContext() in the init above and in the
// following code ensures that we are incrementally generating
// instructions in the right order

// dummy main function
// should be replaced with actual codegen for the main method 
// using the full Decaf grammar
static llvm::Function *TheFunction = 0;

// we have to create a main function 
llvm::Function *gen_main_def() {
  // create the top-level definition for main
  llvm::FunctionType *FT = llvm::FunctionType::get(llvm::IntegerType::get(llvm::getGlobalContext(), 32), false);
  llvm::Function *TheFunction = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, "main", TheModule);
  if (TheFunction == 0) {
    throw runtime_error("empty function block"); 
  }
  // Create a new basic block which contains a sequence of LLVM instructions
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(llvm::getGlobalContext(), "entry", TheFunction);
  // All subsequent calls to IRBuilder will place instructions in this location
  Builder.SetInsertPoint(BB);
  return TheFunction;
}

#include "decafcomp.cc"

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
%type <ast> extern_param extern_type method_type decaf_type
%type <ast> field_list method_list
%type <ast> multivar id_list constant
%type <ast> param_list block var_list statement_list statement
%type <ast> assign_list assign method_call method_arg_list method_arg
%type <ast> expr and_level
%type <ast> comp_level comp_op
%type <ast> plus_level plus_op
%type <ast> mult_level mult_op 
%type <ast> not_level to_endpoint

%%

start: program

program: extern_list decafpackage {
        ProgramAST *prog = new ProgramAST((decafStmtList *)$1, (PackageAST *)$2);
        try {
            prog->Codegen();
        }
        catch (std::runtime_error &e) {
            cout << "semantic error: " << e.what() << endl;
            exit(EXIT_FAILURE);
        }
        delete prog;
    }

extern_list: /* empty */ { $$ = new decafStmtList(); }
    | T_EXTERN T_FUNC T_ID T_LPAREN T_RPAREN method_type T_SEMICOLON extern_list {
        string* id = $3;
        ExternAST* ext = new ExternAST(*id, (TypeSym*) $6, NULL);
        delete id;
        decafStmtList* l = (decafStmtList*) $8;
        l->push_front(ext);
        $$ = l;
    }
    | T_EXTERN T_FUNC T_ID T_LPAREN extern_param T_RPAREN method_type T_SEMICOLON extern_list {
        string* id = $3;
        decafStmtList* ex_list = (decafStmtList*) $5;
        ExternAST* ext = new ExternAST(*id, (TypeSym*) $7, ex_list);
        delete id;
        decafStmtList* l = (decafStmtList*) $9;
        l->push_front(ext);
        $$ = l;
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

extern_type: T_STRINGTYPE { $$ = new VarDecl(V_STRING); }
    | decaf_type { $$ = new VarDecl((TypeSym*) $1); }
    ;

method_type: T_VOID { $$ = new TypeSym(V_VOID); }
    | decaf_type { $$ = $1; }
    ;

decaf_type: T_INTTYPE { $$ = new TypeSym(V_INT); }
    | T_BOOLTYPE { $$ = new TypeSym(V_BOOL); }
    ;

decafpackage: T_PACKAGE T_ID T_LCB field_list method_list T_RCB {
        decafStmtList* fields = (decafStmtList*) $4;
        decafStmtList* stmts = (decafStmtList*) $5;
        $$ = new PackageAST(*$2, fields, stmts); 
        delete $2; 
    }
    ;

field_list: /* empty */ { $$ = new decafStmtList(); } // zero or more
    | field_list T_VAR T_ID decaf_type T_SEMICOLON {
        decafStmtList* var_list = (decafStmtList*) $1;
        VarDecl* var = new VarDecl(*$3);
        var->Type = (TypeSym*) $4;
        var_list->push_back(new GlobalVar(var));
        $$ = var_list;
    }
    | field_list multivar {
        decafStmtList* globals = (decafStmtList*) $1;
        decafStmtList* mlist = (decafStmtList*) $2;

        for (list<decafAST*>::iterator vit = mlist->begin(); 
            vit != mlist->end(); vit++) {
            VarDecl* var = (VarDecl*) *vit;
            globals->push_back(new GlobalVar(var));
        }
        $$ = globals;
    }
    | field_list T_VAR id_list T_LSB T_INTCONSTANT T_RSB decaf_type T_SEMICOLON { 
        decafStmtList* globals = (decafStmtList*) $1;
        decafStmtList* mlist = (decafStmtList*) $3;
        TypeSym* var_type = (TypeSym*) $7;

        for (list<decafAST*>::iterator vit = mlist->begin(); 
            vit != mlist->end(); vit++) {
            VarDecl* var = (VarDecl*) *vit;
            var->Type = new TypeSym(*var_type);
            NumLit* arrsize = new NumLit(*$5);
            globals->push_back(new GlobalVar(var, arrsize));
        }
        delete var_type;
        delete $5;
        $$ = globals;
    }
    | field_list T_VAR T_ID decaf_type T_ASSIGN constant T_SEMICOLON {
        decafStmtList* globals = (decafStmtList*) $1;
        globals->push_back(new GlobalVar(*$3, (TypeSym*) $4, $6));
        delete $3;
        $$ = globals;
    }
    ;

var_list: /* empty */ { $$ = new decafStmtList(); } // zero or more
    | var_list multivar {
        decafStmtList* vars = (decafStmtList*) $1;
        vars->push_back($2);
        $$ = vars;
    }
    ;

multivar: T_VAR id_list decaf_type T_SEMICOLON {
        decafStmtList* var_list = (decafStmtList*) $2;
        TypeSym* var_type = (TypeSym*) $3;

        for (list<decafAST*>::iterator vit = var_list->begin(); 
            vit != var_list->end(); vit++) {
            VarDecl* var = (VarDecl*) *vit;
            var->Type = new TypeSym(*var_type);
        }
        delete var_type;
        $$ = var_list;
    }
    ;

id_list: T_ID { // one or more
        decafStmtList* v_list = new decafStmtList();
        VarDecl* var = new VarDecl(*$1);
        v_list->push_back(var);
        $$ = v_list;
    }
    | id_list T_COMMA T_ID {
        decafStmtList* v_list = (decafStmtList*) $1;
        VarDecl* var = new VarDecl(*$3);
        v_list->push_back(var);
        $$ = v_list;
    }
    ;

constant: T_INTCONSTANT { $$ = new NumLit(*$1); delete $1; }
    | T_CHARCONSTANT {
        try {
            string strrep = ConvertEsc(*$1);
            int val = strrep[1];
            $$ = new NumLit(val); 
            delete $1;
        } catch (string e) {
            yyerror(e.c_str());
            return -1;
        }
    }
    | T_TRUE { $$ = new BoolLit(true); }
    | T_FALSE { $$ = new BoolLit(false); }
    ;

method_list: /* empty */ { $$ = new decafStmtList(); } // zero or more
    | T_FUNC T_ID T_LPAREN T_RPAREN method_type block method_list {
        decafStmtList* l = (decafStmtList*) $7;
        BlockAST* bloc = (BlockAST*) $6;
        l->push_front(new MethodDecl(*$2, (TypeSym*) $5, NULL, bloc));
        $$ = l;
    }
    | T_FUNC T_ID T_LPAREN param_list T_RPAREN method_type block method_list {
        decafStmtList* l = (decafStmtList*) $8;
        BlockAST* bloc = (BlockAST*) $7;
        decafStmtList* params = (decafStmtList*) $4;
        l->push_front(new MethodDecl(*$2, (TypeSym*) $6, params, bloc));
        $$ = l;
    }
    ;

param_list: T_ID decaf_type { // one or more
        decafStmtList* res = new decafStmtList();
        res->push_back(new VarDecl(*$1, (TypeSym*) $2));
        $$ = res;
    } 
    | T_ID decaf_type T_COMMA param_list {
        decafStmtList* res = (decafStmtList*) $4;
        res->push_front(new VarDecl(*$1, (TypeSym*) $2));
        $$ = res;
    } 
    ;

block: T_LCB var_list statement_list T_RCB {
        decafStmtList* vars = (decafStmtList*) $2;
        decafStmtList* stats = (decafStmtList*) $3;
        $$ = new BlockAST(vars, stats);
    }
    ;

statement_list: /* empty */ { $$ = new decafStmtList(); } // zero or more
    | statement statement_list {
        decafStmtList* res = (decafStmtList*) $2;
        res->push_front($1);
        $$ = res;
    }
    ;

statement: block { $$ = $1; }
    | assign T_SEMICOLON { $$ = $1;}
    | method_call T_SEMICOLON { $$ = $1; }
    | T_IF T_LPAREN expr T_RPAREN block { 
        BlockAST* ifBloc = (BlockAST*) $5;
        $$ = new IfElseAST($3, ifBloc, NULL);
    }
    | T_IF T_LPAREN expr T_RPAREN block T_ELSE block {
        BlockAST* ifBloc = (BlockAST*) $5;
        BlockAST* elseBloc = (BlockAST*) $7;
        $$ = new IfElseAST($3, ifBloc, elseBloc);}
    | T_WHILE T_LPAREN expr T_RPAREN block {
        BlockAST* bloc = (BlockAST*) $5;
        $$ = new WhileStmtAST($3, bloc);
    }
    | T_FOR T_LPAREN assign_list T_SEMICOLON expr T_SEMICOLON assign_list T_RPAREN block {
        decafStmtList* init = (decafStmtList*) $3;
        decafStmtList* iter = (decafStmtList*) $7;
        BlockAST* bloc = (BlockAST*) $9;
        $$ = new ForStmtAST(init, $5, iter, bloc);
    }
    | T_RETURN T_SEMICOLON { $$ = new ReturnAST(NULL); }
    | T_RETURN T_LPAREN T_RPAREN T_SEMICOLON { $$ = new ReturnAST(NULL); }
    | T_RETURN T_LPAREN expr T_RPAREN T_SEMICOLON { $$ = new ReturnAST($3); }
    | T_BREAK T_SEMICOLON { $$ = new BreakAST(); }
    | T_CONTINUE T_SEMICOLON { $$ = new ContAST(); }
    ;

assign_list: assign { // one or more
        decafStmtList* res = new decafStmtList(); 
        res->push_back($1);
        $$ = res;
    } 
    | assign T_COMMA assign_list {
        decafStmtList* res = (decafStmtList*) $3; 
        res->push_front($1);
        $$ = res;
    }
    ;

assign: T_ID T_LSB expr T_RSB T_ASSIGN expr { $$ = new AssignAST(*$1, $3, $6); }
    | T_ID T_ASSIGN expr { $$ = new AssignAST(*$1, $3); }
    ;

method_call: T_ID T_LPAREN T_RPAREN { $$ = new MethodCall(*$1, NULL); }
    | T_ID T_LPAREN method_arg_list T_RPAREN {
        decafStmtList* args = (decafStmtList*) $3; 
        $$ = new MethodCall(*$1, args);
    }
    ;

method_arg_list: method_arg { // one or more
        decafStmtList* res = new decafStmtList(); 
        res->push_back($1);
        $$ = res;
    }
    | method_arg T_COMMA method_arg_list {
        decafStmtList* res = (decafStmtList*) $3; 
        res->push_front($1);
        $$ = res;
    }
    ;

method_arg: expr { $$ = $1; } 
    | T_STRINGCONSTANT { 
        try {
            $$ = new StringLit(*$1);
        } catch (string e) {
            yyerror(e.c_str());
            return -1;
        }
    }
    ;

expr: and_level { $$ = $1; }
    | expr T_OR and_level {
        $$ = new Operation($1, new OpSym(OR), $3); 
    }
    ;

and_level: comp_level { $$ = $1; }
    | and_level T_AND comp_level {
        $$ = new Operation($1, new OpSym(AND), $3); 
    }
    ;

comp_level: plus_level { $$ = $1; }
    | comp_level comp_op plus_level { $$ = new Operation($1, (OpSym*) $2, $3); }
    ;

plus_level: mult_level { $$ = $1; }
    | plus_level plus_op mult_level { $$ = new Operation($1, (OpSym*) $2, $3); }
    ;

mult_level: not_level { $$ = $1; }
    | mult_level mult_op not_level { $$ = new Operation($1, (OpSym*) $2, $3); }
    ;

not_level: to_endpoint { $$ = $1; }
    | T_NOT not_level { $$ = new Operation($2, new OpSym(NOT)); }
    ;

to_endpoint: T_ID { $$ = new VarCall(*$1); delete $1; }
    | T_ID T_LSB expr T_RSB { $$ = new VarCall(*$1, $3); delete $1; }
    | method_call { $$ = $1; }
    | constant { $$ = $1; }
    | T_LPAREN expr T_RPAREN { $$ = $2; }
    | T_MINUS to_endpoint { $$ = new Operation($2, new OpSym(NEG)); }
    ;

comp_op: T_EQ { $$ = new OpSym(EQ); }
    | T_NEQ { $$ = new OpSym(NEQ); }
    | T_LT { $$ = new OpSym(LT); }
    | T_LEQ { $$ = new OpSym(LE); }
    | T_GT { $$ = new OpSym(GT); }
    | T_GEQ { $$ = new OpSym(GE); }

plus_op: T_PLUS { $$ = new OpSym(ADD); }
    | T_MINUS { $$ = new OpSym(MINUS); }
    ;

mult_op: T_MULT { $$ = new OpSym(MULT); }
    | T_DIV { $$ = new OpSym(DIV); }
    | T_LEFTSHIFT { $$ = new OpSym(LSHI); }
    | T_RIGHTSHIFT { $$ = new OpSym(RSHI); }
    | T_MOD { $$ = new OpSym(MOD); }
    ;

%%

int main() {
    // initialize LLVM
    // Make the module, which holds all the code.
    TheModule = new llvm::Module("Test", Context);
    // set up symbol table
    // set up dummy main function

    // parse the input and create the abstract syntax tree
    int retval = yyparse();
    TheFunction = TheModule->getFunction("main");

    // remove symbol table
    // Finish off the main function.
    // return 0 from main, which is EXIT_SUCCESS
    // Validate the generated code, checking for consistency.
    //verifyFunction(*TheFunction);
    // Print out all of the generated code to stderr
    TheModule->dump();

    return(retval >= 1 ? EXIT_FAILURE : EXIT_SUCCESS);
}

