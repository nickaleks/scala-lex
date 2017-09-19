#include <string>

namespace lexer 
{

enum class TokenType 
{
    If, Else, For, While
    //To be continued
} 

class Token
{
public:
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value): type{type}, value{value} {};

    Token(TokenType type) type{type}, value{""} {};
}

}