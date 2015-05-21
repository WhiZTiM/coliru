#include <iostream>
#include <cmath>
#include <string>
#include <cctype>
#include <sstream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;

template <typename T>
class BSTNodeT
{
    public:
    BSTNodeT()
    {
        left_ = NULL;
        right_ = NULL;
        contents_ = T();
        count_ = 0;
    }

    BSTNodeT( T contents )
    {
        left_ = NULL;
        right_ = NULL;
        contents_ = contents;
        count_ = 0;
    }

    ~BSTNodeT()
    {
        left_ = NULL;
        right_ = NULL;
    }

    void SetContents( T contents )
    {
        contents_ = contents;
    }

    void SetLeft( BSTNodeT<T>* node )
    {
        left_ = node;
    }

    void SetRight( BSTNodeT<T>* node )
    {
        right_ = node;
    }

    void IncrementCount()
    {
        count_++;
    }

    void DecrementCount()
    {
        count_--;
    }

    T GetContents() const
    {
        return contents_;
    }

    T& GetContents()
    {
        return contents_;
    }

    BSTNodeT<T>* GetLeft() const
    {
        return left_;
    }

    BSTNodeT<T>*& GetLeft()
    {
        return left_;
    }

    BSTNodeT<T>* GetRight() const
    {
        return right_;
    }

    BSTNodeT<T>*& GetRight()
    {
        return right_;
    }

    int GetCount()
    {
        return count_;
    }
    // private:
    T contents_;
    BSTNodeT<T>* left_;
    BSTNodeT<T>* right_;
    int count_;
};


template <typename T>
class BSTreeT
{
    public:
    BSTreeT()
    {
        root_ = NULL;
        size_ = 0;
    }

    ~BSTreeT()
    {
        Clear();
    }

    int GetSize() const
    {
        return size_;
    }

    void Clear()
    {
        Clear( root_ );
        size_ = 0;
    }

    int Insert( T i )
    {
        return Insert( i, root_ );
    }

    bool Exists( T i )
    {
        return Exists( i, root_ );
    }

    int Remove( T i )
    {
        return Remove( i, root_ );
    }

    BSTNodeT<T>* Get( T i )
    {
        return Get( i, root_ );
    }

    std::string ToStringForwards() const
    {
        return ToStringForwards( root_ );
    }

    std::string ToStringBackwards() const
    {
        return ToStringBackwards( root_ );
    }

    //private:
    BSTNodeT<T>* root_;
    int size_;

    void Clear( BSTNodeT<T>*& node )
    {
        BSTNodeT<T>* left;
        BSTNodeT<T>* right;
        if( node != NULL )
        {
            left = node->GetLeft();
            right = node->GetRight();
            Clear( left );
            Clear( right );
            // //delete node;
            node = NULL;
        }
    }

    int Insert( T i, BSTNodeT<T>*& node )
    {
        int count = 0;
        if( node == NULL )
        {
            node = new BSTNodeT<T>( i );
            size_++;
            count++;
        }
        else if( node->GetContents() > i )
        {
            root_ = node;
            return Insert( i, node->GetLeft() );
        }
        else if( node->GetContents() < i )
        {
            root_ = node;
            return Insert( i, node->GetRight() );
        }
        else
        {
            node->IncrementCount();
            count++;
            return Insert( i, node );
        }
        return count;
    }

    bool Exists( T i, BSTNodeT<T>* node )
    {
        if( node != NULL )
        {
            Exists( i, node->GetLeft() );
            if( node->GetContents() == i )
            {
                return true;
            }
            Exists( i, node->GetRight() );
        }
        return false;
    }

    int Remove( T i, BSTNodeT<T>* node )
    {
        T min;
        if( node != NULL )
        {
            if( node->GetContents() == i )
            {
                if( ( node->GetLeft() == NULL ) && node->GetRight() == NULL )
                {
                    if( i == 1 )
                    {
                        ////delete node;
                        node = NULL;
                        size_--;
                        return 0;
                    }
                    else
                    {
                        node->DecrementCount();
                        return node->GetContents();
                    }
                }
                else if( ( node->GetLeft() != NULL ) && ( node->GetRight() ) == NULL )
                {
                    if( i == 1 )
                    {
                        ////delete node;
                        node = NULL;
                        size_--;
                        return 0;
                    }
                    else
                    {
                        node->DecrementCount();
                        return node->GetContents();
                    }
                }
                else if( ( node->GetLeft() == NULL ) && ( node->GetRight() ) != NULL )
                {
                    if( i == 1 )
                    {
                        //delete node;
                        node = NULL;
                        size_--;
                        return 0;
                    }
                    else
                    {
                        node->DecrementCount();
                        return node->GetContents();
                    }
                }
                else
                {
                    if( i == 1 )
                    {
                        //delete node;
                        node = NULL;
                        size_--;
                        return 0;
                    }
                    else
                    {
                        node->DecrementCount();
                        return node->GetContents();
                    }
                }
            }
            else if( node->GetContents() > i )
            {
                return Remove( i, node->GetLeft() );
            }
            else if( node->GetContents() < i )
            {
                return Remove( i, node->GetRight() );
            }
        }
        return -1;
    }

    BSTNodeT<T>* Get( T i, BSTNodeT<T>* node )
    {
        if( node != NULL )
        {
            Get( i, node->GetLeft() );
            if( node->GetContents() == i )
            {
                return node;
            }
            Get( i, node->GetRight() );
        }
        return NULL;
    }

    string ToStringForwards( BSTNodeT<T>* node ) const
    {
        string str;
        if( node != NULL )
        {
            std::ostringstream ss;

            //////////////////////////////////////////////////////
            string left_str = ToStringForwards( node->GetLeft() );
            if( !left_str.empty() ) ss << left_str << ", " ;
            //////////////////////////////////////////////////////

            ss << node->GetContents() ;
            
            BSTNodeT<T>* end = GetEnd( node );
            if( node != end )
            {
                ss << ", ";
            }
            
            ss << ToStringForwards( node->GetRight() );
            str = ss.str();
        }
        return str;
    }

    string ToStringBackwards( BSTNodeT<T>* node ) const
    {
        if( node != NULL )
        {
            std::ostringstream ss;
            ss << ToStringBackwards( node->GetRight() );
            ss << node->GetContents();
            if( ( node->GetLeft() != NULL ) || ( node->GetRight() != NULL ) )
            {
                ss << ", ";
            }
            ss << ToStringBackwards( node->GetLeft() );
            return ss.str();
        }
        return "";
    }

    T FindMin( BSTNodeT<T>* node ) const
    {
        if( node != NULL )
        {
            if( node->GetLeft() == NULL )
            {
                return node->GetContents();
            }
            else
            {
                return FindMin( node->GetLeft() );
            }
        }
        return T();
    }

    BSTNodeT<T>* GetEnd( BSTNodeT<T>* node ) const
    {
        if( node != NULL )
        {
            if( node->GetRight() != NULL )
            {
                return GetEnd( node->GetRight() );
            }
            else if( node->GetLeft() != NULL )
            {
                return GetEnd( node->GetLeft() );
            }
        }
        return node;
    }
};

int main()
{
    BSTreeT<int> tree ;
    BSTNodeT<int> node[] = { 32, 21, 78, 12, 25, 92 } ;
    node[0].left_ = node + 1 ;
    node[0].right_ = node + 2 ;
    node[1].left_ = node + 3 ;
    node[1].right_ = node + 4 ;
    node[2].right_ = node + 5 ;
    tree.root_ = node ;


    std::cout << tree.ToStringForwards() << '\n' ;
}
