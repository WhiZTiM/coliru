#include <iostream>

int main() {

    int outer = 5;

    int loop_cnt = 0 ;
    while( outer >= 1 && std::cout << "\n\n" << ++loop_cnt << ". while( outer >= 1 ): outer == " << outer << '\n' )
    {
        int inner = outer ;
        std::cout << "    after int inner = outer ; inner == " << inner << '\n' ;

        int inner_lc = 0 ;
        while( inner >=1 && std::cout << "\n    " << ++inner_lc << "> while( inner >= 1 ): inner == " << inner << '\n' ){
            std::cout << "        inner-- == " << inner-- << '\n' ;
            std::cout << "        after inner-- inner == " << inner << '\n' ;
        }
        --outer;
    }
}
