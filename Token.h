//
// Created by Dustin on 8/24/25.
//

#ifndef JSONPARSER_TOKEN_H
#define JSONPARSER_TOKEN_H

#include <string>

enum class TokenType {
    OpenBrace,
    CloseBrace,
    OpenSquareBracket,
    CloseSquareBracket,
    Quote,
    String,
    Number,
    True,
    False,
    Colon,
    Comma
};

struct Token {
public:

private:
    std::string token_;
    TokenType type_;
};

#endif //JSONPARSER_TOKEN_H
