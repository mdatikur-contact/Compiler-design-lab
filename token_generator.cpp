#include<iostream>
#include<regex>
#include<string>
#include<fstream>
#include<sstream>
#include<unordered_set>
using namespace std;

unordered_set<string>keywords={
 "int", "float", "double", "char", "void", "if", "else", "while", "for",
    "return", "break", "continue", "switch", "case", "default", "struct",
    "class", "public", "private", "protected", "namespace", "template", "try", "catch"
};

string tokentype(const string& token)
{
    if(keywords.find(token)!=keywords.end())
    {
        return "keywords";
    }

    regex identifier("^[a-zA-Z_][0-9a-zA-Z_]*$");
    if(regex_match(token,identifier))
    {
        return "identifier";
    }

    regex number("^[+-]?([0-9]*[.])?[0-9]+$");
    if(regex_match(token,number))
    {
        return "number";
    }

    regex string_("^\".*\"$");
    if(regex_match(token,string_))
    {
        return "string";
    }

    regex char_("^'.'$");
    if(regex_match(token,char_))
    {
        return "char";
    }

    regex operatorRegex("^[\\+\\-\\*/%=<>!&|^~]+$");
    if (regex_match(token, operatorRegex)) {
        return "operator";
    }

    return "delimeter";
}
int main()
{
    remove("done.txt");
    string file_name;
    cout<<"Enter the file name:";
    cin>>file_name;
    fstream file(file_name);
    ofstream new_file("done.txt");

    if(!file.is_open())
    {
        cout<< "Error occur while opening the file.";
        return 1;
    }

    string code,line;
    while(getline(file,line))
    {
        code=code+line+"\n";
    }

    regex tokenRegex(R"(\s*([a-zA-Z_][0-9a-zA-Z_]*|[0-9]+(?:\.[0-9]+)?|\"[^\"]*\"|'.'|\S)\s*)");
    smatch matches;

    string::const_iterator start(code.cbegin());
    while(regex_search(start,code.cend(),matches,tokenRegex))
    {
        string token=matches[1].str();

        if(token.empty()||token==" "||token=="\n"||token=="\t")
        {
            start=matches.suffix().first;
            continue;
        }

        string token_type=tokentype(token);
        new_file<<token<< " - "<< token_type<<endl;
        start=matches.suffix().first;
    }

    cout<<"Process is done.";

    file.close();
    new_file.close();




}
