#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <stdexcept> // For standard exceptions
#include <unordered_set>

using namespace std;

// Define token types using an enumeration
enum TokenType {
    IDENTIFIER,  // Variables like x, y, etc.
    NUMBER,      // Numeric literals like 10, 20
    OPERATOR,    // Operators like +, -, =, *, /, %, <, >, <=, >=, !=
    KEYWORD,     // Keywords like int, return, etc.
    STRING,      // String literals
    PARENTHESIS, // Parentheses like ( )
    ENDING,
    END_OF_FILE  // End of input
};

// Structure to store a token and its type
struct Token {
    TokenType type;
    string value;
};

// Lexer class to perform lexical analysis
class Lexer {
public:
    // Constructor takes the input source code
    explicit Lexer(const string& source) : source(source), position(0) {}

    // Function to get the next token from the input
    Token getNextToken() {
        try {
            // Loop to skip whitespace and read characters
            while (position < source.length()) {
                if (isspace(source[position])) {
                    position++; // Skip spaces
                    continue;
                }

                // Check if the character is a digit (number)
                if (isdigit(source[position])) {
                    return tokenizeNumber();
                }
                // Check if the character is a letter (identifier or keyword)
                else if (isalpha(source[position])) {
                    return tokenizeIdentifierOrKeyword();
                }
                // Check if the character is a string literal (starts with ")
                else if (source[position] == '"') {
                    return tokenizeStringLiteral();
                }
                // Check if the character is an operator (including comparison operators)
                else if (isOperator(source[position])) {
                    return tokenizeOperator();
                }
                // Check if the character is a parenthesis
                else if (source[position] == '(' || source[position] == ')') {
                    return tokenizeParenthesis();
                }
                // Check if the character is a semicolon (ending token)
                else if (source[position] == ';') {
                    return tokenizeEnding();
                }

                // If we encounter an unexpected character, throw an exception
                throw runtime_error("Unexpected character: '" + string(1, source[position]) + "' at position " + to_string(position));
            }

            // If no more characters, return an END_OF_FILE token
            return {END_OF_FILE, ""};
        } catch (const exception& e) {
            cerr << "Lexer Error: " << e.what() << endl;
            exit(1); // Exit the program with an error code
        }
    }

private:
    // Set of common recognized keywords
    unordered_set<string> keywords = {
        "int", "float", "double", "char", "void", "if", "else", "while", "for", 
        "return", "break", "continue", "switch", "case", "default", "struct", "class",
        "public", "private", "protected", "try", "catch", "throw", "new", "delete", 
        "const", "static", "volatile", "sizeof", "namespace", "true", "false", "inline"
    };

    // Helper function to tokenize a number
    Token tokenizeNumber() {
        string num;
        // Read digits and build the number string
        while (position < source.length() && isdigit(source[position])) {
            num += source[position++];
        }

        if (num.empty()) {
            throw runtime_error("Invalid number token at position " + to_string(position));
        }

        return {NUMBER, num};
    }

    // Helper function to tokenize an identifier or keyword
    Token tokenizeIdentifierOrKeyword() {
        string id;
        // Read letters and digits to form the identifier
        while (position < source.length() && isalnum(source[position])) {
            id += source[position++];
        }

        if (id.empty()) {
            throw runtime_error("Invalid identifier token at position " + to_string(position));
        }

        // Check if the identifier is a keyword
        if (keywords.find(id) != keywords.end()) {
            return {KEYWORD, id};
        }

        return {IDENTIFIER, id};
    }

    // Helper function to tokenize string literals (enclosed in double quotes)
    Token tokenizeStringLiteral() {
        string str;
        position++; // Skip the opening quote

        // Read characters inside the string literal
        while (position < source.length() && source[position] != '"') {
            str += source[position++];
        }

        // If we reach the end of the string without finding a closing quote, it's an error
        if (position >= source.length() || source[position] != '"') {
            throw runtime_error("Unterminated string literal at position " + to_string(position));
        }

        position++; // Skip the closing quote
        return {STRING, str};
    }

    // Helper function to tokenize parentheses
    Token tokenizeParenthesis() {
        string paren(1, source[position++]);
        return {PARENTHESIS, paren};
    }

    // Helper function to tokenize operators (including comparison operators)
    Token tokenizeOperator() {
        string op(1, source[position++]);

        // Handle two-character operators
        if (position < source.length()) {
            if ((op == "<" && source[position] == '=') || 
                (op == ">" && source[position] == '=') ||
                (op == "=" && source[position] == '=') || 
                (op == "!" && source[position] == '=')) {
                op += source[position++];
            }
        }

        return {OPERATOR, op};
    }

    // Helper function to check if a character is a valid operator
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || 
                c == '!' || c == '<' || c == '>');
    }

    // Helper function to tokenize semicolon as an "ENDING" token
    Token tokenizeEnding() {
        string end;
        end += source[position++];
        return {ENDING, end};
    }

    string source; // The input source code
    size_t position; // The current position in the input
};

int main() {
    try {
        string input;
        char continueInput = 'y';
        
        // Loop to repeatedly ask the user for source code
        while (continueInput == 'y') {
            cout << "Enter the source code: ";
            getline(cin, input); // Get user input for source code

            if (input.empty()) {
                throw runtime_error("No input provided.");
            }

            Lexer lexer(input);
            vector<Token> tokens;

            // Read tokens until we reach the end of the file
            Token token;
            while ((token = lexer.getNextToken()).type != END_OF_FILE) {
                tokens.push_back(token);
            }

            // Print the tokens
            for (const auto& t : tokens) {
                cout << "Token Type: ";
                switch (t.type) {
                    case IDENTIFIER:
                        cout << "IDENTIFIER";
                        break;
                    case NUMBER:
                        cout << "NUMBER";
                        break;
                    case OPERATOR:
                        cout << "OPERATOR";
                        break;
                    case KEYWORD:
                        cout << "KEYWORD";
                        break;
                    case STRING:
                        cout << "STRING";
                        break;
                    case PARENTHESIS:
                        cout << "PARENTHESIS";
                        break;
                    case ENDING:
                        cout << "ENDING";
                        break;
                    default:
                        break;
                }
                cout << ", Value: " << t.value << endl;
            }

            // Ask if the user wants to continue
            cout << "Do you want to continue (y/n)? ";
            cin >> continueInput; // Get input to check if the user wants to continue
            cin.ignore(); // Ignore the newline left in the input buffer

            // If the user answers "n" (no), exit the loop and halt
            if (continueInput == 'n') {
                cout << "Exiting the program." << endl;
                break;
            }
        }
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1; // Exit with an error code
    }

    return 0;
}