#include <iostream>
#include <string>

using namespace std;

void room(string enemy, string treasure, string description);

int main()
{
    room("Ork", "Blunt Sword", "You have entered the mouth of the cave");
    room("Engraged Ork", "", "You venture deeper");
	return 0;
}

void room(string enemy, string treasure, string description){
    bool
        // the empty member function tells you whether a string is blank, or contains no characters.
        // the ! before it is another boolean operator, but this one takes just one argument.
        // Just like != instead of == means not equal instead of not, this reverses the boolean value
        // given by the function. Think of it as saying "If the string storing the enemy value isn't empty"
        enemyPresent = !enemy.empty(); 
        
    bool
        // again, it's saying the same thing: there's treasure present in this room, if the
        // string passed in isn't blank. Do note: typically, you don't want to store
        // information in a way that depends on special values, because you might want to use
        // those special values later. Packaging this information together requires classes,
        // which you haven't covered yet, so we're going to use the special value method of 
        // telling whether or not either one of these is present.
        treasurePresent = !treasure.empty();
        
    std::cout << description << "\n";
    if(enemyPresent){
        std::cout << "An " << enemy << " stands menacing before you! You're victorious in the fight though.\n";
        if(treasurePresent){
            std::cout << "In the aftermath of the battle, you notice treasure nearby! You pick up " << treasure << ".\n";
        }
        else{
            std::cout << "There is nothing in the remnants of your battle worth picking up. You should continue on.\n";
        }
    }
    else{
        std::cout << "There is no one here but you.\n";
        if(treasurePresent){
            std::cout << "As you make to leave, you notice something: a " << treasure << "! How fortuitous.\n";
        }
    }
    
}