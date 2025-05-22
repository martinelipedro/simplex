#include "include/lexer.h"

#include <cctype>

Lexer::Lexer(std::string source) : source(source), current_char(source[0]), current_index(0) {}

void Lexer::advance()
{
    if (this->current_char)
    {
        this->current_index++;
        this->current_char = this->source[this->current_index];
    }
}

void Lexer::add_token(TokenType type, std::string value)
{
    this->token_list.push_back(Token(type, value));
}

void Lexer::collect_id()
{
    std::string buffer{};

    while (isalpha(this->current_char))
    {
        buffer += this->current_char;
        this->advance();
    }

    this->add_token(TokenType::ID, buffer);
}

void Lexer::collect()
{
    while (this->current_char)
    {
        if (isalpha(this->current_char))
        {
            this->collect_id();
        }

        switch (this->current_char)
        {
        case ' ':
        case '\n':
        case '\r':
            this->advance();
            break;
        case ';':
            this->add_token(TokenType::SEMI, ";");
            this->advance();
            break;
        case '(':
            this->add_token(TokenType::LPAREN, "(");
            this->advance();
            break;
        case ')':
            this->add_token(TokenType::RPAREN, ")");
            this->advance();
            break;
        case '=':
            this->add_token(TokenType::EQUALS, "=");
            this->advance();
            break;
        }
    }
}
