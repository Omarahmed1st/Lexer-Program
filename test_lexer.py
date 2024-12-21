import pytest
from lexer import Lexer, Token, TokenType


# Test for basic tokenization of a number
def test_tokenize_number():
    lexer = Lexer("123")
    token = lexer.get_next_token()
    assert token.type == TokenType.NUMBER
    assert token.value == "123"


# Test for tokenizing an identifier
def test_tokenize_identifier():
    lexer = Lexer("myVariable")
    token = lexer.get_next_token()
    assert token.type == TokenType.IDENTIFIER
    assert token.value == "myVariable"


# Test for tokenizing a keyword
def test_tokenize_keyword():
    lexer = Lexer("int")
    token = lexer.get_next_token()
    assert token.type == TokenType.KEYWORD
    assert token.value == "int"


# Test for tokenizing a string literal
def test_tokenize_string():
    lexer = Lexer('"Hello, World!"')
    token = lexer.get_next_token()
    assert token.type == TokenType.STRING
    assert token.value == "Hello, World!"


# Test for tokenizing an operator
def test_tokenize_operator():
    lexer = Lexer("+")
    token = lexer.get_next_token()
    assert token.type == TokenType.OPERATOR
    assert token.value == "+"


# Test for handling two-character operators like <=
def test_tokenize_two_char_operator():
    lexer = Lexer("<=")
    token = lexer.get_next_token()
    assert token.type == TokenType.OPERATOR
    assert token.value == "<="


# Test for tokenizing parentheses
def test_tokenize_parentheses():
    lexer = Lexer("()")
    token = lexer.get_next_token()
    assert token.type == TokenType.PARENTHESIS
    assert token.value == "("
    
    token = lexer.get_next_token()
    assert token.type == TokenType.PARENTHESIS
    assert token.value == ")"


# Test for tokenizing semicolons
def test_tokenize_ending():
    lexer = Lexer(";")
    token = lexer.get_next_token()
    assert token.type == TokenType.ENDING
    assert token.value == ";"


# Test for invalid number token (empty number)
def test_invalid_number():
    lexer = Lexer("abc 123")
    with pytest.raises(RuntimeError):
        lexer.get_next_token()


# Test for invalid character (unexpected character)
def test_invalid_character():
    lexer = Lexer("$")
    with pytest.raises(RuntimeError):
        lexer.get_next_token()


# Test for handling an empty input (EOF)
def test_end_of_file():
    lexer = Lexer("")
    token = lexer.get_next_token()
    assert token.type == TokenType.END_OF_FILE
    assert token.value == ""


# Test for handling a mix of tokens
def test_mixed_tokens():
    lexer = Lexer('int x = 10 + 20;')
    token = lexer.get_next_token()
    assert token.type == TokenType.KEYWORD
    assert token.value == "int"
    
    token = lexer.get_next_token()
    assert token.type == TokenType.IDENTIFIER
    assert token.value == "x"
    
    token = lexer.get_next_token()
    assert token.type == TokenType.OPERATOR
    assert token.value == "="
    
    token = lexer.get_next_token()
    assert token.type == TokenType.NUMBER
    assert token.value == "10"
    
    token = lexer.get_next_token()
    assert token.type == TokenType.OPERATOR
    assert token.value == "+"
    
    token = lexer.get_next_token()
    assert token.type == TokenType.NUMBER
    assert token.value == "20"
    
    token = lexer.get_next_token()
    assert token.type == TokenType.ENDING
    assert token.value == ";"


# Test for handling invalid string literal (unterminated string)
def test_invalid_string_literal():
    lexer = Lexer('"Unterminated string')
    with pytest.raises(RuntimeError):
        lexer.get_next_token()


# Test for keywords
@pytest.mark.parametrize("keyword", [
    "int", "float", "double", "char", "void", "if", "else", "while", "for", 
    "return", "break", "continue", "switch", "case", "default", "struct", "class",
    "public", "private", "protected", "try", "catch", "throw", 
    "const", "static", "true", "false"
])
def test_keywords(keyword):
    lexer = Lexer(keyword)
    token = lexer.get_next_token()
    assert token.type == TokenType.KEYWORD
    assert token.value == keyword
