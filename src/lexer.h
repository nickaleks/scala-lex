#include <vector>
#include "token.h"

namespace lexer
{
class Lexer
{
    std::vector<Token> buf{};
    const std::string& source;
public:
    Lexer(const std::string& source): source{source} 
    {
        scan();
    };

    std::vector<Token>& token_buffer() { return buf; };

private:
    // Parse source text and populate token buffer  
    void scan();
};
}