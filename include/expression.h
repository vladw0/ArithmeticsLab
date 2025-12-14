#pragma once

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "stack.h"

class TExpression
{
private:
    static int GetPriority(char operation)
    {
        if (operation == '(')
        {
            return 0;
        }
        if (operation == '+' || operation == '-')
        {
            return 1;
        }
        if (operation == '*' || operation == '/')
        {
            return 2;
        }
        return -1;
    }

public:
    // Проверка расстановки скобок
    static bool CheckBrackets(const char* expression)
    {
        TStack<int> stack(255);
        int bracketIndex = 0;
        bool hasErrors = false;

        for (int index = 0; expression[index] != '\0'; index++)
        {
            if (expression[index] == '(')
            {
                bracketIndex++;
                stack.Push(bracketIndex);
            }
            else if (expression[index] == ')')
            {
                bracketIndex++;
                if (stack.IsEmpty())
                {
                    std::cout << "- " << bracketIndex << std::endl;
                    hasErrors = true;
                }
                else
                {
                    int openIndex = stack.Pop();
                    std::cout << openIndex << " " << bracketIndex << std::endl;
                }
            }
        }

        while (!stack.IsEmpty())
        {
            int openIndex = stack.Pop();
            std::cout << openIndex << " -" << std::endl;
            hasErrors = true;
        }

        return !hasErrors;
    }

    // Перевод в постфиксную форму
    static void InfixToPostfix(const char* infix, char* postfix)
    {
        TStack<char> stack(255);
        int outputIndex = 0;

        for (int index = 0; infix[index] != '\0'; index++)
        {
            char symbol = infix[index];

            if ((symbol >= '0' && symbol <= '9') || symbol == '.')
            {
                postfix[outputIndex] = symbol;
                outputIndex++;
            }
            else
            {
                postfix[outputIndex] = ' ';
                outputIndex++;

                if (symbol == '(')
                {
                    stack.Push(symbol);
                }
                else if (symbol == ')')
                {
                    while (!stack.IsEmpty() && stack.Top() != '(')
                    {
                        postfix[outputIndex] = stack.Pop();
                        outputIndex++;
                        postfix[outputIndex] = ' ';
                        outputIndex++;
                    }
                    stack.Pop();
                }
                else
                {
                    while (!stack.IsEmpty() &&
                           GetPriority(stack.Top()) >= GetPriority(symbol))
                    {
                        postfix[outputIndex] = stack.Pop();
                        outputIndex++;
                        postfix[outputIndex] = ' ';
                        outputIndex++;
                    }
                    stack.Push(symbol);
                }
            }
        }

        while (!stack.IsEmpty())
        {
            postfix[outputIndex] = ' ';
            outputIndex++;
            postfix[outputIndex] = stack.Pop();
            outputIndex++;
        }

        postfix[outputIndex] = '\0';
    }

    // Вычисление постфиксного выражения
    static double CalculatePostfix(const char* postfix)
    {
        TStack<double> stack(255);
        char buffer[64];
        int bufferIndex = 0;

        for (int index = 0; postfix[index] != '\0'; index++)
        {
            if (postfix[index] == ' ')
            {
                if (bufferIndex > 0)
                {
                    buffer[bufferIndex] = '\0';
                    double value = atof(buffer);
                    stack.Push(value);
                    bufferIndex = 0;
                }
            }
            else if (postfix[index] == '+' || postfix[index] == '-' ||
                     postfix[index] == '*' || postfix[index] == '/')
            {
                double right = stack.Pop();
                double left = stack.Pop();
                double result = 0.0;

                if (postfix[index] == '+')
                {
                    result = left + right;
                }
                else if (postfix[index] == '-')
                {
                    result = left - right;
                }
                else if (postfix[index] == '*')
                {
                    result = left * right;
                }
                else if (postfix[index] == '/')
                {
                    result = left / right;
                }

                stack.Push(result);
            }
            else
            {
                buffer[bufferIndex] = postfix[index];
                bufferIndex++;
            }
        }

        return stack.Pop();
    }
};