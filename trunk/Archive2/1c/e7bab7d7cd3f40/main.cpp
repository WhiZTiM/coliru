#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Player{
    int score;
    void autoID(){}
};

istream& operator>>(istream &is, Player &player){
    int score;

    is >> score;

    player.score = score;
    player.autoID();

    return is;
}


istream& operator>>(istream &is, vector <Player> &players){
    string foo;
    is >> foo;  // garbage

    while(!is.eof()){
        Player player;
        is >> player;
        players.push_back(player);
    }

    return is;
}

int main() {
    ifstream input_file;

    if(input_file.is_open()){
        vector <Player> players;
        input_file >> players;  // *BOOM*
    }
}