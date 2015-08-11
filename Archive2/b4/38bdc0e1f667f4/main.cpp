#include <iostream>
#include <string>
#include <vector>
#include <iterator>

struct player
{
    std::string name ;
    bool alive = true ; // set to false to kill the player

    void kill() { alive = false ; std::cout << "player '" << name << "' killed\n" ; }
};

int main()
{
    std::vector<player> players { { "Gideon" }, { "Zacchaeus" }, { "Aaliyah" }, { "Micah" } };
    std::cout << "players: " ;
    for( player p : players ) if( p.alive ) std::cout << p.name << ' ' ;
    std::cout << '\n' ;

    // find player "Zacchaeus"
    auto iter_zach = std::begin(players) ;
    for( ; iter_zach != std::end(players) ; ++iter_zach ) if( iter_zach->name == "Zacchaeus" ) break ;

    // if found, kill "Zacchaeus"
    if( iter_zach != std::end(players) ) iter_zach->kill() ; // mark the player as not alive

    std::cout << "players still in the game: " ;
    for( player p : players ) if( p.alive ) std::cout << p.name << ' ' ;
    std::cout << '\n' ;

    // remove the dead player "Zacchaeus" (invoke destructor)
    if( iter_zach != std::end(players) ) players.erase(iter_zach) ;
}
