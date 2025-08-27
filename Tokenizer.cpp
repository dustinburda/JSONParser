//
// Created by Dustin on 8/24/25.
//

#include "Tokenizer.h"

#include "Token.h"

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
   while (Peek().has_value()) {
       char c = Peek().value();

       switch (c) {
           case '{':
               Consume();
               tokens_.push_back(Token{"", TokenType::OpenBrace});
               break;
           case '}':
               Consume();
               tokens_.push_back(Token{"", TokenType::CloseBrace});
               break;
           case '[':
               Consume();
               tokens_.push_back(Token{"", TokenType::OpenSquareBracket});
               break;
           case ']':
               Consume();
               tokens_.push_back(Token{"", TokenType::CloseSquareBracket});
               break;
           case '"':
                std::string s = ConsumeString();
                tokens.push_back(Token("s", TokenType::String));
                break;
       }

   }
}



std::optional<char> Tokenizer::Peek() {
    if (index_ >= src_.size())
        return std::nullopt;

    return src_[index_];
}

std::optional<char> Tokenizer::Consume() {
    if (index_ >= src_.size())
        return std::nullopt;

    return src_[index_++];
}

std::optional<char> Tokenizer::PeekN(int n) {
    if (index_ >= src_.size())
        return std::nullopt;

    return src_[index_ + n - 1];
}

void Tokenizer::ConsumeWhitespace() {
    while (Peek() == '\t' || Peek() == '\n' || Peek() == ' ')
        Consume();
}
