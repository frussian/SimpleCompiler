//
// Created by Anton on 21.05.2022.
//

#ifndef LAB3_PARSER_H
#define LAB3_PARSER_H

#include <utility>
#include <vector>
#include <string>
#include <memory>
#include "llvm/IR/IRBuilder.h"

class Token;
class Value;

enum ASTCmpOp {
    AST_LT = 0,
    AST_GT,
    AST_EQ,
    AST_NE
};

enum ASTArithOp {
    AST_PLUS = 0,
    AST_MINUS,
    AST_MUL,
    AST_DIV
};

class CodeGenContext {
public:
    std::unique_ptr<llvm::LLVMContext> ctx;
    std::unique_ptr<llvm::IRBuilder<>> builder;
    std::unique_ptr<llvm::Module> module;
    explicit CodeGenContext();
};

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual Value *codegen(CodeGenContext *ctx) {return nullptr;};
};

class NumberNode: public ASTNode {
public:
    explicit NumberNode(int num): num(num){};
    int num;
};

class VarNode: public ASTNode {
public:
    std::string name;
    explicit VarNode(std::string name):
        name(std::move(name)){};
};

class BinOpNode: public ASTNode {
public:
    std::unique_ptr<ASTNode> lhs, rhs;
    ASTArithOp op;
    explicit BinOpNode(std::unique_ptr<ASTNode> lhs, std::unique_ptr<ASTNode> rhs,
                       ASTArithOp op):
    lhs(std::move(lhs)), rhs(std::move(rhs)), op(op){};
};

class DefNode: public ASTNode {
public:
    std::vector<std::string> names;
    explicit DefNode(std::vector<std::string> names): names(std::move(names)){};
};

class AsgNode: public ASTNode {
public:
    std::string name;
    std::unique_ptr<ASTNode> rhs;
    explicit AsgNode(std::string name, std::unique_ptr<ASTNode> rhs):
        name(std::move(name)), rhs(std::move(rhs)){};
};

class CondNode: public ASTNode {
public:
    std::unique_ptr<ASTNode> lhs, rhs;
    ASTCmpOp cmpOp;
    explicit CondNode(std::unique_ptr<ASTNode> lhs, std::unique_ptr<ASTNode> rhs,
                      ASTCmpOp cmpOp):
    lhs(std::move(lhs)), rhs(std::move(rhs)), cmpOp(cmpOp){};
};

class StmtsNode: public ASTNode {
    std::vector<ASTNode*> stmts;
    explicit StmtsNode(std::vector<ASTNode*> stmts):
            stmts(std::move(stmts)){};
};

class IfNode: public ASTNode {
    std::unique_ptr<CondNode> cond;
    std::unique_ptr<StmtsNode> body;
    explicit IfNode(std::unique_ptr<CondNode> cond, std::unique_ptr<StmtsNode> body):
        cond(std::move(cond)), body(std::move(body)){};
};

class ForNode: public ASTNode {
    std::unique_ptr<StmtsNode> body;
    llvm::BasicBlock *afterBB;
    explicit ForNode(std::unique_ptr<StmtsNode> body):
        body(std::move(body)){};
};

class ReturnNode: public ASTNode {
    std::unique_ptr<ASTNode> expr;
    explicit ReturnNode(std::unique_ptr<ASTNode> expr):
            expr(std::move(expr)){};
};

class BreakNode: public ASTNode {
    std::unique_ptr<ForNode> forNode;
    explicit BreakNode(std::unique_ptr<ForNode> forNode):
    forNode(std::move(forNode)){};
};

class Parser {
public:
    explicit Parser(std::vector<Token> &tokens):
        tokens(tokens){};
    void parse();
private:
    std::vector<Token> tokens;
    Token nextToken();
    Token currToken();
    Token peekToken();
    void skipNewlines();
    std::unique_ptr<ASTNode> genError();
    std::unique_ptr<ASTNode> parseBlock();
    std::vector<ASTNode*> parseStmts();
    std::unique_ptr<ASTNode> parseStmt();
    std::unique_ptr<ASTNode> parseDef();
    int i = 0;
};


#endif //LAB3_PARSER_H
