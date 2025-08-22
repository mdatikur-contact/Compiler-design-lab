#include <iostream>
#include <fstream>
#include <regex>
#include <string>
using namespace std;

int main() {
    ifstream file("test.txt");

    regex comment(R"((\/\/[^\n]*)|(\/\*[\s\S]*?\*\/))");
    string code((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

    auto begin = sregex_iterator(code.begin(), code.end(), comment);
    auto end = sregex_iterator();

    if (begin == end) {
        cout << "No comments found." << endl;
    } else {
        cout << "Comments detected:" << endl;
        for (auto i = begin; i != end; ++i) {
            cout << i->str() << endl;
        }
    }

    return 0;
}
