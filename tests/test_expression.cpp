#include <gtest/gtest.h>
#include "expression.h"

// ---------- Brackets ----------

TEST(BracketsTest, CorrectBrackets)
{
    const char* expr = "(1+2)*(3+4)";
    EXPECT_TRUE(TExpression::CheckBrackets(expr));
}

TEST(BracketsTest, IncorrectBrackets)
{
    const char* expr = "(1+2)*(3+4";
    EXPECT_FALSE(TExpression::CheckBrackets(expr));
}

// ---------- Infix -> Postfix ----------

TEST(PostfixTest, SimpleExpression)
{
    const char* infix = "1+2";
    char postfix[255];

    TExpression::InfixToPostfix(infix, postfix);
    EXPECT_STREQ(postfix, "1 2 +");
}

TEST(PostfixTest, ComplexExpression)
{
    const char* infix = "(1+2)/(3+4)";
    char postfix[255];

    TExpression::InfixToPostfix(infix, postfix);
    EXPECT_STREQ(postfix, "1 2 + 3 4 + /");
}

// ---------- Calculation ----------

TEST(CalcTest, SimpleCalc)
{
    const char* postfix = "1 2 +";
    double result = TExpression::CalculatePostfix(postfix);

    EXPECT_DOUBLE_EQ(result, 3.0);
}

TEST(CalcTest, ComplexCalc)
{
    const char* postfix = "1 2 + 3 4 + /";
    double result = TExpression::CalculatePostfix(postfix);

    EXPECT_DOUBLE_EQ(result, 3.0 / 7.0);
}