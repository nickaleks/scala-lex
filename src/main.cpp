#include <iostream>
#include "lexer.h"


int main(int argc, char **argv)
{
    lexer::Lexer lexer{"Hello World"};
    auto buffer = lexer.token_buffer();
    std::cout << buffer.size();

    return 0;
}