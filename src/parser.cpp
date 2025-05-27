#include "include/parser.h"

Parser::Parser(std::vector<Token> tokens) : tokens(tokens)
{
    this->current_index = 0;
    this->current_token = &this->tokens[0];

    if (this->tokens.size() < 1)
    {
        printf("Missing tokens, exiting...");
        exit(1);
    }
}

void Parser::advance()
{
    this->current_index++;
    if (this->current_index < this->tokens.size())
    {
        this->current_token = &this->tokens[this->current_index];
        return;
    }

    this->current_token = new Token(TokenType::_EOF, "\0");
}

Token *Parser::eat(TokenType type)
{
    Token *consumed;

    if (this->current_token->type == type)
    {
        consumed = this->current_token;
        this->advance();
        return consumed;
    }

    printf("Was expecting %d, got %d. Exiting...", static_cast<int>(type), static_cast<int>(this->current_token->type));
    exit(1);
    return nullptr;
}

ASTNode *Parser::parse()
{
    ASTNode *root = this->parse_statement();

    if (this->current_token->type != TokenType::_EOF)
        printf("Error, more tokens than expected...");

    return root;
}

ASTNode *Parser::parse_statement()
{
    return this->parse_expr();
}

ASTNode *Parser::parse_expr()
{
    ASTNode *node = this->parse_term();

    while (this->current_token->type == TokenType::PLUS || this->current_token->type == TokenType::MINUS)
    {
        Token *op = this->current_token;
        this->advance();
        ASTNode *right = this->parse_term();
        node = new BinaryOpNode(node, op->type, right);
    }

    return node;
}

ASTNode *Parser::parse_term()
{
    ASTNode *node = this->parse_factor();

    while (this->current_token->type == TokenType::STAR || this->current_token->type == TokenType::SLASH)
    {
        Token *op = this->current_token;
        this->advance();
        ASTNode *right = this->parse_factor();
        node = new BinaryOpNode(node, op->type, right);
    }

    return node;
}

ASTNode *Parser::parse_factor()
{
    Token *tok = this->current_token;

    if (tok->type == TokenType::NUMBER)
    {
        this->eat(TokenType::NUMBER);
        return new NumberNode(std::stod(tok->value));
    }
    else if (tok->type == TokenType::LPAREN)
    {
        this->eat(TokenType::LPAREN);
        ASTNode *expr = this->parse_expr();
        this->eat(TokenType::RPAREN);
        return expr;
    }

    printf("Error parsing factor!");
    exit(1);
}