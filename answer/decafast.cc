
#include "decafast-defs.h"
#include <list>
#include <ostream>
#include <iostream>
#include <sstream>

#ifndef YYTOKENTYPE
#include "decafast.tab.h"
#endif

using namespace std;

/// decafAST - Base class for all abstract syntax tree nodes.
class decafAST {
public:
  virtual ~decafAST() {}
  virtual string str() { return string(""); }
};

string getString(decafAST *d) {
	if (d != NULL) {
		return d->str();
	} else {
		return string("None");
	}
}

template <class T>
string commaList(list<T> vec) {
    string s("");
    for (typename list<T>::iterator i = vec.begin(); i != vec.end(); i++) { 
        s = s + (s.empty() ? string("") : string(",")) + (*i)->str(); 
    }
    if (s.empty()) {
        s = string("None");
    }   
    return s;
}

class terminalAST : public decafAST {
	string Name;
public:
	terminalAST(string name) : Name(name) {}
	string str() { return Name; }
};

class temporaryAST : public decafAST {
public:
	list<string*> types;
	~temporaryAST() {
		for (list<string*>::iterator i = types.begin(); i != types.end(); i++) { 
			delete *i;
		}
	}
};

class constantAST : public decafAST {
	string wrap;
	string data;
public:
	constantAST(string wrap, string data) : wrap(wrap), data(data) {}
	string str() { return wrap + "(" + data + ")"; }
};

class typedSymAST : public decafAST {
	string content;
	decafAST* Type;
public:
	typedSymAST(decafAST* Type) : content(""), Type(Type) {}
	typedSymAST(string in) : content("") { Type = new terminalAST(in); }
	typedSymAST(string content, decafAST* Type) : content(content), Type(Type) {}
	~typedSymAST() { if (NULL != Type) { delete Type; } }
	string str() { 
		string res = "VarDef(";
		if (0 != content.size()) {
			res += content + ",";
		}
		return res + getString(Type) + ")"; 
	}
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
	int size() { return stmts.size(); }
	void push_front(decafAST *e) { stmts.push_front(e); }
	void push_back(decafAST *e) { stmts.push_back(e); }
	string str() { return commaList<class decafAST *>(stmts); }
};

class FieldDecl : public decafAST {
	string Name;
	string arrNum;
	decafAST* Type;
	constantAST* constant;
public:
	FieldDecl(string Name, decafAST* Type)
		: Name(Name), Type(Type), arrNum(""), constant(NULL) {}
	FieldDecl(string Name, decafAST* Type, string arrNum) 
		: Name(Name), Type(Type), arrNum(arrNum), constant(NULL) {}
	FieldDecl(string Name, decafAST* Type, constantAST* constant)
		: Name(Name), Type(Type), arrNum(""), constant(constant) {}
	~FieldDecl() {
		if (NULL != Type) {
			delete Type;
		}
		if (NULL != constant) {
			delete constant;
		}
	}
	string str() {
		if (NULL != constant) {
			return string("AssignGlobalVar(") + Name + "," 
				+ getString(Type) + "," + getString(constant) + ")";
		}
		string res = string("FieldDecl(") + Name + "," + getString(Type) + ",";
		if (arrNum.size() > 0) {
			res += "Array(" + arrNum + ")";
		} else {
			res += "Scalar";
		}
		return res + ")";
	}
};

class ExternAST : public decafAST {
	string Name;
	terminalAST* RetType;
	decafStmtList* typelist;
public:
	ExternAST(string identifier, terminalAST* ret, decafStmtList* param) 
		: Name(identifier), RetType(ret), typelist(param) {}
	~ExternAST() { if (NULL != typelist) { delete typelist; } }
	string str() {
		return string("ExternFunction(") + Name + "," + getString(RetType) + "," + getString(typelist) + ")"; 
	}
};

class methodCallAST : public decafAST {
	string Name;
	decafStmtList* args;
public:
	methodCallAST(string Name, decafStmtList* args) 
		: Name(Name), args(args) {}
	~methodCallAST() { if (NULL != args) { delete args; } }
	string str() {
		return string("MethodCall(") + Name + "," + getString(args) + ")"; 
	}
};

class ReturnStmt : public decafAST {
	decafAST* ret;
public:
	ReturnStmt(decafAST* ret) : ret(ret) {}
	~ReturnStmt() { if (NULL != ret) { delete ret; } }
	string str() {
		return string("ReturnStmt(") + getString(ret) + ")";
	}
};

class assignAST : public decafAST {
	string lvalue1;
	decafAST* lvalue2;
	decafAST* rvalue;
public:
	assignAST(string lvalue, decafAST* rvalue) 
		: lvalue1(lvalue), lvalue2(NULL), rvalue(rvalue) {}
	assignAST(string lvalue1, decafAST* lvalue2, decafAST* rvalue) 
		: lvalue1(lvalue1), lvalue2(lvalue2), rvalue(rvalue) {}
	~assignAST() {
		if (NULL != lvalue2) {
			delete lvalue2;
		}
		if (NULL != rvalue) {
			delete rvalue;
		}
	}
	string str() {
		string res;
		if (NULL == lvalue2) {
			res = "AssignVar(" + lvalue1 + ",";
		} else {
			res = "AssignArrayLoc(" + lvalue1 + "," + getString(lvalue2) + ",";
		}
		return res + getString(rvalue) + ")";
	}
};

class blockAST : public decafAST {
	decafStmtList* varList;
	decafStmtList* stateList;
public:
	blockAST(decafStmtList* varList, decafStmtList* stateList) : varList(varList), stateList(stateList) {}
	~blockAST() {
		if (NULL != varList) {
			delete varList;
		}
		if (NULL != stateList) {
			delete stateList;
		}
	}
	string str() {
        return string("Block(") + getString(varList) + "," + getString(stateList) + ")";
	}
};

class IfElseAST : public decafAST {
	decafAST* condition;
	blockAST* if_block;
	blockAST* else_block;
public:
	IfElseAST(decafAST* condition, blockAST* if_block, blockAST* else_block)
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
	string str() {
		return string("IfStmt(") + getString(condition) + "," + 
			getString(if_block) + "," + getString(else_block) + ")";
	}
};

class WhileStmt : public decafAST {
	decafAST* condition;
	blockAST* block;
public:
	WhileStmt(decafAST* condition, blockAST* block)
		: condition(condition), block(block) {}
	~WhileStmt() {
		if (NULL != condition) {
			delete condition;
		}
		if (NULL != block) {
			delete block;
		}
	}
	string str() {
		return string("WhileStmt(") + getString(condition) + "," + getString(block) + ")"; 
	}
};

class ForStmt : public decafAST {
	decafStmtList* init;
	decafAST* condition;
	decafStmtList* iter;
public:
	ForStmt(decafStmtList* init, decafAST* condition, decafStmtList* iter)
		: init(init), condition(condition), iter(iter) {}
	~ForStmt() {
		if (NULL != init) { 
			delete init; 
		}
		if (NULL != condition) { 
			delete condition; 
		}
		if (NULL != iter) { 
			delete iter; 
		}
	}
	string str() {
		return string("ForStmt(") + getString(init) + "," +
			getString(condition) + "," + getString(iter) + ")";
	}
};

class MethodDeclAST : public decafAST {
	string Name;
	decafAST* Type;
	decafStmtList* arrParam;
	blockAST* block;
public:
	MethodDeclAST(string Name, decafAST* retType, decafStmtList* params, blockAST* block)
		: Name(Name), Type(retType), arrParam(params), block(block) {}
	~MethodDeclAST() {
		if (NULL != Type) {
			delete Type;
		}
		if (NULL != arrParam) {
			delete arrParam;
		}
		if (NULL != block) {
			delete block;
		}
	}
	string str() {
        return string("Method(") + Name + "," + getString(Type) + "," + 
        	getString(arrParam) + "," + getString(block) + ")";
	}
};

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
	string str() { 
		return string("Package") + "(" + Name + "," + getString(FieldDeclList) + "," + getString(MethodDeclList) + ")";
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
	string str() { return string("Program") + "(" + getString(ExternList) + "," + getString(PackageDef) + ")"; }
};


