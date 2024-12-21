import tkinter as tk
from tkinter import ttk, messagebox

class TokenType:
    IDENTIFIER = "IDENTIFIER"
    NUMBER = "NUMBER"
    OPERATOR = "OPERATOR"
    KEYWORD = "KEYWORD"
    STRING = "STRING"
    PARENTHESIS = "PARENTHESIS"
    ENDING = "ENDING"
    END_OF_FILE = "END_OF_FILE"

class Token:
    def __init__(self, type_, value):
        self.type = type_
        self.value = value

class Lexer:
    def __init__(self, source):
        self.source = source
        self.position = 0
        self.keywords = {
            "int", "float", "double", "char", "void", "if", "else", "while", "for", 
            "return", "break", "continue", "switch", "case", "default", "struct", "class",
            "public", "private", "protected", "try", "catch", "throw",
            "const", "static", "true", "false"
        }

    def get_next_token(self):
        while self.position < len(self.source):
            char = self.source[self.position]
 
            if char.isspace():
                self.position += 1
                continue

            if char.isdigit():
                return self.tokenize_number()

            elif char.isalpha():
                return self.tokenize_identifier_or_keyword()

            elif char == '"':
                return self.tokenize_string_literal()

            elif self.is_operator(char):
                return self.tokenize_operator()

            elif char in ('(', ')'):
                return self.tokenize_parenthesis()

            elif char == ';':
                return self.tokenize_ending()

            raise RuntimeError(f"Unexpected character: '{char}' at position {self.position}")

        return Token(TokenType.END_OF_FILE, "")

    def tokenize_number(self):
        num = ''
        while self.position < len(self.source) and self.source[self.position].isdigit():
            num += self.source[self.position]
            self.position += 1

        return Token(TokenType.NUMBER, num)

    def tokenize_identifier_or_keyword(self):
        identifier = ''
        while self.position < len(self.source) and self.source[self.position].isalnum():
            identifier += self.source[self.position]
            self.position += 1

        if identifier in self.keywords:
            return Token(TokenType.KEYWORD, identifier)

        return Token(TokenType.IDENTIFIER, identifier)

    def tokenize_string_literal(self):
        self.position += 1
        str_val = ''

        while self.position < len(self.source) and self.source[self.position] != '"':
            str_val += self.source[self.position]
            self.position += 1

        if self.position >= len(self.source) or self.source[self.position] != '"':
            raise RuntimeError(f"Unterminated string literal at position {self.position}")

        self.position += 1
        return Token(TokenType.STRING, str_val)

    def tokenize_parenthesis(self):
        paren = self.source[self.position]
        self.position += 1
        return Token(TokenType.PARENTHESIS, paren)

    def tokenize_operator(self):
        op = self.source[self.position]
        self.position += 1

        if self.position < len(self.source):
            two_char_ops = {"<=", ">=", "==", "!="}
            potential_op = op + self.source[self.position]
            if potential_op in two_char_ops:
                op = potential_op
                self.position += 1

        return Token(TokenType.OPERATOR, op)

    def is_operator(self, char):
        return char in {'+', '-', '*', '/', '%', '=', '!', '<', '>'}

    def tokenize_ending(self):
        end = self.source[self.position]
        self.position += 1
        return Token(TokenType.ENDING, end)

def run_lexer():
    source_code = input_text.get("1.0", tk.END).strip()
    if not source_code:
        messagebox.showerror("Error", "No input provided!")
        return

    try:
        lexer = Lexer(source_code)
        tokens = []

        token = lexer.get_next_token()
        while token.type != TokenType.END_OF_FILE:
            tokens.append(token)
            token = lexer.get_next_token()

        tokens_list.delete(*tokens_list.get_children())
        for t in tokens:
            tokens_list.insert("", "end", values=(t.type, t.value))

    except RuntimeError as e:
        messagebox.showerror("Lexer Error", str(e))

app = tk.Tk()
app.title("Lexer GUI")
app.geometry("600x400")

tk.Label(app, text="Source Code:").pack(anchor="w", padx=10, pady=5)
input_text = tk.Text(app, height=10, wrap="word")
input_text.pack(fill="both", padx=10, pady=5, expand=True)

tk.Button(app, text="Run Lexer", command=run_lexer).pack(pady=10)

tokens_frame = ttk.Frame(app)
tokens_frame.pack(fill="both", padx=10, pady=5, expand=True)

tokens_list = ttk.Treeview(tokens_frame, columns=("Type", "Value"), show="headings")
tokens_list.heading("Type", text="Token Type")
tokens_list.heading("Value", text="Value")
tokens_list.pack(fill="both", expand=True)

app.mainloop()
