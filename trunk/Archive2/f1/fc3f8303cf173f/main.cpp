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
std::pair<bool, int> balanced_and_size(node<T>* root) {
    if (root == nullptr) return std::make_pair(true, 0);
    auto left_pair = balanced_and_size(root);
    auto right_pair = balanced_and_size(root);
    bool balanced = left_pair.first 
                 && right_pair.first 
                 && std::abs(left_pair.second - right_pair.second) <= 1;
    int size = left_pair.second + 1 + right_pair.second;
    return std::make_pair(balanced, size);
}

template<typename T>
bool is_balanced(node<T>* root) {
    return std::get<0>(balanced_and_size(root));
}

int main() {}