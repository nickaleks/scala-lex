#include "lexer.h"
#include <iostream>

void lexer::Lexer::scan() {
    // lexer implementation goes here
    auto it = source.begin();   
    while(it != source.end()) {
        auto word =  getWord(it);
        
        it += word.len;
    }
}