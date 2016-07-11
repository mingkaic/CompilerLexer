#include <string>
#include <map>
#include <list>
#include "decafexpr-defs.h"

using namespace std;

typedef map<string, llvm::AllocaInst* > scope_layer;

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
				return (**it)[name];
		}
		return (*content.back())[name];
	}
	void method_args(string name, llvm::AllocaInst* v) {
		(*methodbuffer)[name] = v;
	}
	void enterscope() {
		content.push_front(methodbuffer);
		methodbuffer = new scope_layer;
	}
	void exitscope() {
		methodbuffer->clear();
		delete content.front();
		content.pop_front();
	}
};