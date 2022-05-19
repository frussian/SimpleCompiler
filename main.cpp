#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Instructions.h>
#include "llvm/IR/Constants.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

#include "Lexer.h"

void test() {
    std::string s = "test2 aw     \n";
    std::regex r("^test");
    std::smatch matches;

    std::regex_search(s, matches, r);
    matches.position();
    for (size_t i = 0; i < matches.size(); ++i) {
        std::cout << i << ": '" << matches[i].str() << "'\n";
    }
}

int main(int argc, char *argv[]) {
//    test();
//    if (argc != 2) {
//        printf("usage: lab3 <file>");
//        exit(1);
//    }

    std::stringstream program;
    std::ifstream inFile;
    inFile.open(
//            argv[1]
            "../test.txt"
            );
    if (inFile.is_open()) {
        program << inFile.rdbuf();
        inFile.close();
    } else {
        printf("cannot open file %s", argv[1]);
        exit(0);
    }

    std::string prog_str = program.str();
    auto tokens = Lexer::get_tokens(prog_str);
    for (auto & token : tokens) {
        token.print();
    }

//    auto ctx = std::make_unique<llvm::LLVMContext>();
//    auto builder = std::make_unique<llvm::IRBuilder<>>(*ctx);
//    auto module = std::make_unique<llvm::Module>("Module", *ctx);
//    llvm::FunctionType *main_type = llvm::FunctionType::
//    get(llvm::Type::getInt32Ty(*ctx), false);
//    llvm::Function *f_main = llvm::Function::Create(
//            main_type, llvm::Function::ExternalLinkage, "main", module.get());
//    llvm::BasicBlock *entryBB = llvm::BasicBlock::Create(
//            *ctx, "entry", f_main);
//    builder->SetInsertPoint(entryBB);
//
//    llvm::Value *v1 = builder->getInt32(56);
//    llvm::Value *v2 = builder->getInt32(41);
////    llvm::Value *res = builder->CreateCmp(llvm::CmpInst::Predicate::ICMP_EQ, v1, v2);
//
//    llvm::BasicBlock *trueBB = llvm::BasicBlock::Create(
//            *ctx, "true", f_main);
//
//    llvm::BasicBlock *falseBB = llvm::BasicBlock::Create(
//            *ctx, "false", f_main);
//    llvm::Value *cmp = builder->CreateCmp(llvm::CmpInst::Predicate::ICMP_NE, builder->getInt32(32), builder->getInt32(0));
//    builder->CreateCondBr(cmp, trueBB, falseBB);
//
//    builder->SetInsertPoint(trueBB);
//    builder->CreateRet(builder->getInt32(1));
//    builder->SetInsertPoint(falseBB);
//    builder->CreateRet(builder->getInt32(0));
//
//    module->print(llvm::errs(), nullptr);
    return 0;
}
