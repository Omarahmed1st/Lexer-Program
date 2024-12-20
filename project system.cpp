#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <stdexcept> // For standard exceptions
#include <unordered_set>

using namespace std;

enum TokenType {
    IDENTIFIER, 
    NUMBER,      
    OPERATOR,    
    KEYWORD,     // Keywords like int, return, etc.
    STRING,      
    PARENTHESIS, 
    ENDING,
    END_OF_FILE  // End of input
};

struct Token {
    TokenType type;
    string value;
};

class Lexer {
public:
    explicit Lexer(const string& source) : source(source), position(0) {}

    Token getNextToken() {
        try {
            // Loop to skip whitespace and read characters
            while (position < source.length()) {
                if (isspace(source[position])) {
                    position++; 
                    continue;
                }

                if (isdigit(source[position])) {
                    return tokenizeNumber();
                }
                else if (isalpha(source[position])) {
                    return tokenizeIdentifierOrKeyword();
                }
                
                else if (source[position] == '"') {
                    return tokenizeStringLiteral();
                }
                else if (isOperator(source[position])) {
                    return tokenizeOperator();
                }
                else if (source[position] == '(' || source[position] == ')') {
                    return tokenizeParenthesis();
                }
                else if (source[position] == ';') {
                    return tokenizeEnding();
                }

                throw runtime_error("Unexpected character: '" + string(1, source[position]) + "' at position " + to_string(position));
            }

            return {END_OF_FILE, ""};
        } catch (const exception& e) {
            cerr << "Lexer Error: " << e.what() << endl;
            exit(1); // Exit the program with an error code
        }
    }

private:
    unordered_set<string> keywords = {
        "int", "float", "double", "char", "void", "if", "else", "while", "for", 
        "return", "break", "continue", "switch", "case", "default", "struct", "class",
        "public", "private", "protected", "try", "catch", "throw", "new", "delete", 
        "const", "static", "volatile", "sizeof", "namespace", "true", "false", "inline"
    };

    Token tokenizeNumber() {
        string num;
        while (position < source.length() && isdigit(source[position])) {
            num += source[position++];
        }

        if (num.empty()) {
            throw runtime_error("Invalid number token at position " + to_string(position));
        }

        return {NUMBER, num};
    }

    Token tokenizeIdentifierOrKeyword() {
        string id;
        while (position < source.length() && isalnum(source[position])) {
            id += source[position++];
        }

        if (id.empty()) {
            throw runtime_error("Invalid identifier token at position " + to_string(position));
        }

        if (keywords.find(id) != keywords.end()) {
            return {KEYWORD, id};
        }

        return {IDENTIFIER, id};
    }

    Token tokenizeStringLiteral() {
        string str;
        position++; 

        while (position < source.length() && source[position] != '"') {
            str += source[position++];
        }

        if (position >= source.length() || source[position] != '"') {
            throw runtime_error("Unterminated string literal at position " + to_string(position));
        }

        position++; 
        return {STRING, str};
    }

    Token tokenizeParenthesis() {
        string paren(1, source[position++]);
        return {PARENTHESIS, paren};
    }

    Token tokenizeOperator() {
        string op(1, source[position++]);

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

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '=' || 
                c == '!' || c == '<' || c == '>');
    }

    Token tokenizeEnding() {
        string end;
        end += source[position++];
        return {ENDING, end};
    }

    string source; 
    size_t position;
};

int main() {
    try {
        string input;
        char continueInput = 'y';
        
        while (continueInput == 'y') {
            cout << "Enter the source code: ";
            getline(cin, input);

            if (input.empty()) {
                throw runtime_error("No input provided.");
            }

            Lexer lexer(input);
            vector<Token> tokens;

            Token token;
            while ((token = lexer.getNextToken()).type != END_OF_FILE) {
                tokens.push_back(token);
            }


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

            cout << "Do you want to continue (y/n)? ";
            cin >> continueInput; 
            cin.ignore();

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
