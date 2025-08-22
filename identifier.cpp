#include <bits/stdc++.h>
using namespace std;

bool isValidIdentifier(const string &token)
{
    regex identifierRegex("^[a-zA-Z_][a-zA-Z0-9_]*$");
    return regex_match(token, identifierRegex);
}

int main()
{
    string token;
    cout << "inter a tokern or type end to exit" << endl;
    while (true)
    {
        cin >> token;
        if (token == "end")
        {
            cout << "exiting program" << endl;
            break;
        }
        if (isValidIdentifier(token))
        {
            cout << token << " is a valid C++ identifier." << endl;
        }
        else
        {
            cout << token << " is NOT a valid C++ identifier." << endl;
        }
    }
}
