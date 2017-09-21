#include <iostream>
#include "lexer.h"


void interpretateMode()
{
    std::cout << "Welcome! Please, enter the string you want to be lexical processed:\n>> ";
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        std::string input;
        getline(std::cin, input);
        lexer::Lexer lexer{input};
        lexer.token_buffer();
        std::cout << "\nResult: ";
        lexer.print_buffer();
        std::cout << "\n\n>> ";
    }
#pragma clang diagnostic pop
}

int main(int argc, char **argv)
{
    std::string source{"if def(while);true{\n}\ncatch if else <book> <author> Zuev </author> Good Book </book> "
                               "<foo> bar </foo> _ >: #"};
    lexer::Lexer lexer{source};
    auto buffer = lexer.token_buffer();

    lexer.print_buffer();

    return 0;
}