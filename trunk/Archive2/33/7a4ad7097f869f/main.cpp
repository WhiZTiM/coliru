includes and stuff
...
...

static SystemObject game;

...
BaseCharacter player(game, "Player1", 1, 100, 100, s);

int main() {
    system("mode 100, 35");
    game.setBuffer(mainBuffer);
    ...
    ...


--------------------------------------------------------------------------------------------------------------


class BaseCharacter {
public:
    BaseCharacter(SystemObject& g, string n, int l, int hp, int mp, int initStats[]) { initialize(n, l, hp, mp, initStats); GAME_CONTROLLER = g; }
    ~BaseCharacter() { }

    ...
    ...
    ...

protected:
    ...
    ...
    const SystemObject GAME_CONTROLLER;
};


--------------------------------------------------------------------------------------------------------------


int BaseCharacter::heal(int amt)
{
    if ( (health + amt) > maxHealth ) {
        amt = maxHealth - health;
        health = maxHealth;
    }
    else
        health += amt;

    GAME_CONTROLLER.printToBuffer(name + " has recovered " + to_string(amt) + " health!");    <--- Desired usage
    return amt;
}




~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
This is the error I am getting.

error: use of deleted function 'SystemObject& SystemObject::operator=(const SystemObject&)'|