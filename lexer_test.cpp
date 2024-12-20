#include <gtest/gtest.h>
#include "project system.cpp" // Include your lexer implementation

// Test case for tokenizing a number
TEST(LexerTests, TokenizeNumber) {
    Lexer lexer("42");
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.type, NUMBER);
    EXPECT_EQ(token.value, "42");
}

// Test case for tokenizing an identifier
TEST(LexerTests, TokenizeIdentifier) {
    Lexer lexer("variable");
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.type, IDENTIFIER);
    EXPECT_EQ(token.value, "variable");
}

// Test case for tokenizing a keyword
TEST(LexerTests, TokenizeKeyword) {
    Lexer lexer("int");
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.type, KEYWORD);
    EXPECT_EQ(token.value, "int");
}

// Test case for tokenizing an operator
TEST(LexerTests, TokenizeOperator) {
    Lexer lexer("+");
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.type, OPERATOR);
    EXPECT_EQ(token.value, "+");
}

// Test case for tokenizing a string
TEST(LexerTests, TokenizeString) {
    Lexer lexer("\"hello\"");
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.type, STRING);
    EXPECT_EQ(token.value, "hello");
}

// Test case for handling unexpected characters
TEST(LexerTests, UnexpectedCharacter) {
    Lexer lexer("@");
    try {
        lexer.getNextToken();
        FAIL() << "Expected runtime_error";
    } catch (const std::runtime_error& e) {
        EXPECT_EQ(string(e.what()), "Unexpected character: '@' at position 0");
    }
}

// Test case for tokenizing multiple tokens
TEST(LexerTests, MultipleTokens) {
    Lexer lexer("int x = 42;");
    Token token = lexer.getNextToken();
    EXPECT_EQ(token.type, KEYWORD);
    EXPECT_EQ(token.value, "int");

    token = lexer.getNextToken();
    EXPECT_EQ(token.type, IDENTIFIER);
    EXPECT_EQ(token.value, "x");

    token = lexer.getNextToken();
    EXPECT_EQ(token.type, OPERATOR);
    EXPECT_EQ(token.value, "=");

    token = lexer.getNextToken();
    EXPECT_EQ(token.type, NUMBER);
    EXPECT_EQ(token.value, "42");

    token = lexer.getNextToken();
    EXPECT_EQ(token.type, ENDING);
    EXPECT_EQ(token.value, ";");
}
