#include <iostream>
#include <string>
#include <vector>
#include <tuple>

template<typename T>
struct node {
    T data;
    node* left;
    node* right;
};

template<typename T>
void tree_get_minmax_height(node<T> const* const root, int& min, int&max) {
    if (root==nullptr) {
        min = 0;
        max = 0;
    }
    tree_get_minmax_height(root->left, min, max);
    min += 1;
    max += 1;
    if (root->right) {
        size_t rightmin, rightmax);
        tree_get_minmax_height(root->right, rightmin, rightmax);
        min += rightmin;
        max += rightmax;
    }
}

template<typename T>
bool is_balanced(node<T> const* const root) {
    size_t min,max;
    tree_get_minmax_height(root, min, max);
    return max-min <= 1;
}

int main() {}