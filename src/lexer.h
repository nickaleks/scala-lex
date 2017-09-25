#include <vector>
#include <iostream>
#include "token.h"

namespace lexer
{
template <typename Iter>
class SourceWord
{
public:
    Iter it;
    const std::size_t len;

    SourceWord(Iter it, std::size_t len): it{it}, len{len} {};

    bool operator==(const std::string& rhs)
    {
        if (len != rhs.length()) {
            return false;
        }
        for (int i = 0; i < len; i++) {
            if (*(it + i) != rhs[i]){
                return false;
            }
        }
        return true;
    };

    // Makes copy of sliced string
    std::string operator*() {
        std::string res{};
        res.reserve(len);
        for (auto i = 0; i < len; i++, it++) {
            res += *it;
        }

        return res;
    }
};

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
    using Word = SourceWord<string_iter>;

    bool new_lines_enabled;
    // Parse source text and populate token buffer
    void scan();

    bool is_separator(char ch) const;

    bool can_terminate_statement(const Token& tok) const;
    

    Word get_word(string_iter pos);
   
    // This function analyzes last token in buffer, 
    // and if it is an end of statement token 
    // with newline value, it replace it with NewLine token. 
    // Otherwise does nothing
    void replace_end_of_statement();

    /*
     * Understands, if the next statement is going to be an XML one; does
     * not shift the iterator
     */
    bool xml_begins(string_iter iterator) {
        // XML must be preceded with whitespace, or either of brackets
        // If buffer is empty, skip this check
        if (!buf.empty()) {
            auto &prev = buf.back();
            if (!(prev.type == TokenType::Whitespace || prev.type == TokenType::OpenBracket ||
                  prev.type == TokenType::OpenBrace))
                return false;
        }

        // Then, goes the '<' symbol
        char next = *iterator;
        if (next != '<')
            return false;

        // Then, goes '_', base char or ideographic
        iterator++;
        next = *iterator;
        if (next == '_' || isalpha(next)) {
            iterator--;
            return true;
        }
        iterator--;
        return false;
    }

    /*
     * Analyzes the XML and shifts the iterator; assumes that XML is valid
     */
    void process_xml(string_iter &iterator) {
        // Take the first tag
        iterator++;
        char curChar = *iterator;
        std::string firstTag;
        firstTag += curChar;
        iterator++;
        while ((curChar = *iterator) != '>') {
            firstTag += curChar;
            iterator++;
        }

        // Now, we have the first tag and we need to proceed until
        // we find the closing first tag, </firstTag>
        std::string secondTag;
        while (iterator != source.end()) {
            secondTag = "";
            // Proceed until we find an open bracket
            iterator++;
            curChar = *iterator;
            if (curChar == '<') {
                // If the open bracket is followed by a slash, it is
                // a close tag
                iterator++;
                curChar = *iterator;
                if (curChar == '/') {
                    // Take the tag, which is closed by those brackets
                    iterator++;
                    while ((curChar = *iterator) != '>') {
                        secondTag += curChar;
                        iterator++;
                    }
                    // If this tag is equal to the first one, we found
                    // end of XML insertion
                    if (firstTag == secondTag)
                        break;
                }
            }
        }

        // If they are not equal, XML format is wrong
        if (firstTag != secondTag)
            throw InvalidXMLException();

        // Iterator is on the last close bracket, so move it forward
        iterator++;
    }

    enum class CommentType
    {
        Singleline,
        Multiline
    };

    bool comment_begins(string_iter& iterator)
    {
        // Comment begins with // or /*
        auto curChar = *iterator;
        if (curChar != '/')
            return false;

        iterator++;
        curChar = *iterator;

        if (curChar == '/')
        {
            process_comment(iterator, CommentType::Singleline);
            return true;
        }
        else if (curChar == '*')
        {
            process_comment(iterator, CommentType::Multiline);
            return true;
        }
        return false;
    }

    void process_comment(string_iter& iterator, CommentType commentType)
    {
        iterator++;
        auto curChar = *iterator;
        iterator++;

        if (commentType == CommentType::Singleline)
        {
            // Go until end of line is met
            while (curChar != '\n' && iterator != source.end())
            {
                curChar = *iterator;
                iterator++;
            }
        }
        else
        {
            while (iterator != source.end())
            {
                curChar = *iterator;
                if (curChar == '*')
                {
                    iterator++;
                    curChar = *iterator;
                    if (curChar == '/')
                        break;
                }
                iterator++;
            }
        }

        if (iterator != source.end())
            iterator++;
    }
};
}