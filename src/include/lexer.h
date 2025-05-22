#ifndef SIMPLEX_LEXER_H
#define SIMPLEX_LEXER_H

#include "token.h"
#include <vector>

class Lexer
{
private:
    std::string source;
    char current_char;
    unsigned int current_index;

    void advance();
    void add_token(TokenType type, std::string value);
    void collect_id();
    void collect_number();

public:
    std::vector<Token> token_list;

    Lexer(std::string source);
    void collect();
};

#endif