#include <iostream>

class field
{
private:
    char PlayField[5][5];

public:
    char o = 'o';
    field()
    {
        char PlayField[5][5] = { { o, o, o, o, o }, { o, o, o, o, o }, { o, o, o, o, o }, { o, o, o, o, o }, { o, o, o, o, o } };
    }


    void setTile(int x_val, int y_val)
    {
        PlayField[x_val][y_val] = 'x';
    }
    char getTile(int x_val, int y_val)
    {
        return PlayField[x_val][y_val]; 
    }



    /*field::~field();*/
};

int main()
{
    char x;

    field FourWins;
    //FourWins.setTile(3, 2);
    x = FourWins.getTile(3, 2);
    std::cout <<  x << std::endl;

    return 0;
}