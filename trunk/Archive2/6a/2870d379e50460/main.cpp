#include <string>
#include <iostream>
#include <vector>

using namespace std;

void prnt(string str)
{
    cout << str << endl;
}

void check(int val)
{
    if(val == 0)
        cout << "equal" << endl;
    else if(val < 0)
        cout << "lesser" << endl;
    else
        cout << "greater" << endl;
}

struct Client
{
    string id;
};

struct Node
{
    Node() : client(nullptr) {}
    Client* client;
};

int main()
{
    string s1 = "4xILASs5dmhcexwgWLIf6MJiKuA";
    string s2 = "4XILASs5dmhcexwgWLIf6MJiKuA";
    
    Node node;
    if(!node.client) cout << "client pointer not initialized" << endl;
    node.client = new Client;
    if(node.client) cout << "client pointer initialized" << endl;
    node.client->id = s1;
    check(node.client->id.compare(s1));
    check(node.client->id.compare(s2));
}
