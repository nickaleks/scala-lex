#include "lexer.h"
#include <iostream>

void lexer::Lexer::scan() {
    // lexer implementation goes here
    auto it = source.begin();   
    while(it != source.end()) {
        auto word =  getWord(it);
        if (word == " ") {
            buf.emplace_back(TokenType::Whitespace);
        } else if (word == "if") {
            buf.emplace_back(TokenType::If);
        } else if (word == "while") {
            buf.emplace_back(TokenType::While);
        } else if (word == "else") {
            buf.emplace_back(TokenType::Else);
        }
        it += word.len;
    }
}