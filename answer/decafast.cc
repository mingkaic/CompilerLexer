
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

class vardefAST : public decafAST {
	decafAST* content;
public:
	vardefAST(decafAST* content) : content(content) {}
	vardefAST(string in) { content = new terminalAST(in); }
	~vardefAST() { if (NULL != content) { delete content; } }
	string str() { return string("VarDef(") + getString(content) + ")"; }
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

class ExternAST : public decafAST {
	string Name;
	terminalAST* RetType;
	decafStmtList* typelist;
public:
	ExternAST(string identifier, terminalAST* ret, decafStmtList* param) 
		: Name(identifier), RetType(ret), typelist(param) {}
	~ExternAST() {
		if (NULL != typelist) { delete typelist; }
	}
	string str() {
		return string("ExternFunction") + "(" + Name + "," + getString(RetType) + "," + getString(typelist) + ")"; 
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


