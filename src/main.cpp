#include "include/parser.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    std::ifstream input("code.sx");
    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string source = buffer.str();

    Lexer lexer = Lexer(source);
    lexer.collect();

    printf("Tokens: \n");
    for (auto &token : lexer.token_list)
    {
        std::cout << token;
    }

    printf("\n\nAST: \n");

    Parser parser = Parser(lexer.token_list);
    ASTNode *root = parser.parse();

    root->print(0);
}