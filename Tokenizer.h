//
// Created by Dustin on 8/24/25.
//

#ifndef JSONPARSER_TOKENIZER_H
#define JSONPARSER_TOKENIZER_H

#include "Token.h"

#include <optional>
#include <string>
#include <vector>

class Tokenizer {
public:
    Tokenizer() = default;

    // TODO: tokenize contents of file
    std::vector<Token> Tokenize(std::string src);
    void Tokenize(std::string src, std::vector<Token>& tokens);
private:
    void InternalTokenize(std::vector<Token>& tokens);

    std::optional<char> Peek();
    std::optional<char> Consume();
    std::optional<char> PeekN(int n);
    void ConsumeWhitespace();


    std::string src_;
    std::size_t index_;

    std::vector<Token> tokens_;
};


#endif //JSONPARSER_TOKENIZER_H
