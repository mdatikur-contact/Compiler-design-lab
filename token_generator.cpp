#include <bits/stdc++.h>
using namespace std;

unordered_set<string> keywords = {
    "int", "float", "double", "char", "void", "if", "else", "while", "for",
    "return", "break", "continue", "switch", "case", "default", "struct",
    "class", "public", "private", "protected", "namespace", "template", "try", "catch"
};

// Function to classify tokens
string tokenType(const string& token, const string& nextToken) {
    // Preprocessor directives
    if (regex_match(token, regex("^#.*$"))) return "preprocessor directive";

    // Header file detection <stdio.h> or "myheader.h"
    if (regex_match(token, regex("^<.*>$")) || regex_match(token, regex("^\".*\"$")))
        return "header file";

    // Keywords
    if (keywords.count(token)) return "keyword";

    // Function check: identifier followed by "("
    if (regex_match(token, regex("^[a-zA-Z_][a-zA-Z0-9_]*$")) && nextToken == "(")
        return "function";

    // Valid identifier
    if (regex_match(token, regex("^[a-zA-Z_][a-zA-Z0-9_]*$")))
        return "identifier";

    // Invalid identifier (starts with number but has letters/underscores)
    if (regex_match(token, regex("^[0-9][a-zA-Z0-9_]+$")))
        return "invalid identifier";

    // Numbers
    if (regex_match(token, regex("^[+-]?[0-9]+(\\.[0-9]+)?$")))
        return "number";

    // String
    if (regex_match(token, regex("^\".*\"$")))
        return "string";

    // Char
    if (regex_match(token, regex("^'.'$")))
        return "char";

    // Operators
    if (regex_match(token, regex("^[+*/%=<>!&|^~\\-]+$")))
        return "operator";

    return "delimiter";
}

int main() {
    ifstream file("test.txt");
 
    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Regex now includes #include and <header>
    regex tokenRegex("(#\\w+|<[^>]+>|\"[^\"]+\"|[a-zA-Z_][a-zA-Z0-9_]*|[0-9][a-zA-Z0-9_]+|[0-9]+(\\.[0-9]+)?|'.'|[+*/%=<>!&|^~\\-]+|;|\\(|\\)|\\{|\\}|\\[|\\])");
    smatch match;
    string::const_iterator start = code.cbegin();

    vector<string> tokens;

    // Collect all tokens first
    while (regex_search(start, code.cend(), match, tokenRegex)) {
        tokens.push_back(match.str());
        start = match.suffix().first;
    }

    // Classify with lookahead (for functions)
    for (size_t i = 0; i < tokens.size(); i++) {
        string next = (i + 1 < tokens.size()) ? tokens[i + 1] : "";
        cout << tokens[i] << " >> is a " << tokenType(tokens[i], next) << endl;
    }
}
