#include "include/token.h"
#include "include/lexer.h"
#include <iostream>

int main()
{
    std::string source = "print(variable);";

    Lexer lexer = Lexer(source);
    lexer.collect();

    for (auto &token : lexer.token_list)
    {
        std::cout << token;
    }
}