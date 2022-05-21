//
// Created by Anton on 21.05.2022.
//

#include "Parser.h"
#include "Lexer.h"

void Parser::parse() {

}

//{ stmts }
std::unique_ptr<ASTNode> Parser::parseBlock() {
    auto tok = currToken();
    if (tok.tag != L_CURLY_BR) {
        return std::move(genError());
    }
    nextToken();
    auto stmts = parseStmts();
}

std::vector<ASTNode*> Parser::parseStmts() {
    std::vector<ASTNode*> stmts;

    while (true) {
        skipNewlines();
        auto tok = currToken();
        if (tok.tag == R_CURLY_BR) {
            nextToken();
            return stmts;
        }
        auto stmt = parseStmt();
        stmts.push_back(stmt.release());
    }
    return stmts;
}

std::unique_ptr<ASTNode> Parser::parseStmt() {
    auto tok = currToken();
    if (tok.tag == KEYWORD_INT) {
        nextToken();
        return parseDef();
    } else {

    }
    return std::unique_ptr<ASTNode>();
}

std::unique_ptr<ASTNode> Parser::parseDef() {
    auto tok = currToken();
    if (tok.tag != IDENT) {
        return genError();
    }
    std::vector<std::string> names;
    names.push_back(tok.ident);

    while (true) {
        tok = nextToken();
        if (tok.tag == NL) {
            nextToken();
            return std::make_unique<DefNode>(names);
        } else if (tok.tag != COMMA) {
            return genError();
        }
        tok = nextToken();
        if (tok.tag != IDENT) {
            return genError();
        }
        names.push_back(tok.ident);
    }
    return std::make_unique<DefNode>(names);
}

Token Parser::nextToken() {
    i++;
    return tokens[i];
}

Token Parser::currToken() {
    return tokens[i];
}

Token Parser::peekToken() {
    return tokens[i+1];
}

std::unique_ptr<ASTNode> Parser::genError() {
    auto tok = tokens[i];
    printf("unexpected token %d at (%d, %d)", tok.tag, tok.frag.ys, tok.frag.xs);
    return nullptr;
}

void Parser::skipNewlines() {
    while (currToken().tag == NL) {
        nextToken();
    }
}
