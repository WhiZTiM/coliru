#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

void usun_znak( vector < string > * slowa, string filtr )
{
    vector < string >::iterator iter = slowa->begin();
    vector < string >::iterator iter_koniec = slowa->end();
    if( !filtr.size() )
         filtr.insert( 0, "\".,:;!?0123456789)(\\/" );
   
    while( iter != iter_koniec ) {
        string::size_type poz = 0;
        while(( poz =( * iter ).find_first_of( filtr, poz ) ) != string::npos )
            ( * iter ).erase( poz, 1 );
       
        iter++;
    }
}
int main()
{
    string tmp, plik, efilter;
    ifstream in( "plik.txt" );
    ofstream out( "word.txt" );
   
    vector < string > zn;
    set < string > call;
    set < string >::iterator it;
   
    while( in >> tmp )
    {
        zn.push_back( tmp );
        usun_znak( & zn, efilter );
        call.insert( zn.begin(), zn.end() );
    }
    for( it = call.begin(); it != call.end(); ++it ) {
       
        cout <<* it << endl;
        out <<* it << endl;
       
    }
    cin.get();
    return 0;
}