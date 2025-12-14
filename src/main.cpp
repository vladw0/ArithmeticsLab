#include <iostream>
#include "expression.h"

int main()
{
    const char* expression = "(1+2)/(3+4*6.7)-5.3*4.4";
    char postfix[255];

    std::cout << "Checking brackets:" << std::endl;
    if (!TExpression::CheckBrackets(expression))
    {
        std::cout << "Errors found" << std::endl;
        return 0;
    }

    TExpression::InfixToPostfix(expression, postfix);

    std::cout << "Postfix form:" << std::endl;
    std::cout << postfix << std::endl;

    double result = TExpression::CalculatePostfix(postfix);

    std::cout << "Result:" << std::endl;
    std::cout << result << std::endl;

    return 0;
}