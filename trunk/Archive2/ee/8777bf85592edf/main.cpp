#include <iostream>

template <class type>
class avlTree
{
public:
    avlTree() {}      //default constructor
    ~avlTree() {}    //destructor
    const type & findMin() const;
    const type & findMax() const;
    bool isEmpty() const;
    void printTree() const;
    void makeEmpty();
    void insert(const type & newData);
    void remove(const type & deleteItem);
 
private:
    // template<class typeB>
    struct avlNode
    {
        type info;
        avlNode *left;
        avlNode *right;
        int height;
 
        avlNode(const type & data, avlNode *ll, avlNode *rl, int h = 0)
            : info{ data }, left{ ll }, right{ rl }, height{ h } {}
    };
 
    avlNode* root;
 
    void insert(const type & newData, avlNode* & p);
    void remove(const type & deleteItem, avlNode* & p);
    avlNode* findMin(avlNode* p);  //these two methods are where I'm having problems.
    avlNode* findMax(avlNode* p);
 
 friend void f();
};
 
template <typename type>
avlTree<type>::avlNode* 
    avlTree<type>::findMin(avlNode* p) {
        std::cout << "boo\n";
  return p;
}

void f() {
    avlTree<int> t;
	t.findMin(nullptr);
}

int main()
{
	f();
}