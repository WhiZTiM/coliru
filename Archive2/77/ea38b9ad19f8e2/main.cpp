#include <iostream>
#include <sstream>
#include <unordered_set>
#include <string>

// assumes that a word is any sequence of non-white-space characters
// return unordered_set of the unique words read from the input stream
std::unordered_set<std::string> words_read_from( std::istream& stm )
{
    std::unordered_set<std::string> words ;
    std::string str ;
    while( stm >> str ) words.insert(str) ;
    return words ;
}

// assumes that a word is any sequence of non-white-space characters
// return unordered_set of unique words in phrase
std::unordered_set<std::string> split_into_words( const std::string& phrase )
{
    std::istringstream stm(phrase) ; // create an input string stream to read from
    return words_read_from(stm) ;
}

// return true if 'phrase' contains any of the words in the set 'words'
// note: case-sensitive
bool contains_word_in( const std::string& phrase, const std::unordered_set<std::string>& words )
{
    for( const std::string& str : split_into_words(phrase) ) // for each unique word in 'phrase'
    {
        if( words.find(str) != words.end() ) // if it is present in the unordered_set 'words'
            return true ;
    }
    return false ;
}

int main()
{
    std::istringstream txt1( "Dad has apples\n"
                             "Mom has pears\n"
                             "Grandma has grapes\n"
                             "Grandpa has nectarines\n"
                             "I have oranges\n" ) ;

    std::istringstream txt2( "oranges\n"
                             "apples\n"
                             "pears\n" ) ;

    // step 1: get the set of all words in txt2
    const auto words_in_txt2 = words_read_from(txt2) ;

    // step 2: for each line in txt1
    std::string line ;
    while( std::getline( txt1, line ) )
    {
        // step 2a. check if the line contains any word in the set of words in txt2
        if( contains_word_in( line, words_in_txt2) ) // if it does
            std::cout << line << '\n' ; // print the line
    }
}
