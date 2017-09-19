#include <vector>
#include "token.h"

namespace lexer
{
template <typename Iter>
class SourceWord
{
public:
    Iter it;
    const long len;

    SourceWord(Iter it, long len): it{it}, len{len} {};
};

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

    // Type declarations for convenience
    using string_iter = decltype(source.begin());
    using Word = SourceWord<string_iter>;
    // Parse source text and populate token buffer  
    void scan();

    bool is_separator(char ch) {
        return ch == ' ' || ch == '(' || ch == ')' || 
               ch == '{' || ch == '}' || ch == '[' || 
               ch == ']' || ch == '\n' || ch == ';';
    }
    
    Word getWord(string_iter pos)
    {
        char ch = *pos;
        auto begin = pos;
        long len = 1;
        if (is_separator(ch)) {
            return Word{begin, len};
        }
        while (!is_separator(ch) && pos != source.end()) {
            pos++;
            len++;
            ch = *pos;
        }
        ch--;
        return Word{begin, len - 1};
    };
};
}