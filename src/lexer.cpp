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
        }
        it += word.len;
    }
}