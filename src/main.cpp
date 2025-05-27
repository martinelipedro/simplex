#include "include/token.h"
#include "include/lexer.h"
#include <iostream>

int main()
{
    std::string source = "print(4568);";

    Lexer lexer = Lexer(source);
    lexer.collect();

    for (auto &token : lexer.token_list)
    {
        std::cout << token;
    }
}