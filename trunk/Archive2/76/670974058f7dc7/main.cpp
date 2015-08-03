#include <vector>
 
struct Tile
{
    short a;
    short b;
    char b1;
    char b2;
    char b3;
    char b4;
};

void rle(char) {}

template <char Tile::*field, class Ite>
void compress(Ite begin, Ite end)
{
    for(; begin != end; ++begin) {
        rle((*begin).*field);
    }
}
 
int main()
{
    std::vector<Tile> tiles(128*128);
   
    compress<&Tile::b1>(begin(tiles), end(tiles));
   
    return 0;
}