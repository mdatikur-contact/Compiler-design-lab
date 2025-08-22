#include <iostream>
#include <fstream>
#include <regex>
#include <unordered_set>
#include <string>
#include <sstream>

using namespace std;

// List of C++ keywords
unordered_set<string> keywords = {
    "int", "float", "double", "char", "void", "if", "else", "while", "for",
    "return", "break", "continue", "switch", "case", "default", "struct",
    "class", "public", "private", "protected", "namespace", "template", "try", "catch"
};

// Function to identify token type
string identifyToken(const string& token) {
    // Check if the token is a keyword
    if (keywords.find(token) != keywords.end()) {
        return "keyword";
    }

    // Check if the token is a number (integer or float)
    regex numberRegex("^[+-]?([0-9]*[.])?[0-9]+$");
    if (regex_match(token, numberRegex)) {
        return "number";
    }

    // Check if the token is a valid identifier
    regex identifierRegex("^[a-zA-Z_][a-zA-Z0-9_]*$");
    if (regex_match(token, identifierRegex)) {
        return "identifier";
    }

    // Check if the token is a string literal
    regex stringLiteralRegex("^\".*\"$");
    if (regex_match(token, stringLiteralRegex)) {
        return "string literal";
    }

    // Check if the token is a character literal
    regex charLiteralRegex("^'.'$");
    if (regex_match(token, charLiteralRegex)) {
        return "char literal";
    }

    // Check if the token is an operator or symbol (e.g., +, -, *, ==, etc.)
    regex operatorRegex("^[\\+\\-\\*/%=<>!&|^~]+$");
    if (regex_match(token, operatorRegex)) {
        return "operator";
    }

    // Otherwise, classify it as a punctuation or unknown
    return "Delimeter";
}

int main() {
    string code;
    string line;

    // Read input from the file or standard input (for simplicity, read until EOF)
    cout << "Enter the preprocessed C++ code (type 'END' to stop input):\n";
    while (getline(cin, line)) {
        if (line == "END") {
            break;
        }
        code += line + "\n";
    }

    // Output file to store the tokens
    ofstream outputFile("tokens.txt");

    // Define a regex pattern to match possible tokens
    regex tokenRegex(R"(\s*([A-Za-z_][A-Za-z0-9_]*|[0-9]+(?:\.[0-9]+)?|\"[^\"]*\"|'.'|\S)\s*)");
    smatch matches;

    // Iterate through the code and find all tokens
    string::const_iterator searchStart(code.cbegin());
    while (regex_search(searchStart, code.cend(), matches, tokenRegex)) {
        string token = matches[1].str();

        // Ignore whitespace tokens
        if (token.empty() || token == " " || token == "\n" || token == "\t") {
            searchStart = matches.suffix().first;
            continue;
        }

        // Identify the token type
        string tokenType = identifyToken(token);

        // Output token and its type to the file
        outputFile << token << " - " << tokenType << endl;

        // Move to the next token
        searchStart = matches.suffix().first;
    }

    cout << "Tokens have been stored in 'tokens.txt'.\n";

    outputFile.close();
    return 0;
}

