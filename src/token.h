#include <string>
#include <unordered_map>

namespace lexer {

    enum class TokenType {
        // Prefix  is because some of them are C++ reserved words as well
        Abstract, Case, Catch, Class, Def,
        Do, Else, False, Final, Extends,
        Finally, For, ForSome, If, Implicit,
        Import, Lazy, Macro, Match, New,
        Null, Object, Override, Package, Private,
        Protected, Return, Sealed, Super, This,
        Throw, Trait, Try, True, Type,
        Val, Var, While, With, Yield,
        Whitespace, Underscore, Colon, Equal,
        Comma,              // ,
        Dot,                // .
        Lambda,             // =>
        ForLoopIterator,    // <-
        UpperBounds,        // <:
        LowerBounds,        // >:
        ViewBounds,         // <%
        TypeNotation,       // #
        PatternMatching,    // @
        EndOfExpression,
        OpenParenthesis,
        CloseParenthesis,
        OpenBrace,
        CloseBrace,
        OpenBracket,
        CloseBracket,
        NewLine,
        Tab,
        XMLInclusion,
        InvalidToken
    };

    class Token {
    public:
        TokenType type;
        std::string value;

        Token(TokenType type, std::string value) : type{type}, value{value} {};

        Token(TokenType type) : type{type}, value{""} {};

        static const std::unordered_map<lexer::TokenType, std::string> to_string;
    };
}