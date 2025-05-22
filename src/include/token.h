#ifndef SIMPLEX_TOKEN_H
#define SIMPLEX_TOKEN_H

#include <cstdint>
#include <iostream>
#include <string>

enum class TokenType : uint8_t
{
    _EOF = 0,
    ID,
    NUMBER,
    SEMI,
    COMMA,
    LPAREN,
    RPAREN,
    EQUALS,
    PLUS,
    MINUS,
    STAR,
    SLASH,

};

class Token
{
private:
public:
    TokenType type;
    std::string value;

    Token(TokenType type, std::string value);
    friend std::ostream &operator<<(std::ostream &os, Token const &obj)
    {
        os << "(" << static_cast<int>(obj.type) << " : '" << obj.value << "')\n";
        return os;
    }
};

#endif
