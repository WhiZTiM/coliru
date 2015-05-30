#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node
{
    string name ;
    int    size ;
    
    node ( string name_ , int size_):name(name_) , size(size_)
    {}

    friend ostream& operator<<(ostream &os , const node & no ) ;
} ;

ostream &operator<< (ostream &os , const node & no )
{
    os<<"node name :"<<no.name<< endl ;
    os<<"node size :"<<no.size<< endl ;
    
    return os ;
}

typedef vector<node> nodeList ;

void print_node ( nodeList &n   )
{
   for ( vector<node>::iterator it = n.begin() ; it!= n.end() ; it++ )
     cout << *it << endl ;
}


int main ( void )
{
    nodeList list ;
    string name = "Aimer" ;
    
    for ( int i = 0 ; i < 10 ; i++ )
        list.push_back (node( name , i) ) ;
        
    
    print_node ( list ) ;
    
    return 0 ;
}

















