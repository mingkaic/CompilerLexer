
#include "decafcomp-defs.h"
#include <list>
#include <ostream>
#include <iostream>
#include <sstream>
#include <exception>
#include "decafsym.cc"

#ifndef YYTOKENTYPE
#include "decafcomp.tab.h"
#endif

using namespace std;

template <class T>
static llvm::Value *ListCodegen(list<T> vec) {
	llvm::Value *val = NULL;
	for (typename list<T>::iterator i = vec.begin(); i != vec.end(); i++) { 
		llvm::Value *j = (*i)->Codegen();
		if (j != NULL) { val = j; }
	}	
	return val;
}

string ConvertEsc(string s) {
	string res = "";
	size_t len = s.size();
	for (size_t i = 0; i < len; i++) {
		if (s[i] == '\\') {
			switch(s[i+1]) {
                case '\'':
                case '"':
                case '\\':
                    res.push_back(s[i+1]);
                    break;
                case 'n':
                    res.push_back('\n');
                    break;
                case 'r':
                    res.push_back('\r');
                    break;
                case 't':
                    res.push_back('\t');
                    break;
                case 'v':
                    res.push_back('\v');
                    break;
                case 'f':
                    res.push_back('\f');
                    break;
                case 'a':
                    res.push_back('\a');
                    break;
                case 'b':
                    res.push_back('\b');
                    break;
                default: // just in case lexer misses
                    throw "unknown escape sequence";
            }
            i++;
		} else {
			res.push_back(s[i]);
		}
	}
	return res;
}

/// decafAST - Base class for all abstract syntax tree nodes.
class decafAST {
public:
  virtual ~decafAST() {}
  virtual llvm::Value *Codegen() = 0;
  virtual TYPEs getType() { return V_BAD; }
};

/// decafStmtList - List of Decaf statements
class decafStmtList : public decafAST {
	list<decafAST *> stmts;
public:
	decafStmtList() {}
	~decafStmtList() {
		for (list<decafAST *>::iterator i = stmts.begin(); i != stmts.end(); i++) {
			delete *i;
		}
	}
	list<decafAST *>::iterator begin() { return stmts.begin(); }
	list<decafAST *>::iterator end() { return stmts.end(); }
	int size() { return stmts.size(); }
	void push_front(decafAST *e) { stmts.push_front(e); }
	void push_back(decafAST *e) { stmts.push_back(e); }
	llvm::Value *Codegen() { 
		return ListCodegen<decafAST *>(stmts); 
	}
};

// ========================== Symbols ========================== //

class OpSym : public decafAST {
	OPs sym;
public:
	OpSym(OPs s) : sym(s) {}
	llvm::Value* Codegen() { return NULL; }
	OPs getOP() { return sym; }
};

class TypeSym : public decafAST {
	TYPEs t;
public:
	TypeSym(TYPEs t) : t(t) {}
	virtual TYPEs getType() { return t; }
	llvm::Value* Codegen() { return NULL; }
	llvm::Type* Tgen();
};

// ========================== Right Values ========================== //

class BoolLit : public decafAST {
	bool data;
public:
	BoolLit(bool data) : data(data) {}
	llvm::Value* Codegen();
	virtual TYPEs getType() { return V_BOOL; }
};

class NumLit : public decafAST {
	int data;
public:
	NumLit(int data) : data(data) {}
	NumLit(string data) {
		if (data[1] == 'x' || data[1] == 'X') {
			size_t pos = 2;
			this->data = stoi(data, &pos, 16);
		} else {
			this->data = stoi(data);
		}
	}
	llvm::Value* Codegen();
	virtual TYPEs getType() { return V_INT; }
};

class StringLit : public decafAST {
	string data;
public:
	StringLit(string data) {
		this->data = data.substr(1, data.size()-2);
		this->data = ConvertEsc(this->data);
	}
	llvm::Value* Codegen();
	virtual TYPEs getType() { return V_STRING; }
};

class VarCall : public decafAST {
	string id;
	decafAST* index;
public:
	VarCall(string identifier, decafAST* index = NULL) 
		: id(identifier), index(index) {}
	~VarCall() { if (NULL != index) { delete index; } }
	TYPEs getType();
	llvm::Value* Codegen();
};

class MethodCall : public decafAST {
	string Name;
	decafStmtList* args;
public:
	MethodCall(string Name, decafStmtList* args) 
		: Name(Name), args(args) {}
	~MethodCall() { if (NULL != args) { delete args; } }
	llvm::Value* Codegen();
};

// ========================== Left Values ========================== //

class VarDecl : public decafAST {
	string Name;
public:
	TypeSym* Type;
	VarDecl(string Name) : Name(Name) {}
	VarDecl(TYPEs in) : Name("") { Type = new TypeSym(in); }
	VarDecl(TypeSym* Type) : Name(""), Type(Type) {}
	VarDecl(string Name, TypeSym* Type) 
		: Name(Name), Type(Type) {}
	~VarDecl() {
		if (Type) {
			delete Type;
		}
	}

	string getName() { return Name; }

	TYPEs getType() { return Type->getType(); }

	llvm::Value* Codegen();
	llvm::Type* Tgen() { return Type->Tgen(); }
};

class GlobalVar : public decafAST {
	VarDecl* var; // guaranteed 1 to 1, no need for smart ptrs
	NumLit* arrSize;
	decafAST* init_val;
public:
	GlobalVar(VarDecl* var) 
		: var(var), arrSize(NULL), init_val(NULL) {}
	GlobalVar(VarDecl* var, NumLit* arrSize) 
		: var(var), arrSize(arrSize), init_val(NULL) {}
	GlobalVar(string Name, TypeSym* var_type, decafAST* init_val)
		: arrSize(NULL), init_val(init_val) { var = new VarDecl(Name, var_type); }
	virtual ~GlobalVar() {
		delete var;
		if (init_val) {
			delete init_val;
		}
		if (arrSize) {
			delete arrSize;
		}
	}
	llvm::Value* Codegen();
};

// ========================== Block ========================== //

class BlockAST : public decafAST {
	decafStmtList* varList;
	decafStmtList* stateList;
public:
	BlockAST(decafStmtList* varList, decafStmtList* stateList) : varList(varList), stateList(stateList) {}
	~BlockAST() {
		if (NULL != varList) {
			delete varList;
		}
		if (NULL != stateList) {
			delete stateList;
		}
	}
	llvm::Value* Codegen();
};

// ========================== Functions ========================== //

class ReturnAST : public decafAST {
	decafAST* ret;
public:
	ReturnAST(decafAST* ret) : ret(ret) {}
	~ReturnAST() { if (NULL != ret) { delete ret; } }
	llvm::Value* Codegen() {
		if (!ret) return NULL;
		return ret->Codegen();
	}
};

class ExternAST : public decafAST {
protected:
	string Name;
	TypeSym* RetType;
	decafStmtList* args;
	llvm::Value* proto();
public:
	ExternAST(string identifier, TypeSym* ret, decafStmtList* param) 
		: Name(identifier), RetType(ret), args(param) {}
	virtual ~ExternAST() { 
		if (NULL != RetType) { delete RetType; }
		if (NULL != args) { delete args; } 
	}
	llvm::Value* Codegen();
};

class MethodDecl : public ExternAST {
	BlockAST* block;
public:
	MethodDecl(string Name, TypeSym* retType, decafStmtList* params, BlockAST* block);
	~MethodDecl() {
		if (NULL != block) {
			delete block;
		}
	}
	llvm::Value* Codegen();
};

class AssignAST : public decafAST {
	string idname;
	decafAST* arridx;
	decafAST* rvalue;
public:
	AssignAST(string idname, decafAST* rvalue) 
		: idname(idname), arridx(NULL), rvalue(rvalue) {}
	AssignAST(string idname, decafAST* arridx, decafAST* rvalue) 
		: idname(idname), arridx(arridx), rvalue(rvalue) {}
	~AssignAST() {
		if (NULL != arridx) {
			delete arridx;
		}
		if (NULL != rvalue) {
			delete rvalue;
		}
	}
	llvm::Value* Codegen();
};

class Operation : public decafAST {
	decafAST* lvalue;
	decafAST* rvalue;
	OpSym* op;
public:
	Operation(decafAST* lvalue, OpSym* op, decafAST* rvalue = NULL)
		: lvalue(lvalue), rvalue(rvalue), op(op) {}
	~Operation() {
		if (NULL != lvalue) { 
			delete lvalue;
		}
		if (NULL != rvalue) { 
			delete rvalue;
		}
		if (NULL != op) { 
			delete op;
		}
	}
	virtual TYPEs getType() {
		if (!rvalue) { // unary only
			return lvalue->getType();
		}
		return V_BAD;
	}
	llvm::Value* Codegen();
};

// ========================== Control Flow ========================== //

class BreakAST : public decafAST {
public:
	llvm::Value* Codegen() {
		return NULL;
	}
};

class ContAST : public decafAST {
public:
	llvm::Value* Codegen() {
		return NULL;
	}
};

class IfElseAST : public decafAST {
	decafAST* condition;
	BlockAST* if_block;
	BlockAST* else_block;
public:
	IfElseAST(decafAST* condition, BlockAST* if_block, BlockAST* else_block)
		: condition(condition), if_block(if_block), else_block(else_block) {}
	~IfElseAST() {
		if (NULL != condition) {
			delete condition;
		}
		if (NULL != if_block) {
			delete if_block;
		}
		if (NULL != else_block) {
			delete else_block;
		}
	}
	llvm::Value* Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
};

class WhileStmtAST : public decafAST {
	decafAST* condition;
	BlockAST* block;
public:
	WhileStmtAST(decafAST* condition, BlockAST* block)
		: condition(condition), block(block) {}
	~WhileStmtAST() {
		if (NULL != condition) {
			delete condition;
		}
		if (NULL != block) {
			delete block;
		}
	}
	llvm::Value* Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
};

class ForStmtAST : public decafAST {
	decafStmtList* init;
	decafAST* condition;
	decafStmtList* iter;
	BlockAST* block;
public:
	ForStmtAST(decafStmtList* init, decafAST* condition, decafStmtList* iter, BlockAST* block)
		: init(init), condition(condition), iter(iter), block(block) {}
	~ForStmtAST() {
		if (NULL != init) { 
			delete init; 
		}
		if (NULL != condition) { 
			delete condition; 
		}
		if (NULL != iter) { 
			delete iter; 
		}
		if (NULL != block) {
			delete block;
		}
	}
	llvm::Value* Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
};

#include "decafcodegen.cc"

// ========================== Top Level ========================== //

class PackageAST : public decafAST {
	string Name;
	decafStmtList *FieldDeclList;
	decafStmtList *MethodDeclList;
public:
	PackageAST(string name, decafStmtList *fieldlist, decafStmtList *methodlist) 
		: Name(name), FieldDeclList(fieldlist), MethodDeclList(methodlist) {}
	~PackageAST() { 
		if (FieldDeclList != NULL) { delete FieldDeclList; }
		if (MethodDeclList != NULL) { delete MethodDeclList; }
	}
	llvm::Value *Codegen() { 
		llvm::Value *val = NULL;
		TheModule->setModuleIdentifier(llvm::StringRef(Name)); 
		if (NULL != FieldDeclList) {
			val = FieldDeclList->Codegen();
		}
		if (NULL != MethodDeclList) {
			val = MethodDeclList->Codegen();
		}
		// Q: should we enter the class name into the symbol table?
		return val; 
	}
};

/// ProgramAST - the decaf program
class ProgramAST : public decafAST {
	decafStmtList *ExternList;
	PackageAST *PackageDef;
public:
	ProgramAST(decafStmtList *externs, PackageAST *c) : ExternList(externs), PackageDef(c) {}
	~ProgramAST() { 
		if (ExternList != NULL) { delete ExternList; } 
		if (PackageDef != NULL) { delete PackageDef; }
	}
	llvm::Value *Codegen() { 
		llvm::Value *val = NULL;
		if (NULL != ExternList) {
			val = ExternList->Codegen();
		}
		if (NULL != PackageDef) {
			val = PackageDef->Codegen();
		} else {
			throw runtime_error("no package definition in decaf program");
		}
		return val; 
	}
};