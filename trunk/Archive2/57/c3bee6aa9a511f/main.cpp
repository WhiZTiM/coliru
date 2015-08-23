#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <memory>

enum RBColor { BLACK = 0, RED };
const int LEFT = 0;
const int RIGHT = 1;

// A red-black tree implementation. The `RBNode` objects are allocated and
// initialized by the user themselves and then inserted into the tree. The
// keys of each node must be unique (i.e operator=(k1, k2) returns false). The
// tree does not own the nodes and will not free them. So don't forget to walk
// the tree and free the nodes!

template <typename K, typename V> struct RBNode {
    // The part common in the nil node and normal nodes
    RBColor _color;
    RBNode<K, V> *_parent;
    RBNode<K, V> *_kids[2];
    
    K _key; // Key
    V _val; // Value

    RBNode(const K &key, const V &val) : _key(key), _val(val) {}

    RBNode(K &&key, V &&val) : _key(std::move(key)), _val(std::move(val)) {}

    RBNode(const RBNode<K, V> &other) = delete;
};

// The nil node shared by any and every `RBT<K, V>`
struct Nil{
    RBColor _color;
    Nil* _parent;
    Nil* _kids[2];
} g_nil_node = {BLACK, nullptr, {nullptr, nullptr}};

// Returns a pointer to the nil node cast to `RBNode<K, V>*`
template <typename K, typename V>
static inline RBNode<K, V>* NilNode() {
    return reinterpret_cast<RBNode<K, V>*>(&g_nil_node);
}

template <typename K, typename V> struct RBT {
    RBNode<K, V> *_root;    // The pointer to root
    size_t _nr_nodes;       // Number of nodes in the tree

    // Constructor
    RBT() : _root(NilNode<K, V>()), _nr_nodes(0) {}

    // On deletion, just set these to nullptr to catch any error
    ~RBT() {
        _root = nullptr;
    }

    // No copying please. That would require the tree to own the nodes - hence
    // have knowledge of how to allocate and deallocate nodes.
    RBT(const RBT<K, V> &other) = delete;

    // Move ctor is fine
    RBT(RBT<K, V> &&other) {
        if (this != &other) {
            _root = other._root;
            other._root = nullptr;
        }
    }

    // Insert the given node
    void insert(RBNode<K, V>* n);

    // Remove the node given
    RBNode<K, V>* remove(RBNode<K, V> *n);

    // Returns pointer to the node with the given key
    RBNode<K, V>* get_node(const K &key);

  private:
    // Transplants the given node `n2` to the given node `n1`'s position
    void _graft(RBNode<K, V> *n1, RBNode<K, V> *n2);

    // Rotations
    template <int left, int right>
    void _rotate(RBNode<K, V> *n);

    // Bottom-up fix for insertion and deletion
    template <int left, int right>
    inline RBNode<K, V> *_insert_fix(RBNode<K, V> *z);

    template <int left, int right>
    inline RBNode<K, V> *_remove_fix(RBNode<K, V> *x);
};

template <typename K, typename V>
static inline bool is_root(RBT<K, V> *t, RBNode<K, V> *n) {
    return n->_parent == NilNode<K, V>();
}

template <typename K, typename V>
RBNode<K, V>* RBT<K, V>::get_node(const K& key) {
    auto cur = _root;
    while (cur != NilNode<K, V>()) {
        if (cur->_key == key) {
            return cur;
        }
        if (key < cur->_key) {
            cur = cur->_kids[LEFT];
        } else {
            cur = cur->_kids[RIGHT];
        }
    }
    return nullptr;
}

template <typename K, typename V>
void RBT<K, V>::_graft(RBNode<K, V> *n1, RBNode<K, V> *n2) {
    // assert(n1 != (NilNode<K, V>()));
    // assert(n2 != (NilNode<K, V>()));
    if (is_root(this, n1)) {
        _root = n2;
    } else if (n1->_parent->_kids[0] == n1) {
        n1->_parent->_kids[0] = n2;
    } else {
        n1->_parent->_kids[1] = n2;
    }
    n2->_parent = n1->_parent;
}

template <typename K, typename V>
void RBT<K, V>::insert(RBNode<K, V> *n) {
    if (_root == NilNode<K, V>()) {
        _root = n;
        n->_color = BLACK;
        n->_parent = NilNode<K, V>();
        n->_kids[LEFT] = NilNode<K, V>();
        n->_kids[RIGHT] = NilNode<K, V>();
        return;
    }

    RBNode<K, V> *cur = _root;
    RBNode<K, V> *par = _root;
    int dir = LEFT;
    while (cur != NilNode<K, V>()) {
        assert(cur != nullptr);
        par = cur;
        assert(n->_key != cur->_key);
        if (n->_key < cur->_key) {
            cur = cur->_kids[LEFT];
            dir = LEFT;
        } else {
            cur = cur->_kids[RIGHT];
            dir = RIGHT;
        }
    }
    n->_color = RED;
    n->_parent = par;
    n->_kids[LEFT] = NilNode<K, V>();
    n->_kids[RIGHT] = NilNode<K, V>();
    par->_kids[dir] = n;
    ++_nr_nodes;

    // bottom-up fix
    while (n->_parent->_color == RED) {
        if (n->_parent == n->_parent->_parent->_kids[LEFT]) {
            n = _insert_fix<LEFT, RIGHT>(n);
        } else {
            n = _insert_fix<RIGHT, LEFT>(n);
        }
    }
    _root->_color = BLACK;
}

template <typename K, typename V>
template <int left, int right>
RBNode<K, V>* RBT<K, V>::_insert_fix(RBNode<K, V> *z) {
    auto y = z->_parent->_parent->_kids[right];
    if (y->_color == RED) {
        z->_parent->_color = BLACK;
        y->_color = BLACK;
        z->_parent->_parent->_color = RED;
        z = z->_parent->_parent;
    } else {
        if (z == z->_parent->_kids[right]) {
            z = z->_parent;
            _rotate<left, right>(z);
        }
        z->_parent->_color = BLACK;
        z->_parent->_parent->_color = RED;
        _rotate<right, left>(z->_parent->_parent);
    }
    return z;
}

template <typename K, typename V>
template <int left, int right>
void RBT<K, V>::_rotate(RBNode<K, V> *x) {
    auto y = x->_kids[right];
    x->_kids[right] = y->_kids[left];
    if (y->_kids[left] != NilNode<K, V>()) {
        y->_kids[left]->_parent = x;
    }
    y->_parent = x->_parent;
    if (x->_parent == NilNode<K, V>()) {
        _root = y;
    } else if (x == x->_parent->_kids[left]) {
        x->_parent->_kids[left] = y;
    } else {
        x->_parent->_kids[right] = y;
    }
    y->_kids[left] = x;
    x->_parent = y;
}

template <typename K, typename V>
RBNode<K, V>* RBT<K, V>::remove(RBNode<K, V> *n) {
    auto y = n;
    RBColor orig_color = n->_color;
    RBNode<K, V>* x;
    if (n->_kids[LEFT] == NilNode<K, V>()) {
        x = n->_kids[RIGHT];
        _graft(n, n->_kids[RIGHT]);
    } else if (n->_kids[RIGHT] == NilNode<K, V>()) {
        x = n->_kids[LEFT];
        _graft(n, n->_kids[RIGHT]);
    } else {
        // minimum of n->_kids[RIGHT]
        auto min = n->_kids[RIGHT];
        while (min->_kids[LEFT] != NilNode<K, V>()) {
            min = min->_kids[LEFT];
        }
        y = min;
        orig_color = y->_color;
        x = y->_kids[RIGHT];
        if (y->_parent == n) {
            x->_parent = y;
        } else {
            _graft(y, y->_kids[RIGHT]);
            y->_kids[RIGHT] = n->_kids[RIGHT];
            y->_kids[RIGHT]->_parent = y;
        }
        _graft(n, y);
        y->_kids[LEFT] = n->_kids[LEFT];
        y->_kids[LEFT]->_parent = y;
        y->_color = n->_color;
    }
    if (orig_color == RED) {
        return n;
    }
    // remove fix
    while (x != _root && x->_color == BLACK) {
        if (x == x->_parent->_kids[LEFT]) {
            x = _remove_fix<LEFT, RIGHT>(x);
        } else {
            x = _remove_fix<RIGHT, LEFT>(x);
        }
    }
    x->_color = BLACK;
    return n;
}

template <typename K, typename V>
template <int left, int right>
RBNode<K, V>* RBT<K, V>::_remove_fix(RBNode<K, V>* x) {
    auto w = x->_parent->_kids[right];
    if (w->_color == RED) {
        w->_color = BLACK;
        x->_parent->_color = RED;
        _rotate<left, right>(x->_parent);
        w = x->_parent->_kids[right];
    }
    if (w->_kids[left]->_color == BLACK && w->_kids[right]->_color == BLACK) {
        w->_color = RED;
        x = x->_parent;
    } else {
        if (w->_kids[right]->_color == BLACK) {
            w->_kids[left]->_color = BLACK;
            w->_color = RED;
            _rotate<right, left>(w);
            w = x->_parent->_kids[right];
        }
        w->_color = x->_parent->_color;
        x->_parent->_color = BLACK;
        w->_kids[right]->_color = BLACK;
        _rotate<left, right>(x->_parent);
        x = _root;
    }
    return x;
}

// Commence tests :)


#ifdef TEST
#include <vector>
#include <algorithm>
#include <iostream>

template <typename K, typename V>
void accumulate_black_heights(RBT<K, V> *t, RBNode<K, V> *cur_root,
                              int accum_height, std::vector<int> &heights) {
    if (cur_root->_color == BLACK) {
        accum_height = accum_height + 1;
    }
    if (cur_root->_kids[LEFT] == NilNode<K, V>() && cur_root->_kids[RIGHT] == NilNode<K, V>()) {
        printf("//Height at %d = %d\n", cur_root->_key, accum_height);
        heights.push_back(accum_height);
    }
    if (cur_root->_kids[LEFT] != NilNode<K, V>()) {
        accumulate_black_heights(t, cur_root->_kids[LEFT], accum_height,
                                 heights);
    }
    if (cur_root->_kids[RIGHT] != NilNode<K, V>()) {
        accumulate_black_heights(t, cur_root->_kids[RIGHT], accum_height,
                                 heights);
    }
}

template <typename K, typename V> void valid_black_height(RBT<K, V>* t) {
    std::vector<int> heights;
    accumulate_black_heights(t, t->_root, 0, heights);
    assert(std::all_of(heights.cbegin(), heights.cend(),
                       [&](const int h1) { return h1 == heights.front(); }));
}

template <typename K, typename V>
void valid_red_kids(RBT<K, V>* t) {
    std::vector<RBNode<K, V> *> nodes;
    nodes.push_back(t->_root);
    while (nodes.size() != 0) {
        auto n = nodes.back();
        nodes.pop_back();
        for (int i = LEFT; i <= RIGHT; ++i) {
            if (n->_kids[i] != NilNode<K, V>()) {
                assert(!(n->_color == RED && n->_kids[i]->_color == RED));
                nodes.push_back(n->_kids[i]);
            }
        }
    }
}

// Example deletion
template <typename K, typename V>
void delete_nodes(RBT<K, V>* t, RBNode<K, V> *cur) {
    if (cur->_kids[LEFT] != NilNode<K, V>()) {
        delete_nodes(t, cur->_kids[LEFT]);
    }
    if (cur->_kids[RIGHT] != NilNode<K, V>()) {
        delete_nodes(t, cur->_kids[RIGHT]);
    }
    delete cur;
}

using IntTree = RBT<int, int>;
using IntNode = RBNode<int, int>;



// Print in dot format
void inttree_print(IntTree *t);
void _inttree_print(IntTree *t, IntNode *cur);
// Print in-order (sorted)
void inttree_inorder(IntTree *t, IntNode *cur);

void inttree_inorder(IntTree *t, IntNode *cur) {
    if (cur->_kids[LEFT] != NilNode<int, int>()) {
        inttree_inorder(t, cur->_kids[LEFT]);
    }
    printf("%d, ", cur->_key);
    if (cur->_kids[RIGHT] != NilNode<int, int>()) {
        inttree_inorder(t, cur->_kids[RIGHT]);
    }
}

void inttree_print(IntTree *t) {
    printf("digraph RBT {\n");
    _inttree_print(t, t->_root);
    printf("}\n");
}

void _inttree_print(IntTree *t, IntNode *cur) {
    if (cur == NilNode<int, int>()) {
        return;
    }
    if (cur->_kids[LEFT] != NilNode<int, int>()) {
        printf("%d -> %d [label = %s];\n", cur->_key, cur->_kids[LEFT]->_key,
               "LEFT");
        _inttree_print(t, cur->_kids[LEFT]);
    }
    if (cur->_kids[RIGHT] != NilNode<int, int>()) {
        printf("%d -> %d [label = %s];\n", cur->_key, cur->_kids[RIGHT]->_key,
               "RIGHT");
        _inttree_print(t, cur->_kids[RIGHT]);
    }
    printf("%d [style=filled, shape=circle, fillcolor=%s];\n", cur->_key,
           cur->_color == RED ? "RED" : "GRAY");
}

int main() {
    IntTree t;
    //int n;
    //while (fscanf(stdin, "%d", &n) != EOF) {
    //    t.insert(new IntNode(n, n));
    //}
    for (int i = 1; i < 100; ++i) {
        t.insert(new IntNode(i, i));
    }

    for (int i = 1; i < 100; ++i) {
        auto n = t.get_node(i);
        printf("// key = %d, val = %d\n", n->_key, n->_val);
        fflush(stdout);
        assert (n != nullptr && n->_val == i);
    }

    for (int i = 1; i < 50; ++i) {
        auto n = t.get_node(i);
        assert (n != nullptr && n->_val == i);
        n = t.remove(n);
        assert (n != nullptr && n->_val == i && "Did not remove the correct key");
        delete n;
    }

    inttree_print(&t);
    printf("//Inorder: ");
    inttree_inorder(&t, t._root);
    printf( "\n");
    fflush(stdout);

    valid_black_height(&t);
    valid_red_kids(&t);

    //delete_nodes(&t, t._root);
}

#endif