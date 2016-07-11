
#include "decafexpr-defs.h"
#include <list>
#include <ostream>
#include <iostream>
#include <sstream>
#include <exception>
#include "decafsym.cc"

#ifndef YYTOKENTYPE
#include "decafexpr.tab.h"
#endif

using namespace std;

static symbtbl NamedValues;

void LogError(const char *Str) {
  fprintf(stderr, "LogError: %s\n", Str);
}

llvm::Value *LogErrorV(const char *Str) {
  LogError(Str);
  return nullptr;
}

static llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Type* t, llvm::Function *TheFunction,
                                          const std::string &VarName) {
	llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
	return TmpB.CreateAlloca(t, NULL, VarName.c_str());
}

/// decafAST - Base class for all abstract syntax tree nodes.
class decafAST {
public:
  virtual ~decafAST() {}
  virtual string str() { return string(""); }
  virtual llvm::Value *Codegen() = 0;
};

static std::map<std::string, decafAST*> FunctionProtos;

string convertescape(string s) {
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

template <class T>
llvm::Value *listCodegen(list<T> vec) {
	llvm::Value *val = NULL;
	for (typename list<T>::iterator i = vec.begin(); i != vec.end(); i++) { 
		llvm::Value *j = (*i)->Codegen();
		if (j != NULL) { val = j; }
	}	
	return val;
}

class terminalAST : public decafAST {
	string Name;
public:
	terminalAST(string name) : Name(name) {}
	string str() { return Name; }
	llvm::Value* Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
};

enum OPs {
	NEG, NOT, 
	AND, OR, EQ, NEQ, LT, LE, GT, GE, 
	ADD, MINUS, MULT, DIV, LSHI, RSHI, MOD,
};

class opSymAST : public decafAST {
	OPs sym;
public:
	opSymAST(OPs s) : sym(s) {}
	string str() {
		switch(sym) {
			case NEG:
				return "UnaryMinus";
			case NOT:
				return "Not";
			case AND:
				return "And";
			case OR:
				return "Or";
			case EQ:
				return "Eq";
			case NEQ: 
				return "Neq";
			case LT:
				return "Lt";
			case LE:
				return "Leq";
			case GT:
				return "Gt";
			case GE: 
				return "Geq";
			case ADD:
				return "Plus";
			case MINUS:
				return "Minus";
			case MULT:
				return "Mult";
			case DIV:
				return "Div";
			case LSHI:
				return "Leftshift";
			case RSHI:
				return "Rightshift";
			case MOD:
				return "Mod";
		}
		return "";
	}
	llvm::Value* Codegen() { return NULL; }
	OPs getOP() { return sym; }
};

enum TYPEs {
	V_VOID, V_INT, V_BOOL, V_STRING,
};

class typeSymAST : public decafAST {
	TYPEs t;
public:
	typeSymAST(TYPEs t) : t(t) {}
	string str() {
		switch(t) {
			case V_VOID:
				return "VoidType";
			case V_INT:
				return "IntType";
			case V_BOOL:
				return "BoolType";
			case V_STRING:
				return "StringType";
		}
		return "";
	}
	llvm::Value* Codegen() { return NULL; }
	llvm::Type* Tgen() {
		switch (t) {
			case V_VOID:
				return llvm::Type::getVoidTy(Context);
			case V_INT:
				return llvm::Type::getInt32Ty(Context);
			case V_BOOL:
				return llvm::Type::getInt32Ty(Context);
			case V_STRING:
				return llvm::Type::getInt32PtrTy(Context);
			default:
				return NULL; 
		}
	}
};

class temporaryAST : public decafAST {
public:
	list<string*> types;
	~temporaryAST() {
		for (list<string*>::iterator i = types.begin(); i != types.end(); i++) { 
			delete *i;
		}
	}
	llvm::Value* Codegen() { // never called
		return NULL;
	}
};

class booleanAST : public decafAST {
	bool data;
public:
	booleanAST(bool data) : data(data) {}
	string str() { 
		if (data) {
			return "BoolExpr(True)"; 
		}
		return "BoolExpr(False)"; 
	}
	llvm::Value* Codegen() {
		llvm::Value *val = llvm::ConstantInt::get(Context, llvm::APInt(32, data));
		return val;
	}
};

class numericAST : public decafAST {
	int data;
public:
	numericAST(int data) : data(data) {}
	string str() { return "NumberExpr(" + to_string((int)data) + ")"; }
	llvm::Value* Codegen() {
		llvm::Value *val = llvm::ConstantInt::get(Context, llvm::APInt(32, data));
		return val;
	}
};

class stringAST : public decafAST {
	string data;
public:
	stringAST(string data) : data(data) {}
	string str() { return "StringConstant(" + data + ")"; }
	llvm::Value* Codegen() {
		llvm::Value *val = llvm::ConstantDataArray::get(Context, 
			llvm::ArrayRef<uint16_t>((uint16_t*) data.c_str(), data.length()));
		return val;
	}
};

class vardefAST : public decafAST {
	string content;
	typeSymAST* Type;
public:
	vardefAST(typeSymAST* Type) : content(""), Type(Type) {}
	vardefAST(TYPEs in) : content("") { Type = new typeSymAST(in); }
	vardefAST(string content, typeSymAST* Type) : content(content), Type(Type) {}
	~vardefAST() { if (NULL != Type) { delete Type; } }
	string getContent() {return content;}
	string getType() {return getString(Type);}
	string str() { 
		string res = "VarDef(";
		if (0 != content.size()) {
			res += content + ",";
		}
		return res + getString(Type) + ")"; 
	}
	string getName() {
		return content;
	}
	llvm::Value* Codegen() {
		llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

		// Create an alloca for the variable in the entry block.
		if (NamedValues[content]) {
			LogErrorV("Redefining variable in same scope");
		} else {
			// allocate memory
			llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(Type->Tgen(), TheFunction, content);
			NamedValues[content] = Alloca;
			return Alloca;
		}
		return NULL;
	}
	llvm::Type* Tgen() {
		return Type->Tgen();
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
	list<decafAST *>::iterator begin() { return stmts.begin(); }
	list<decafAST *>::iterator end() { return stmts.end(); }
	int size() { return stmts.size(); }
	void push_front(decafAST *e) { stmts.push_front(e); }
	void push_back(decafAST *e) { stmts.push_back(e); }
	string str() { return commaList<class decafAST *>(stmts); }
	llvm::Value *Codegen() { 
		return listCodegen<decafAST *>(stmts); 
	}
};

class FieldDeclAST : public decafAST {
	string Name;
	string arrNum;
	typeSymAST* typ;
	decafAST* constant;
public:
	FieldDeclAST(string Name, typeSymAST* typ)
		: Name(Name), typ(typ), arrNum(""), constant(NULL) {}
	FieldDeclAST(string Name, typeSymAST* typ, string arrNum) 
		: Name(Name), typ(typ), arrNum(arrNum), constant(NULL) {}
	FieldDeclAST(string Name, typeSymAST* typ, decafAST* constant)
		: Name(Name), typ(typ), arrNum(""), constant(constant) {}
	~FieldDeclAST() {
		if (NULL != typ) {
			delete typ;
		}
		if (NULL != constant) {
			delete constant;
		}
	}
	string str() {
		if (NULL != constant) {
			return string("AssignGlobalVar(") + Name + "," 
				+ getString(typ) + "," + getString(constant) + ")";
		}
		string res = string("FieldDecl(") + Name + "," + getString(typ) + ",";
		if (arrNum.size() > 0) {
			res += "Array(" + arrNum + ")";
		} else {
			res += "Scalar";
		}
		return res + ")";
	}
	llvm::Value* Codegen() {
		llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

		// Create an alloca for the variable in the entry block.
		if (NamedValues[Name]) {
			LogErrorV("Redefining variable in same scope");
		} else {
			// allocate memory
			llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(typ->Tgen(), TheFunction, Name);
			NamedValues[Name] = Alloca;
			return Alloca;
		}
		return NULL;
	}
};

class ExternAST : public decafAST {
protected:
	string Name;
	typeSymAST* RetType;
	decafStmtList* args;
	llvm::Value* proto() {
		std::vector<llvm::Type*> params;
		if (args) {
			for (list<decafAST *>::iterator pit = args->begin();
				pit != args->end(); pit++) {
				vardefAST* v = (vardefAST*) *pit;
				params.push_back(v->Tgen());
			}
		}
		llvm::FunctionType *FT = llvm::FunctionType::get(RetType->Tgen(), params, false);
		llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Name, TheModule);
		if (args) {
			list<decafAST *>::iterator it = args->begin();
			for (auto &Arg : F->args()) {
				vardefAST* v = (vardefAST*) *it;
				Arg.setName(v->getName());
				it++;
			}
		}

		return F;
	}
public:
	ExternAST(string identifier, typeSymAST* ret, decafStmtList* param) 
		: Name(identifier), RetType(ret), args(param) {}
	virtual ~ExternAST() { 
		if (NULL != RetType) { delete RetType; }
		if (NULL != args) { delete args; } 
	}
	virtual string str() {
		return string("ExternFunction(") + Name + "," + getString(RetType) + "," + getString(args) + ")"; 
	}
	llvm::Value* Codegen() {
		auto *FnIR = proto();
		if (FnIR) {
			FunctionProtos[Name] = this;
		} else {
			FnIR->dump();
		}
		return FnIR;
	}
};

class opAST : public decafAST {
	decafAST* lvalue;
	decafAST* rvalue;
	opSymAST* op;
public:
	opAST(decafAST* lvalue, opSymAST* op, decafAST* rvalue = NULL)
		: lvalue(lvalue), rvalue(rvalue), op(op) {}
	~opAST() {
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
	string str() {
		if (NULL == rvalue) {
			return string("UnaryExpr(") + getString(op) + "," + getString(lvalue) + ")";
		}
		return string("BinaryExpr(") + getString(op) + "," + getString(lvalue) + "," + getString(rvalue) + ")"; 
	}
	llvm::Value* Codegen() {
		llvm::Value *L = lvalue->Codegen();
		if (!rvalue) { // unary
			if (!L) {
				return NULL;
			}

			switch (op->getOP()) {
				case NEG:
					return Builder.CreateNeg(L, "negtmp");
				case NOT:
					return Builder.CreateNot(L, "nottmp");
				default:
					break;
			}
		} else {
			llvm::Value *R = rvalue->Codegen();
			if (!L || !R) {
				return NULL;
			}

			switch (op->getOP()) {
				case AND:
					return Builder.CreateAnd(L, R, "andtmp");
				case OR:
					return Builder.CreateOr(L, R, "ortmp");
				case EQ:
					return Builder.CreateICmpEQ(L, R, "eqtmp");
				case NEQ: 
					return Builder.CreateICmpNE(L, R, "netmp");
				case LT:
					return Builder.CreateICmpULT(L, R, "lttmp");
				case LE:
					return Builder.CreateICmpULE(L, R, "letmp");
				case GT:
					return Builder.CreateICmpUGT(L, R, "gttmp");
				case GE: 
					return Builder.CreateICmpUGE(L, R, "getmp");
				case ADD:
					return Builder.CreateAdd(L, R, "addtmp");
				case MINUS:
					return Builder.CreateSub(L, R, "subtmp");
				case MULT:
					return Builder.CreateMul(L, R, "multmp");
				case DIV:
					return Builder.CreateSDiv(L, R, "divtmp");
				case LSHI:
					return Builder.CreateShl(L, R, "shltmp");
				case RSHI:
					return Builder.CreateLShr(L, R, "shrtmp");
				case MOD:
					return Builder.CreateSRem(L, R, "modtmp");
				default:
					break;
			}
		}
		return LogErrorV("invalid binary operator");
	}
};

class rvalueAST : public decafAST {
	string id;
	decafAST* index;
public:
	rvalueAST(string identifier, decafAST* index = NULL) 
		: id(identifier), index(index) {}
	~rvalueAST() { if (NULL != index) { delete index; } }
	string str() {
		if (NULL == index) {
			return string ("VariableExpr(") + id + ")";
		}
		return string("ArrayLocExpr(") + id + "," + getString(index) + ")"; 
	}
	llvm::Value* Codegen() {
		llvm::Value *val = NamedValues[id];
		if (!val)
		    LogErrorV("Unknown variable name");
		return Builder.CreateLoad(val, id.c_str());
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
	llvm::Value* Codegen() {
		NamedValues.enterscope();
		llvm::Value *val = NULL;
		if (NULL != varList) {
			val = varList->Codegen();
		}
		if (NULL != stateList) {
			val = stateList->Codegen();
		}
		NamedValues.exitscope();
		return val;
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
	llvm::Value* Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
};

class WhileStmtAST : public decafAST {
	decafAST* condition;
	blockAST* block;
public:
	WhileStmtAST(decafAST* condition, blockAST* block)
		: condition(condition), block(block) {}
	~WhileStmtAST() {
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
	llvm::Value* Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
};

class ForStmtAST : public decafAST {
	decafStmtList* init;
	decafAST* condition;
	decafStmtList* iter;
	blockAST* block;
public:
	ForStmtAST(decafStmtList* init, decafAST* condition, decafStmtList* iter, blockAST* block)
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
	string str() {
		return string("ForStmt(") + getString(init) + "," + getString(condition) + "," 
			+ getString(iter) + "," + getString(block) + ")";
	}
	llvm::Value* Codegen() {
		llvm::Value *val = NULL;
		return val;
	}
};

class MethodDeclAST : public ExternAST {
	blockAST* block;
public:
	MethodDeclAST(string Name, typeSymAST* retType, decafStmtList* params, blockAST* block)
		: ExternAST(Name, retType, params), block(block) {}
	~MethodDeclAST() {
		if (NULL != block) {
			delete block;
		}
	}
	string str() {
        return string("Method(") + this->Name + "," + getString(this->RetType) + "," + 
        	getString(this->args) + ",Method" + getString(block) + ")";
	}
	llvm::Value* Codegen() {
		llvm::Function *TheFunction = TheModule->getFunction(this->Name);
		if (!TheFunction) {
			TheFunction = (llvm::Function*) this->proto();
		}
		if (!TheFunction) {
			return NULL;
		}
		if (!TheFunction->empty()) {
			return (llvm::Function*)LogErrorV("Function cannot be redefined.");
		}
		llvm::BasicBlock *BB = llvm::BasicBlock::Create(Context, "entry", TheFunction);
		Builder.SetInsertPoint(BB);

		// Record the function arguments in the NamedValues map.
		if (this->args) {
			for (list<decafAST *>::iterator pit = args->begin();
				pit != args->end(); pit++) {
				vardefAST* v = (vardefAST*) *pit;
				string VarName = v->getName();

				llvm::AllocaInst* Alloca = CreateEntryBlockAlloca(v->Tgen(), TheFunction, VarName);
				NamedValues.method_args(VarName, Alloca);
			}
		}

		if (llvm::Value *RetVal = block->Codegen()) {
			// Finish off the function.
			if (this->Name.compare("main") != 0) {
				if (RetVal->getType()->isVoidTy()) {
					Builder.CreateRet(NULL);
				} else {
					Builder.CreateRet(RetVal);
				}
			}
		} else {
			Builder.CreateRet(NULL);
		}
		// Validate the generated code, checking for consistency.
		llvm::verifyFunction(*TheFunction);
		return TheFunction;
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
	llvm::Value* Codegen() {
		llvm::Function* callee = TheModule->getFunction(Name);
		if (!callee) {
			return LogErrorV("Unknown function referenced");
		}

		// If argument mismatch error.
		if (callee->arg_size() != args->size()) {
			return LogErrorV("Incorrect # arguments passed");
		}

		std::vector<llvm::Value *> ArgsV;

		for (list<decafAST *>::iterator it = args->begin(); 
			it != args->end(); it++) {
			ArgsV.push_back((*it)->Codegen());
			if (!ArgsV.back()) {
				return nullptr;
			}
		}
		if (callee->getReturnType()->isVoidTy()) {
			return Builder.CreateCall(callee->getFunctionType(), callee, ArgsV);
		}
		return Builder.CreateCall(callee->getFunctionType(), callee, ArgsV, "calltmp");
	}
};

class ReturnStmtAST : public decafAST {
	decafAST* ret;
public:
	ReturnStmtAST(decafAST* ret) : ret(ret) {}
	~ReturnStmtAST() { if (NULL != ret) { delete ret; } }
	string str() {
		return string("ReturnStmt(") + getString(ret) + ")";
	}
	llvm::Value* Codegen() {
		llvm::Value *val = NULL;
		return val;
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
	llvm::Value* Codegen() {
		llvm::Value *lval = NamedValues[lvalue1];
		llvm::Value *rval = rvalue->Codegen();

    	Builder.CreateStore(rval, lval);

		return rval;
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
	string str() { return string("Program") + "(" + getString(ExternList) + "," + getString(PackageDef) + ")"; }
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