#include<iostream>
#include<fstream>
using namespace std;
int main()
{
    fstream file("io.txt");
    if(!file.is_open())
    {
        ofstream file("io.txt");
        cout<<"file is created"<<endl;
    }
    cout<<file.tellg()<<endl;
    cout<<file.tellp()<<endl;
    string a;
    getline(cin,a);
    file<<a<<endl;
    file.seekg(3);
    cout<<file.tellg()<<endl;
    cout<<file.tellp()<<endl;
}
