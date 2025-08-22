#include<iostream>
#include<string>
#include<fstream>
#include<regex>
using namespace std;
int main()
{
    int remove_file=remove("output_code.txt");

    fstream file("source_code.txt");
    ofstream output_file("output_code.txt");

    if(!file.is_open())
    {
        cout<< "Occur error while opening the file.";
        return 0;
    }

    regex comment(R"((\/\/[^\n]*)|(\/\*[\s\S]*?\*\/))");
    regex space(R"([ ]{2,})");
    regex newline(R"(\n{2,})");

    char ch;
    string code,line;

    while(getline(file,line))
    {
        code=code+line+"\n";

    }

    string output_code=regex_replace(code,comment,"");

    output_code=regex_replace(output_code,space,"");
    output_code=regex_replace(output_code,newline,"\n");
    output_file<<output_code;

    cout<< "Preprocessing is done.";

    file.close();
    output_file.close();
}
