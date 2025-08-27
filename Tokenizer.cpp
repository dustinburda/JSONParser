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
           case '{': {
               Consume();
               tokens_.push_back(Token{"", TokenType::OpenBrace});
               break;
           }
           case '}': {
               Consume();
               tokens_.push_back(Token{"", TokenType::CloseBrace});
               break;
           }
           case '[': {
               Consume();
               tokens_.push_back(Token{"", TokenType::OpenSquareBracket});
               break;
           }
           case ']': {
               Consume();
               tokens_.push_back(Token{"", TokenType::CloseSquareBracket});
               break;
           }
           case '\"': {
               std::string s = ConsumeString();
               tokens_.push_back(Token(s, TokenType::String));
               break;
           }
           case ',': {
               Consume();
               tokens_.push_back(Token{"", TokenType::Comma});
               break;
           }
           case ':': {
               Consume();
               tokens_.push_back(Token{"", TokenType::Colon});
               break;
           }
           default: {
            // Parse True, False, Numbers
                if (Peek().value() == 't') {
                    std::string s = PeekN(4).value();

                    if (s != "true")
                        throw std::logic_error("Failed to parse source at character: " + std::to_string(index_));

                    tokens_.push_back(Token{"true", TokenType::True});
                    break;
                } else if (Peek().value() == 'f') {
                    std::string s = PeekN(4).value();

                    if (s != "false")
                        throw std::logic_error("Failed to parse source at character: " + std::to_string(index_));

                    tokens_.push_back(Token{"true", TokenType::True});
                    break;
                } else if (std::isdigit(Peek().value())) {
                    std::string s = ConsumeNumber();

                    tokens_.push_back(Token{s, TokenType::Number});
                    break;
                }
           }
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

std::optional<std::string> Tokenizer::PeekN(int n) {
    if (index_ + n >= src_.size())
        return std::nullopt;

    std::string s;
    for(int i = index_; i < index_ + n; i++) {
        s += src_[i];
    }

    return s;
}

void Tokenizer::ConsumeWhitespace() {
    while (Peek() == '\t' || Peek() == '\n' || Peek() == ' ' || Peek() == '\r')
        Consume();
}

std::string Tokenizer::ConsumeString() {
    Consume();

    std::string s;
    while (Peek().has_value() && Peek().value() != '\"') {
        s += Peek().value();
        Consume();
    }

    if (!Peek().has_value());

    return s;
}

std::string Tokenizer::ConsumeNumber() {
    // TODO: beef this up to the proper JSON spec, only supports positive integers
    std::string s;
    while (Peek().has_value() && std::isdigit(Peek().value())) {
        s += Consume().value();
    }

    return s;
}
