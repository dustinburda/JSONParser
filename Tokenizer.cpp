//
// Created by Dustin on 8/24/25.
//

#include "Tokenizer.h"

std::vector<Token> Tokenizer::Tokenize(std::string src) {
    src_ = src;
    index_ = 0;

    std::vector<Token> tokens;
    InternalTokenize(tokens);

    return tokens;
}

void Tokenizer::Tokenize(std::string src, std::vector<Token>& tokens) {
    src_ = src;
    index_ = 0;

    InternalTokenize(tokens);
}

void Tokenizer::InternalTokenize(std::vector<Token>& tokens) {

}