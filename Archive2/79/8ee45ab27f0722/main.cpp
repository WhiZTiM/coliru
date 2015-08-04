#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

inline void keep_window_open() { char ch; std::cin >> ch; }

int main() {

    // http://www.stroustrup.com/C++11FAQ.html#init-list
    const std::vector<std::string> bleep { "bitch", "fuck", "shit", "damn", "hell" };

	std::string word ;
	while( std::cin >> word ) {

        bool bleepable = false ; // start with the premise that the word is not bleepable
        
		for( std::size_t i = 0; i < bleep.size() ; ++i ) { // for each position in the vector
        
			if( bleep[i] == word ) bleepable = true ; // if this word is the same as the one in the vector, it is bleepable
        }
        
        // or using an idiomatic range-based loop
        // http://www.stroustrup.com/C++11FAQ.html#for
        bleepable = false ;
        for( std::string bleep_this : bleep ) if( word == bleep_this ) bleepable = true ;

        if(bleepable) std::cout << "bleep " ;
        else std::cout << word << ' ' ;
    }
    
    std::cout << '\n' ;
}
