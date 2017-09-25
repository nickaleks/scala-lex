#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.h"

void scan_file(const char *filename) 
{
    std::ifstream fs{filename};
    std::stringstream buffer;
    buffer << fs.rdbuf();
    std::string source = buffer.str();
    lexer::Lexer lexer{source};
    lexer.print_buffer();
}

void interpretation_mode()
{
    std::cout << "Welcome! Please, enter the string you want to be lexical processed:\n>> ";
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true) {
        std::string input;
        getline(std::cin, input);
        lexer::Lexer lexer{input};
        lexer.token_buffer();
        std::cout << "\nResult:\n";
        lexer.print_buffer();
        std::cout << "\n\n>> ";
    }
#pragma clang diagnostic pop
}

int main(int argc, char **argv)
{
    if (argc == 2) {
        scan_file(argv[1]);
    } else if (argc == 1) {
        interpretation_mode();
    } else {
        std::cout << "invalid arguments";
        for (int i = 1; i < argc; ++i) {
            std::cout << argv[i]; 
        }
    }
    return 0;
}
