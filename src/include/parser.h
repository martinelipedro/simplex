#ifndef SIMPLEX_PARSER_H
#define SIMPLEX_PARSER_H

#include "ast.h"

class Parser
{
private:
    std::vector<Token> tokens;
    unsigned int current_index;
    Token *current_token;

    void advance();

public:
    Parser(std::vector<Token> tokens);
    Token *eat(TokenType type);
    ASTNode *parse();
    ASTNode *parse_statement();
    ASTNode *parse_expr();
    ASTNode *parse_term();
    ASTNode *parse_factor();
};

#endif