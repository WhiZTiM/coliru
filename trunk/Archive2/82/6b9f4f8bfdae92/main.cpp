#include <iostream>

void showMoves(int Disk, char from, char to) {
    char third = 'A' + 'B' + 'C' - from - to;
    if (Disk != 1) showMoves(Disk-1, from, third);
    std::cout << "move disk " << Disk << " from peg " << from << " to peg " << to << '\n';
    if (Disk != 1) showMoves(Disk-1, third, to);
}

int main()
{
    int numberOfDisks;
    std::cin >> numberOfDisks;
    showMoves(numberOfDisks,'A','C');
}