#include <iostream>
#include "lexer.h"


int main(int argc, char **argv)
{
    std::string source{"if def(while);true{\n}\ncatch if else _ >: #"};
    lexer::Lexer lexer{source};
    auto buffer = lexer.token_buffer();

    lexer.print_buffer();

    return 0;
}