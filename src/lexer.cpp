#include "lexer.h"
#include <iostream>

void lexer::Lexer::scan() {
    // lexer implementation goes here
    auto it = source.begin();   
    while(it != source.end()) {
        char ch = *it;
        if (ch == ' ') {
            buf.emplace_back(TokenType::Whitespace);
        }
        it++;
    }
}