#include <vector>
#include <iostream>
#include "string_slice.h"
#include "token.h"

namespace lexer
{
    
class InvalidXMLException: public std::runtime_error
{
public:
    explicit InvalidXMLException()
            : std::runtime_error(exceptionMessage) {}

    const char* what() const throw() override {
        return exceptionMessage.c_str();
    }

private:
    std::string exceptionMessage = "Invalid XML construction";
};

class Lexer
{
    std::vector<Token> buf{};
    const std::string& source;
public:
    Lexer(const std::string& source): source{source}, new_lines_enabled{true}
    {
        scan();
    };

    std::vector<Token>& token_buffer() { 
        return buf; 
    };

    void print_buffer() const {
        for (const auto &i : buf) {
            std::cout << Token::to_string.at(i.type) << "(" << i.value << ")" << "\n";
        }
    }

private:

    // Type declarations for convenience
    using string_iter = decltype(source.begin());

    bool new_lines_enabled;
    // Parse source text and populate token buffer
    void scan();

    bool is_separator(char ch) const;

    bool can_terminate_statement(const Token& tok) const;

    StringSlice get_word(string_iter pos);
   
    // This function analyzes last token in buffer, 
    // and if it is an end of statement token 
    // with newline value, it replace it with NewLine token. 
    // Otherwise does nothing
    void replace_end_of_statement();

    /*
     * Understands, if the next statement is going to be an XML one; does
     * not shift the iterator
     */
    bool xml_begins(string_iter iterator);

    /*
     * Analyzes the XML and shifts the iterator; assumes that XML is valid
     */
    void process_xml(string_iter &iterator);

    /*
     * Understands, if the following construction will be comment
     */
    bool comment_begins(string_iter iterator);
    /*
     * Processes the comment, shifting the iterator, and returns the comment itself
     */
    StringSlice process_comment(string_iter& iterator);
};
}