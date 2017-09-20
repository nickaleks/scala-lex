#include <iostream>
#include "lexer.h"


int main(int argc, char **argv)
{
    std::string source{"if def(while);true{}if else"};
    lexer::Lexer lexer{source};
    auto buffer = lexer.token_buffer();
    std::cout << buffer.size() << "\n";

    return 0;
}