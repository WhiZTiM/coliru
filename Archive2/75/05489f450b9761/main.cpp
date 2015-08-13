#include <iostream>
#include <string>

struct player
{
    enum player_type { MAGE, NOT_MAGE };

    player_type type ;
    std::string name;

    player( player_type type, std::string name ) : type(type), name(name) {}

    void transform( player_type new_type ) { type = new_type ; }

    void cast_spell() const
    {
        if( type == MAGE ) std::cout << name << " could cast a spell\n" ;
        // else do nothing (or perhaps throw something)
    }
};

int main()
{
    player billie( player::MAGE, "Lady Day" ) ;
    billie.cast_spell() ; // Lady Day could cast a spell

    player other( player::NOT_MAGE, "xxx" ) ;
    other.cast_spell() ; // do nothing

    other.transform( player::MAGE ) ;
    other.cast_spell() ; // xxx could cast a spell
}
