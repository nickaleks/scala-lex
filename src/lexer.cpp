#include "lexer.h"

using namespace lexer;
void Lexer::scan() 
{
    // lexer implementation goes here
    auto iterator = source.begin();
    while (iterator != source.end()) {
        auto word = get_word(iterator);
        if (xml_begins(iterator)) {
            process_xml(iterator);
            buf.emplace_back(TokenType::XMLInclusion);
        }
        else if (comment_begins(iterator)) {
            auto commentText = process_comment(iterator);
            buf.emplace_back(TokenType::Comment, std::string(commentText));
        }
        else {
            if (word == " ") {
                buf.emplace_back(TokenType::Whitespace);
            } else if (word == ",") {
                buf.emplace_back(TokenType::Comma);
            } else if (word == ".") {
                buf.emplace_back(TokenType::Dot);
            } else if (word == "abstract") {
                buf.emplace_back(TokenType::Abstract);
            } else if (word == "case") {
                buf.emplace_back(TokenType::Case);
            } else if (word == "catch") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::Catch);
            } else if (word == "class") {
                buf.emplace_back(TokenType::Class);
            } else if (word == "def") {
                buf.emplace_back(TokenType::Def);
            } else if (word == "do") {
                buf.emplace_back(TokenType::Do);
            } else if (word == "else") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::Else);
            } else if (word == "extends") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::Extends);
            } else if (word == "false") {
                buf.emplace_back(TokenType::False);
            } else if (word == "final") {
                buf.emplace_back(TokenType::Final);
            } else if (word == "finally") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::Finally);
            } else if (word == "for") {
                buf.emplace_back(TokenType::For);
            } else if (word == "forSome") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::ForSome);
            } else if (word == "if") {
                buf.emplace_back(TokenType::If);
            } else if (word == "implicit") {
                buf.emplace_back(TokenType::Implicit);
            } else if (word == "import") {
                buf.emplace_back(TokenType::Import);
            } else if (word == "lazy") {
                buf.emplace_back(TokenType::Lazy);
            } else if (word == "macro") {
                buf.emplace_back(TokenType::Macro);
            } else if (word == "match") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::Match);
            } else if (word == "new") {
                buf.emplace_back(TokenType::New);
            } else if (word == "null") {
                buf.emplace_back(TokenType::Null);
            } else if (word == "object") {
                buf.emplace_back(TokenType::Object);
            } else if (word == "override") {
                buf.emplace_back(TokenType::Override);
            } else if (word == "package") {
                buf.emplace_back(TokenType::Package);
            } else if (word == "private") {
                buf.emplace_back(TokenType::Private);
            } else if (word == "protected") {
                buf.emplace_back(TokenType::Protected);
            } else if (word == "return") {
                buf.emplace_back(TokenType::Return);
            } else if (word == "sealed") {
                buf.emplace_back(TokenType::Sealed);
            } else if (word == "super") {
                buf.emplace_back(TokenType::Super);
            } else if (word == "this") {
                buf.emplace_back(TokenType::This);
            } else if (word == "throw") {
                buf.emplace_back(TokenType::Throw);
            } else if (word == "trait") {
                buf.emplace_back(TokenType::Trait);
            } else if (word == "try") {
                buf.emplace_back(TokenType::Try);
            } else if (word == "true") {
                buf.emplace_back(TokenType::True);
            } else if (word == "type") {
                buf.emplace_back(TokenType::Type);
            } else if (word == "val") {
                buf.emplace_back(TokenType::Val);
            } else if (word == "var") {
                buf.emplace_back(TokenType::Var);
            } else if (word == "while") {
                buf.emplace_back(TokenType::While);
            } else if (word == "with") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::With);
            } else if (word == "yield") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::Yield);
            } else if (word == "_") {
                buf.emplace_back(TokenType::Underscore);
            } else if (word == ":") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::Colon);
            } else if (word == "=") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::Equal);
            } else if (word == "=>") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::Lambda);
            } else if (word == "<-") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::ForLoopIterator);
            } else if (word == "<:") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::UpperBounds);
            } else if (word == "<%") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::ViewBounds);
            } else if (word == ">:") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::LowerBounds);
            } else if (word == "#") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::TypeNotation);
            } else if (word == "@") {
                buf.emplace_back(TokenType::PatternMatching);
            } else if (word == "(") {
                buf.emplace_back(TokenType::OpenParenthesis);
                new_lines_enabled = false;
            } else if (word == ")") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::CloseParenthesis);
                new_lines_enabled = true;
            } else if (word == "{") {
                buf.emplace_back(TokenType::OpenBrace);
            } else if (word == "}") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::CloseBrace);
            } else if (word == "[") {
                replace_end_of_statement();
                new_lines_enabled = false;
                buf.emplace_back(TokenType::OpenBracket);
            } else if (word == "]") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::CloseBracket);
                new_lines_enabled = true;
            } else if (word == ";") {
                replace_end_of_statement();
                buf.emplace_back(TokenType::EndOfExpression, ";");
            } else if (word == "\n") {
                if (new_lines_enabled &&
                    can_terminate_statement(buf.back())) {
                    buf.emplace_back(TokenType::EndOfExpression, "\\n");
                } else {
                    buf.emplace_back(TokenType::NewLine);
                }
            } else if (word == "\t") {
                buf.emplace_back(TokenType::Tab);
            } else {
                buf.emplace_back(TokenType::InvalidToken, std::string(word));
            }
            iterator += word.length();
        }
    }
}

bool Lexer::is_separator(char ch) const 
{
    return ch == ' ' || ch == ',' || ch == '.' ||
            ch == '(' || ch == ')' || ch == '{' ||
            ch == '}' || ch == '[' || ch == ']' ||
            ch == '\n' || ch == ';' || ch == '\t';
}

bool Lexer::can_terminate_statement(const Token& tok) const 
{
    return tok.type == TokenType::This ||
           tok.type == TokenType::Null ||
           tok.type == TokenType::True ||
           tok.type == TokenType::False ||
           tok.type == TokenType::Return ||
           tok.type == TokenType::Type ||
           tok.type == TokenType::Underscore ||
           tok.type == TokenType::CloseParenthesis ||
           tok.type == TokenType::CloseBrace ||
           tok.type == TokenType::CloseBracket;
}

StringSlice Lexer::get_word(string_iter pos)
{
    char ch = *pos;
    auto begin = pos;
    size_t len = 1;
    if (is_separator(ch)) {
        return StringSlice{&(*begin), len};
    }
    while (!is_separator(ch) && pos != source.end()) {
        pos++;
        len++;
        ch = *pos;
    }
    return StringSlice{&(*begin), len - 1};
}

void Lexer::replace_end_of_statement()
{
    auto& prev = buf.back();
    if (prev.type == TokenType::EndOfExpression && prev.value == "\\n") {
        buf.pop_back();
        buf.emplace_back(TokenType::NewLine);
    }
}

bool Lexer::xml_begins(string_iter iterator) {
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

void Lexer::process_xml(string_iter &iterator) {
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

bool Lexer::comment_begins(const string_iter iterator)
{
    auto changeableIterator = iterator;
    // Comment begins with // or /*
    auto curChar = *changeableIterator;
    if (curChar != '/')
        return false;

    changeableIterator++;
    curChar = *changeableIterator;

    return curChar == '/' || curChar == '*';
}

StringSlice Lexer::process_comment(string_iter& iterator)
{
    auto begin = iterator;
    size_t len = 2;
    iterator++;
    auto curChar = *iterator;
    iterator++;

    if (curChar == '/')
    {
        // Go until end of line or end of file is met
        while (curChar != '\n' && iterator != source.end())
        {
            curChar = *iterator;
            iterator++;
            len++;
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
                len++;
                curChar = *iterator;
                if (curChar == '/')
                    break;
            }
            iterator++;
            len++;
        }
    }

    if (iterator != source.end())
    {
        iterator++;
        len++;
    }

    return StringSlice{&(*begin), len};
}