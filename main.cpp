#include <iostream>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instructions.h>
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

int main() {
    auto ctx = std::make_unique<llvm::LLVMContext>();
    auto builder = std::make_unique<llvm::IRBuilder<>>(*ctx);
    auto module = std::make_unique<llvm::Module>("Module", *ctx);
    llvm::FunctionType *main_type = llvm::FunctionType::
    get(llvm::Type::getInt32Ty(*ctx), false);
    llvm::Function *f_main = llvm::Function::Create(
            main_type, llvm::Function::ExternalLinkage, "main", module.get());
    llvm::BasicBlock *entryBB = llvm::BasicBlock::Create(
            *ctx, "entry", f_main);
    builder->SetInsertPoint(entryBB);

    llvm::Value *v1 = builder->getInt32(56);
    llvm::Value *v2 = builder->getInt32(41);

//    llvm::Value *res = builder->CreateCmp(llvm::CmpInst::Predicate::ICMP_EQ, v1, v2);

    llvm::BasicBlock *trueBB = llvm::BasicBlock::Create(
            *ctx, "true", f_main);

    llvm::BasicBlock *falseBB = llvm::BasicBlock::Create(
            *ctx, "false", f_main);
    //если без сравнения => сравнивать с 0
    llvm::Value *cmp = builder->CreateCmp(llvm::CmpInst::Predicate::ICMP_NE, builder->getInt32(1), builder->getInt32(0));
    builder->CreateCondBr(cmp, trueBB, falseBB);

    builder->SetInsertPoint(trueBB);
    builder->CreateRet(builder->getInt32(1));
    builder->SetInsertPoint(falseBB);
    builder->CreateRet(builder->getInt32(0));

    module->print(llvm::errs(), nullptr);
    return 0;
}
