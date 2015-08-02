#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct student
{
    std::string name;
    int roll;
    double average;
    double grade;
    std::vector<double> scores;
    std::vector<std::string> assignments;
};

// write student object into a stream
std::ostream& operator<< ( std::ostream& stm, const student& stu )
{
    stm << stu.name << '\n' // name on line 1
        << stu.roll << ' ' << stu.average << ' ' << stu.grade << '\n' ; // line 2

    stm << stu.scores.size() << '\n' ; // #scores on line 3
    for( double s : stu.scores ) stm << s << ' ' ; // scores on line 4
    stm << '\n' ;

    stm << stu.assignments.size() << '\n' ; // #assignments on the next lime
    for( const std::string& s : stu.assignments ) stm << s << '\n' ; // one assignment per line

    return stm ;
}

// read student object from a stream
std::istream& operator>> ( std::istream& stm, student& stu )
{
    // skip leading empty lines, read name from non-empty line 1
    while( std::getline( stm, stu.name ) && stu.name.empty() ) ;
    stm >> stu.roll >> stu.average >> stu.grade ; // line 2

    std::size_t score_sz ;
    if( stm >> score_sz ) // #scores from line 3
    {
        stu.scores.resize(score_sz) ;
        for( double& s : stu.scores ) stm >> s ; // read score_sz scores

        std::size_t assignment_sz ;
        if( stm >> assignment_sz >> std::ws ) // read #grades, throw away the new line
        {
            stu.assignments.resize(assignment_sz) ;
            for( std::string& s : stu.assignments ) std::getline( stm, s ) ; // assignment_sz assignments
        }
    }

    if( !stm ) stu = {} ; // input failed; clear everything

    return stm ;
}

int main()
{
    student s { "psychameron ", 1234, 72.34, 81.43, { 1.2, 3.4, 5.6 }, { "ab", "cd ef", "ghijk" } } ;
    std::cout << s << '\n' ;

    std::istringstream stm( "some name\n"
                            "555 48.64 93.45 \n"
                            " 5 \n"
                            "1.0  2.3 4.5 6.7 8.9\n"
                            "3 \n"
                            "hello there\n"
                            "hello again\n"
                            "bye\n" ) ;
    student s2 ;
    if( stm >> s2 ) std::cout << "--------\n" << s2 << '\n' ;

    std::stringstream test_stm ;

    // write vector of students to a stream
    std::vector<student> seq { s, s2 } ;
    for( const student& s : seq ) test_stm << s << '\n' ;

    // read them back
    seq.clear() ;
    student temp ;
    while( test_stm >> temp ) seq.push_back(temp) ;

    // veryfy that they have been read back
    std::cout << "\n----------------------\n" ;
    for( const student& s : seq ) std::cout << s << "\n-----------\n" ;
}
