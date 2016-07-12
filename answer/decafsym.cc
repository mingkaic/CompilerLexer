#include <string>
#include <map>
#include <list>
#include "decafexpr-defs.h"

using namespace std;

enum TYPEs {
	V_VOID, V_INT, V_BOOL, V_STRING, V_BAD,
};

enum OPs {
	NEG, NOT, 
	AND, OR, EQ, NEQ, LT, LE, GT, GE, 
	ADD, MINUS, MULT, DIV, LSHI, RSHI, MOD,
};

struct descriptor {
	llvm::AllocaInst* mem;
	TYPEs t;
};

typedef map<string, descriptor> scope_layer;

class symbtbl {
	list<scope_layer* > content;
	scope_layer* methodbuffer;
public:
	symbtbl() {
		content.push_back(new scope_layer());
		methodbuffer = new scope_layer;
	}
	~symbtbl() {
		while (false == content.empty()) {
			delete content.front();
			content.pop_front();
		}
	}
	llvm::AllocaInst*& operator [](string name) {
		list<scope_layer* >::iterator it;
		for (it = content.begin(); 
			it != content.end(); it++) {
			if ((*it)->find(name) != (*it)->end())
				return (**it)[name].mem;
		}
		return (*content.back())[name].mem;
	}
	llvm::AllocaInst*& curscope(string name) {
		return (*content.front())[name].mem;
	}
	void setType(string name, TYPEs t) {
		list<scope_layer* >::iterator it;
		for (it = content.begin(); 
			it != content.end(); it++) {
			if ((*it)->find(name) != (*it)->end()) {
				(**it)[name].t = t;
				return;
			}
		}
	}
	TYPEs getType(string name) {
		list<scope_layer* >::iterator it;
		for (it = content.begin(); 
			it != content.end(); it++) {
			if ((*it)->find(name) != (*it)->end())
				return (**it)[name].t;
		}
		return V_BAD;
	}
	void method_args(string name, llvm::AllocaInst* v, TYPEs t) {
		(*methodbuffer)[name].mem = v;
		(*methodbuffer)[name].t = t;
	}
	int enterscope() {
		content.push_front(methodbuffer);
		methodbuffer = new scope_layer;
		return content.size();
	}
	void exitscope() {
		methodbuffer->clear();
		delete content.front();
		content.pop_front();
	}
	int curscope() {
		return content.size();
	}
};