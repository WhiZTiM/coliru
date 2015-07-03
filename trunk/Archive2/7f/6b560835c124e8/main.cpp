#include <iostream>

class BTree{

    private:

        struct Node{

            Node* left = nullptr ;
            Node* right = nullptr ;
            int data ;
            explicit Node( int v ) : data(v) {}
        };

        Node* root = nullptr ;

        void insert( Node*& t, int x )
        {
            Node* n = new Node(x);
            if( t == nullptr ) t = n ;
            else if( x > t->data ) insert( t->right, x ) ;
            else insert( t->left, x ) ;
        }

        void do_print( const Node* n ) const // in order
        {
            if( n != nullptr )
            {
                do_print( n->left ) ;
                std::cout << n->data << ' ' ;
                do_print( n->right ) ;
            }
        }

    public:
        void insert( int x ) { insert( root, x ) ; } // *** pass by value
        void print_in_order() const { do_print(root) ; std::cout << '\n' ; } // *** const
};

int main()
{
    BTree a ;
    for( int v : { 5, 6, 4, 1, 8, 7, 3, 9, 2 } ) a.insert(v) ;
    a.print_in_order() ;
}
