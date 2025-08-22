#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int find_element(char arr[],int size_of_array, char element)
{
    bool is_found = false;
    for(int i=0; i<size_of_array; i++)
    {
        if(element == arr[i])
            return i;
    }
    if(!is_found)
        return -1;
}

int main()
{
    // Variable declaration part
    char start_node, end_node, current_node;
    int no_of_nodes, no_of_inputs;
    cout<<"Enter the total no of nodes: ";
    cin>>no_of_nodes;
    char nodes[no_of_nodes];
    cout<<"Enter the total no of inputs: ";
    cin>>no_of_inputs;
    char inputs[no_of_inputs];

    // Input the variables
    for(int i=0; i<no_of_nodes; i++)
    {
        cout<<"Enter the node no -"<<i+1<<": ";
        cin>>nodes[i];
    }
    for(int i=0; i<no_of_inputs; i++)
    {
        cout<<"Enter the input no -"<<i+1<<": ";
        cin>>inputs[i];
    }

    cout<<"Enter the name of initial node: ";
    cin>>start_node;

    cout<<"Enter the name of final node: ";
    cin>>end_node;


    // Create the transition table
    char transition_table [no_of_nodes][no_of_inputs];
    for(int i=0; i<no_of_nodes; i++)
    {
        for(int j=0; j<no_of_inputs; j++)
        {
            cout<<"Enter the node when "<<nodes[i]<<"-->"<<inputs[j]<<": ";
            cin>>transition_table[i][j];
        }
    }

    string check;
    cout<<"Enter the input stream to validate: ";
    cin>>check;

    // Main Logic
    current_node = start_node;
    for(int i=0; i<check.length(); i++)
    {   int x = find_element(nodes, no_of_nodes, current_node);
        int y = find_element(inputs, no_of_inputs, check[i]);
        current_node = transition_table[x][y];
        if (transition_table[x][y]=='@')
            cout << "Invalid Input Stream!"<<endl;
            break;

    }
    if(current_node == end_node)
        cout<<endl<<"Valid Input Stream."<<endl;
        else
            cout<<endl<<"Invalid Input Stream!"<<endl;




}

