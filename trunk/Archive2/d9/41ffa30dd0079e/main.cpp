#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Piece
{
    private:
		int x; //coordinate locations
		int y;
		char name;

	public:
		Piece(char, int, int);
	
};

Piece :: Piece(char name_, int x_, int y_)
{
    x = x_;
	y = y_;
	name = name_;	

}


class Game
{
    private:
		std::vector< std::vector<Piece> > board;
	public:
		void setup();
		void movePiece(int, int, int, int);

		
};


void Game :: setup()
{
    char names[] = "RPNPBPQPKPBPNPRP";

	//create chess board	
	for (int j = 0; j < 8; j++){
		std::vector<Piece> col;
		for (int i = 0; i < 2; i++){//pieces at rows 1 and 2
			col.push_back(Piece(i, j, names[i]));
		}
		board.push_back(col);
		for (int i = 6; i < 8; i++){
			col.push_back(Piece(i, j, names[i-6]));
		}
		board.push_back(col);
	}
	
}

void Game :: movePiece(int xi, int yi, int xf, int yf)
{
	xi -= 97;
	xf -= 97;
	board[xf].erase(board.begin()+yf -1);//erase the element at xf, yf
	swap(board[xi][yi], board [xf][yf]);//move piece at xi, yi to xf, yf
}


}


