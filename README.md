
# Lexer for Source Code Tokenization

This project implements a simple lexer (lexical analyzer) in C++ to tokenize source code into various types of tokens. It can recognize identifiers, keywords, operators, numbers, string literals, parentheses, and semicolons. The lexer is designed to be extended and can be used as a starting point for building more complex compilers or interpreters.

## Features

- Tokenizes a variety of programming elements:
  - **Identifiers** (e.g., variables like `x`, `y`)
  - **Keywords** (e.g., `int`, `float`, `return`)
  - **Operators** (e.g., `+`, `-`, `*`, `=`, `!=`)
  - **Numbers** (integer literals like `10`, `25`)
  - **String Literals** (enclosed in double quotes like `"hello world"`)
  - **Parentheses** (e.g., `(`, `)`)
  - **Semicolons** (used for statement termination)
- Detects errors in input source code and provides error messages for unexpected characters or invalid syntax.

## How to Run

1. **Clone or Download the Project**  
   Clone this repository or download the source code files.

2. **Compile the Code**  
   Use a C++ compiler like g++ to compile the code.  
   Example:
   ```bash
   g++ -o lexer lexer.cpp
   ```

3. **Run the Lexer**  
   After compilation, run the program as follows:
   ```bash
   ./lexer
   ```

4. **Input Source Code**  
   The program will prompt you to input the source code. Enter a piece of code, and the lexer will print out the token types and their corresponding values.

5. **Error Handling**  
   If the lexer encounters an unexpected character or invalid syntax, it will throw an error and display a message explaining the issue.

## Token Types

The lexer recognizes the following token types:

- `IDENTIFIER`: Variable names or user-defined identifiers.
- `NUMBER`: Numeric literals (integers).
- `OPERATOR`: Arithmetic and comparison operators (e.g., `+`, `=`, `!=`, `<`, `>`).
- `KEYWORD`: Reserved language keywords (e.g., `int`, `return`, `if`).
- `STRING`: String literals enclosed in double quotes.
- `PARENTHESIS`: Parentheses `(` and `)`.
- `ENDING`: Semicolons `;` that mark the end of statements.
- `END_OF_FILE`: Marks the end of the source code.

## Example

### Input:
```
int x = 10;
```

### Output:
```
Token Type: KEYWORD, Value: int
Token Type: IDENTIFIER, Value: x
Token Type: OPERATOR, Value: =
Token Type: NUMBER, Value: 10
Token Type: ENDING, Value: ;
```

## License

This project is open source and available under the MIT License. Feel free to modify and extend it as needed.

## Contributing

If you find any bugs or want to add more features, feel free to fork this repository and submit pull requests. Contributions are welcome!
