#include <vector>
#include <string>
#include <random>
#include <ctime>

int main()
{
    const std::size_t nLockedSlots = 50 ;
	std::vector<std::string> lockedSlots(nLockedSlots);

	const std::size_t nSudoku = 10 ;
	// initialise with all " "
	std::vector< std::vector<std::string> > sudoku( nSudoku, { nSudoku, " " } ) ;

    std::mt19937 rng( std::time(nullptr) ) ;
    std::uniform_int_distribution<int> distrib( 1, 4 ) ;
	const int randGame = distrib(rng);

	if (randGame == 1)
	{
        sudoku =
        {
            //      1    2    3    4    5   6   7   8   9
            { " ", " ", " ", " ", " ", " "," "," "," "," "},//IGNORE ROW
            { " ", "4", "5", "8", "6", " "," ","2","3","1"},//1
            { " ", "3", " ", " ", " ", " ","2","7"," "," "},//2
            { " ", " ", "7", "2", "5", "1"," "," "," "," "},//3
            { " ", " ", "6", "7", " ", "8"," ","3"," "," "},//4
            { " ", " ", " ", "4", " ", "9"," ","5"," "," "},//5
            { " ", " ", " ", "9", " ", "5"," ","6","8"," "},//6
            { " ", " ", " ", " ", " ", "2","8","9","6"," "},//7
            { " ", " ", " ", "5", "9", " "," "," "," ","3"},//8
            { " ", "9", "4", "6", " ", " ","5","1","2","8"}// 9
        };
	}
}
