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

void Lexer::collect_number()
{
    std::string buffer{};
    unsigned int dot_count = 0;

    while (isdigit(this->current_char) || this->current_char == '.')
    {
        if (dot_count > 2)
        {
            printf("Two dots in a single number! Exiting");
            exit(1);
        }

        if (this->current_char == '.')
            dot_count++;

        buffer += this->current_char;
        this->advance();
    }

    this->add_token(TokenType::NUMBER, buffer);
}

void Lexer::collect()
{
    while (this->current_char)
    {
        if (isalpha(this->current_char))
        {
            this->collect_id();
        }
        else if (isdigit(this->current_char))
        {
            this->collect_number();
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
        case '+':
            this->add_token(TokenType::PLUS, "+");
            this->advance();
            break;
        case '-':
            this->add_token(TokenType::MINUS, "-");
            this->advance();
            break;
        case '*':
            this->add_token(TokenType::STAR, "*");
            this->advance();
            break;
        case '/':
            this->add_token(TokenType::SLASH, "/");
            this->advance();
            break;
        }
    }
}
