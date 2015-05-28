#include <boost/intrusive/set.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace boost::intrusive;

struct foo : set_base_hook<> {
    std::string name;
    foo(char const* n) : name(n) {}

    bool operator<(const foo &b) const { return name < b.name; }
};

int main()
{
    std::vector<foo> v;
    v.emplace_back("a");
    v.emplace_back("b");
    v.emplace_back("c");

    using Tree = rbtree<foo>;

    Tree tree;
    tree.insert_unique(v.begin(), v.end());

    for (auto key : { "a", "b", "c", "missing" })
    {
        std::cout << "\nusing key '" << key << "': ";
        auto start = tree.iterator_to(*tree.find(key));

        if (start != tree.end()) {
            for (auto it = Tree::reverse_iterator(++start); it != tree.rend(); ++it)
                std::cout << it->name << " ";
        }
    }
}
