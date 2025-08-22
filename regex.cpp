#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main()
{
    string s="my name is tanjid, i can do lots of things";
    regex r("tan[a-zA-Z]+");
    cout<< regex_replace(s,r,"tamo");
}
