#include<iostream>
#include<string>
#include<fstream>
#include<regex>
using namespace std;

int main()
{
    fstream file("test.txt");


    regex comment(R"((\/\/[^\n]*)|(\/\*[\s\S]*?\*\/))");

    string code, line;
    while(getline(file,line))
    {
        code += line + "\n";
    }

    // Search for comments in the whole file
    auto begin = sregex_iterator(code.begin(), code.end(), comment);
    auto end = sregex_iterator();

    if(begin == end) {
        cout << "No comments found." << endl;
    } else {
        cout << "Comments detected:" << endl;
        for(auto i = begin; i != end; ++i)
        {
            smatch match = *i;
            cout << match.str() << endl;  
        }
    }

    file.close();
    return 0;
}
