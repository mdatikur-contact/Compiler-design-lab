#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <unordered_set>
using namespace std;

unordered_set<string> keywords = {
    "int", "float", "double", "char", "void", "if", "else", "while", "for",
    "return", "break", "continue", "switch", "case", "default", "struct",
    "class", "public", "private", "protected", "namespace", "template", "try", "catch"
};

// Function to identify token type
string tokenType(const string& token, const string& nextToken) {
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

    if (regex_match(token, regex("^[+-]?[0-9]+(\\.[0-9]+)?$"))) return "number";
    if (regex_match(token, regex("^\".*\"$"))) return "string";
    if (regex_match(token, regex("^'.'$"))) return "char";
    if (regex_match(token, regex("^[+*/%=<>!&|^~\\-]+$"))) return "operator";

    return "delimiter";
}

int main() {
    ifstream file("test.txt");
    if (!file.is_open()) {
        cerr << "Error: cannot open file\n";
        return 1;
    }

    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Updated regex: also match invalid identifiers like 1num
    regex tokenRegex("([a-zA-Z_][a-zA-Z0-9_]*|[0-9][a-zA-Z0-9_]+|[0-9]+(\\.[0-9]+)?|\"[^\"]*\"|'.'|[+*/%=<>!&|^~\\-]+|;|\\(|\\)|\\{|\\}|\\[|\\])");
    smatch match;
    string::const_iterator start = code.cbegin();

    vector<string> tokens;

    // Collect all tokens first
    while (regex_search(start, code.cend(), match, tokenRegex)) {
        tokens.push_back(match.str());
        start = match.suffix().first;
    }

    // Now classify with lookahead (for functions)
    for (size_t i = 0; i < tokens.size(); i++) {
        string next = (i + 1 < tokens.size()) ? tokens[i + 1] : "";
        cout << tokens[i] << " >> is a " << tokenType(tokens[i], next) << endl;
    }
}
