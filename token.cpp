#include <bits/stdc++.h>
using namespace std;

// Correct spelling
unordered_set<string> keywords = {
    "int", "double", "float", "char", "void", "if", "else", "while", "for"};

// Function to classify each token
string tokenType(const string &token, const string &nextToken)
{
    if (regex_match(token, regex("^#.*$")))
        return "Preprocessor";
    if (regex_match(token, regex("^<.*>$")))
        return "Header File";
    if (keywords.count(token))
        return "Keyword";
    if (regex_match(token, regex("^[a-zA-Z_][a-zA-Z0-9_]*$")) && nextToken == "(")
        return "Function";
    if (regex_match(token, regex("^[a-zA-Z_][a-zA-Z0-9_]*$")))
        return "Identifier";
    if (regex_match(token, regex("^[0-9]+(\\.[0-9]+)?$")))
        return "Number";
    if (regex_match(token, regex(R"([+\*/%&|^~!=<>-]+)")))
        return "Operator";
    return "Delimiter";
}

int main()
{
    // Read entire file into string
    ifstream file("test.txt");
    if (!file)
    {
        cerr << "Cannot open file\n";
        return 1;
    }
    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // Token regex
    regex tokenRegex(R"((#\s*[a-zA-Z_][a-zA-Z0-9_]*)|(<[a-zA-Z0-9_./]+>)|([a-zA-Z_][a-zA-Z0-9_]*)|(\d+(\.\d+)?)|([+\*/%&|^~!=<>-]+)|([{}()\[\];,]))");

    // Tokenize
    smatch match;
    string::const_iterator start = code.cbegin();
    vector<string> tokens;

    while (regex_search(start, code.cend(), match, tokenRegex))
    {
        tokens.push_back(match.str());
        start = match.suffix().first;
    }

    // Print tokens with type
    for (size_t i = 0; i < tokens.size(); i++)
    {
        string next = (i + 1 < tokens.size()) ? tokens[i + 1] : "";
        cout << tokens[i] << " is a " << tokenType(tokens[i], next) << endl;
    }

    return 0;
}
