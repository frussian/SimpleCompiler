//
// Created by zoomo on 19.05.2022.
//

#ifndef LAB3_LEXER_H
#define LAB3_LEXER_H

#include <utility>
#include <vector>
#include <string>

enum DomainTag {
    KEYWORD_IF = 0,
    KEYWORD_FOR,
    KEYWORD_INT,
    KEYWORD_RETURN,
    KEYWORD_ELSE,
    L_CURLY_BR,
    R_CURLY_BR,
    L_ROUND_BR,
    R_ROUND_BR,
    IDENT,
    NUMBER,
    ASG,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LT,
    GT,
    EQ,
    NE,
    END_OF_PROGRAM
};

class Token {
public:
    DomainTag tag;
    union {
        int num;
        std::string ident;
    };
    Token(DomainTag tag, int num):
        tag(tag), num(num){};
    Token(DomainTag tag, std::string ident):
        tag(tag), ident(std::move(ident)){};
    ~Token(){};
};

class Lexer {
public:
    static std::vector<Token>get_tokens();
};


#endif //LAB3_LEXER_H
