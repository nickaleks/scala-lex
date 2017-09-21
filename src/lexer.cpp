#include "lexer.h"
#include <iostream>

void lexer::Lexer::scan() {
    // lexer implementation goes here
    auto iterator = source.begin();
    while (iterator != source.end()) {
        auto word = getWord(iterator);

        if (word == " ") {
            buf.emplace_back(TokenType::Whitespace);
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
        } else if (word== "(") {
            buf.emplace_back(TokenType::OpenParenthesis);
            new_lines_enabled = false;
        } else if (word== ")") {
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
            buf.emplace_back(TokenType::InvalidToken);
        }
        iterator += word.len;
    }
}