#include <bits/stdc++.h>
using namespace std;
int main(){
    ifstream file("test.txt");
    regex comment(R"((\/\/[^\n]*) | (\/\*[\s \S]*\*\/)");

    string code ((istream_iterator<char>(file)), istream_iterator<char> ());

    auto begin = sregex_iterator(code.begin(), code.end(), comment);
    
    auto end = sregex_iterator();

    if(begin ==  end){
        cout<< "comment not detected" <<endl;
    }
    else{
        for( auto i = begin; i != end; ++i){
            cout<< i ->str() << endl;
        }
    }
}