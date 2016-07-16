
static symbtbl NamedValues;
static std::map<std::string, llvm::Function*> FunctionProtos;

static llvm::Value *LogError(const char *Str) {
	cout << "-1";
	fprintf(stderr, "LogError: %s\n", Str);
	return NULL;
}

static llvm::AllocaInst *CreateEntryBlockAlloca(llvm::Type* t, llvm::Function *TheFunction,
                                          const std::string &VarName, llvm::Value* arrsize = NULL) {
	llvm::IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
	return TmpB.CreateAlloca(t, arrsize, VarName.c_str());
}

static llvm::Value* Bool2Int(llvm::Value* b) {
	return Builder.CreateZExt(b, llvm::Type::getInt32Ty(Context));
}

llvm::Type* TypeSym::Tgen() {
	switch (t) {
		case V_VOID:
			return llvm::Type::getVoidTy(Context);
		case V_INT:
			return llvm::Type::getInt32Ty(Context);
		case V_BOOL:
			return llvm::Type::getInt1Ty(Context);
		case V_STRING:
			return llvm::Type::getInt8PtrTy(Context);
		default:
			return NULL; 
	}
}

llvm::Value* VarDecl::Codegen() {
	llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
	// Create an alloca for the variable in the entry block.
	if (NamedValues.curscope(Name)) {
		LogError("Redefining variable in same scope");
	} else {
		// allocate memory
		llvm::Type* vType = Type->Tgen();
		llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(vType, TheFunction, Name);
		Builder.CreateStore(
			llvm::Constant::getNullValue(vType), Alloca);

		NamedValues[Name] = Alloca;
		NamedValues.setType(Name, Type->getType());
		return Alloca;
	}
	return NULL;
}

llvm::Value* GlobalVar::Codegen() {
	llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

	// Create an alloca for the variable in the entry block.
	if (NamedValues[var->getName()]) {
		LogError("Redefining variable in same scope");
	} else {
		// allocate memory
		llvm::Value* size = NULL;
		if (arrSize) {
			size = arrSize->Codegen();	
		}
		llvm::AllocaInst *Alloca = CreateEntryBlockAlloca(
			var->Type->Tgen(), TheFunction, var->getName(), size);

		if (init_val) {
			Builder.CreateStore(init_val->Codegen(), Alloca);
		} else {
			llvm::Type* vType = var->Tgen();
			Builder.CreateStore(
				llvm::Constant::getNullValue(vType), Alloca);
		}

		NamedValues[var->getName()] = Alloca;
		NamedValues.setType(var->getName(), var->getType());
		return Alloca;
	}
	return NULL;
}

llvm::Value* BoolLit::Codegen() {
	if (data) {
		return llvm::ConstantInt::getTrue(Context);
	}
	return llvm::ConstantInt::getFalse(Context);
}

llvm::Value* NumLit::Codegen() {
	return llvm::ConstantInt::get(Context, llvm::APInt(32, data));
}

llvm::Value* StringLit::Codegen() {
	llvm::GlobalVariable *GS = Builder.CreateGlobalString(
		llvm::StringRef(data.c_str(), data.size()), "gstr");
	return Builder.CreateConstGEP2_32(GS->getValueType(), GS, 0, 0, "cast");
}

TYPEs VarCall::getType() {
	return NamedValues.getType(id);
}

llvm::Value* VarCall::Codegen() {
	llvm::Value *val = NamedValues[id];
	if (!val)
	    LogError("Unknown variable name");

	llvm::Value* var_res = NULL;
	if (index) {
		llvm::Value* idx = index->Codegen();
		var_res = Builder.CreateExtractElement(val, idx);
	} else {
		var_res = Builder.CreateLoad(val, id.c_str());
	}

	return var_res;
}

llvm::Value* MethodCall::Codegen() {
	llvm::Function* callee = TheModule->getFunction(Name);
	if (!callee) {
		return LogError("Unknown function referenced");
	}
	std::vector<llvm::Value *> ArgsV;

	if (args) {
		// If argument mismatch error.
		if (callee->arg_size() != args->size()) {
			return LogError("Incorrect # arguments passed");
		}

		llvm::FunctionType* ftype = callee->getFunctionType();
		size_t i = 0;
		for (list<decafAST *>::iterator it = args->begin(); 
			it != args->end(); it++) {

			llvm::Value* vd = (*it)->Codegen();

			// auto cast bool to int
			if (ftype->getParamType(i)->isIntegerTy(32) 
				&& vd->getType()->isIntegerTy(1)) {
				vd = Bool2Int(vd);
			}
			i++;

			ArgsV.push_back(vd);
			if (!ArgsV.back()) {
				return nullptr;
			}
		}
	}
	if (callee->getReturnType()->isVoidTy()) {
		return Builder.CreateCall(callee->getFunctionType(), callee, ArgsV);
	}
	return Builder.CreateCall(callee->getFunctionType(), callee, ArgsV, "calltmp");
}

llvm::Value* BlockAST::Codegen() {
	int scopeid = NamedValues.enterscope();
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

llvm::Value* ExternAST::proto() {
	std::vector<llvm::Type*> params;
	if (args) {
		for (list<decafAST *>::iterator pit = args->begin();
			pit != args->end(); pit++) {
			VarDecl* v = (VarDecl*) *pit;
			params.push_back(v->Tgen());
		}
	}
	llvm::FunctionType *FT = llvm::FunctionType::get(RetType->Tgen(), params, false);
	llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, Name, TheModule);
	if (args) {
		list<decafAST *>::iterator it = args->begin();
		for (auto &Arg : F->args()) {
			VarDecl* v = (VarDecl*) *it;
			Arg.setName(v->getName());
			it++;
		}
	}

	return F;
}

llvm::Value* ExternAST::Codegen() {
	auto *FnIR = proto();
	if (FnIR) {
		FunctionProtos[Name] = (llvm::Function*) FnIR;
	} else {
		FnIR->dump();
	}
	return FnIR;
}

MethodDecl::MethodDecl(string Name, TypeSym* retType, decafStmtList* params, BlockAST* block)
	: ExternAST(Name, retType, params), block(block) {
	FunctionProtos[this->Name] = (llvm::Function*) this->proto();
}

llvm::Value* MethodDecl::Codegen() {
	llvm::Function *TheFunction = TheModule->getFunction(this->Name);
	if (!TheFunction) {
		TheFunction = FunctionProtos[this->Name];
	}
	if (!TheFunction) {
		return NULL;
	}

	if (!TheFunction->empty()) {
		return (llvm::Function*)LogError("Function cannot be redefined.");
	}
	llvm::BasicBlock *BB = llvm::BasicBlock::Create(Context, "entry", TheFunction);
	Builder.SetInsertPoint(BB);

	// Record the function arguments in the NamedValues map.
	if (this->args) {
		list<decafAST *>::iterator pit = args->begin();
		for (auto &Arg : TheFunction->args()) {
			VarDecl* v = (VarDecl*) *pit;
			string VarName = v->getName();

			// Create an alloca for this variable.
			llvm::AllocaInst* Alloca = CreateEntryBlockAlloca(v->Tgen(), TheFunction, VarName);

			// Store the initial value into the alloca.
			Builder.CreateStore(&Arg, Alloca);

			// Add arguments to variable symbol table.
			NamedValues.method_args(VarName, Alloca, v->getType());
			pit++;
		}
	}

	llvm::Type* rt = TheFunction->getFunctionType()->getReturnType();
	llvm::Value *RetVal = block->Codegen();
	// Finish off the function.
	if (this->Name.compare("main") == 0 && RetVal) {
		Builder.CreateRet(llvm::ConstantInt::get(Context, llvm::APInt(32, 0)));
	} else if (!RetVal && rt->isVoidTy()) {
		Builder.CreateRetVoid();
	} else if (RetVal->getType() == rt) {
		if (rt->isVoidTy()) {
			Builder.CreateRetVoid();
		} else {
			Builder.CreateRet(RetVal);
		}
	} else {
		// return type mismatch
		/*LogError("Bad body");
  		TheFunction->eraseFromParent();
  		return NULL;*/
  		Builder.CreateRet(llvm::Constant::getNullValue(rt));
	}

	// Validate the generated code, checking for consistency.
	llvm::verifyFunction(*TheFunction);
	return TheFunction;	
}

llvm::Value* AssignAST::Codegen() {
	llvm::Value *lval = NamedValues[idname];
	llvm::Value *rval = rvalue->Codegen();

	if (!lval) {
		LogError("Unknown variable name");
	}

	if (arridx) {
		llvm::Value *idx = arridx->Codegen();
		Builder.CreateInsertElement(lval, rval, idx);
	} else {
		Builder.CreateStore(rval, lval);
	}

	return rval;
}

llvm::Value* Operation::Codegen() {
	llvm::Value* res;
	llvm::Value *L = lvalue->Codegen();
	if (!rvalue) { // unary
		if (!L) {
			return NULL;
		}

		switch (op->getOP()) {
			case NEG:
				return Builder.CreateNeg(L, "negtmp");
			case NOT:
				res = Builder.CreateNot(L, "nottmp");
				return res;
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
	return LogError("invalid binary operator");
}

