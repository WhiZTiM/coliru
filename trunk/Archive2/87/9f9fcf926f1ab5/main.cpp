#include <iostream>
#include <vector>
#include <queue>

struct symbol {
    explicit symbol(char av = 0, int ac = 0) : value(av), count(ac) { }
    char value; // actual symbol, by default 0 (empty)
    int count;  // count of the symbol, by default 0
}; // symbol

// compare two symbols
// symbol with a lower count is "less than" symbol with a higher count
inline bool operator<(const symbol& lhs, const symbol& rhs) {
    return ((lhs.count < rhs.count) || (!(rhs.count < lhs.count) && (lhs.value < rhs.value)));
} // operator<

template <typename T> struct bnode {
    explicit bnode(const T& t = T(), bnode* l = 0, bnode* r = 0)
        : value(t), left(l), right(r) { }

    T value;      // payload

    bnode* left;  // left child
    bnode* right; // right child
}; // struct bnode

template <typename T>
bool operator<(bnode<T> const& l, bnode<T> const& r)
{
    return false;
}

//and here is me trying to make a priority queue:

std::priority_queue<bnode<symbol> > queue;

int main()
{}
