#include "lexer.h"
#include <iostream>

void lexer::Lexer::scan() {
    // lexer implementation goes here
    auto it = source.begin();   
    while(it != source.end()) {
        auto word =  getWord(it);
        if (word.len == 1 && *word.it == ' ') {
            buf.emplace_back(TokenType::Whitespace);
        } else if (
            word.len == 2 && 
            *word.it == 'i' &&
            *(word.it + 1) == 'f') {
            buf.emplace_back(TokenType::If);
        }
        it += word.len;
    }
}