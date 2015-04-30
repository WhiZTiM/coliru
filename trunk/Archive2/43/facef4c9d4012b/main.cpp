#include <iostream>
#include <string>
#include <map>
using namespace std;

struct Node {
    int x;    
};

typedef map<char, Node*> mapList;

void print(const map<char,Node*>& refers) {
    for (auto const &i : refers) {
        cout << i.second->x << '\n';
    }
}

void print(const map<string, mapList>& h) {
    for (auto const& i : h) {
        cout << "Etiqueta " << i.first << ":\t";
        for (auto const& j : i.second) {
                cout << j.second->x << ' ';
        }    
        cout << '\n';
    }
}

int main() {
    map<char, Node> mapa;
    for (char c = 'a'; c <= 'z'; ++c) {
        mapa.insert({c,{int(c)}});
    }
    
    map<string, mapList> hashtags;
    
    for (auto &i : mapa) {
        string etiq = "etiq";
        etiq += '0' + i.second.x%3 ;
        hashtags[etiq].insert({i.first, &(i.second)});
    }
    print(hashtags);
}
