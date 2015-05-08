#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

template <typename Tree, typename Out, typename T = std::string>
Out enumerate_path(Tree const& pt, typename Tree::path_type path, Out out) {
    if (path.empty())
        return out;

    if (path.single()) {
        *out++ = pt.template get<T>(path);
    } else {
        auto head = path.reduce();
        for (auto& child : pt) {
            if (head == "*" || child.first == head) {
                out = enumerate_path(child.second, path, out);
            }
        }
    }

    return out;
}

int main() {

    std::ostream_iterator<std::string> out(std::cout, ", ");
    using namespace boost::property_tree;

    ptree pt;
    read_json("input.txt", pt);

    std::cout << "\nSpecific children but in arrays: ";
    enumerate_path(pt, "Foo.Bar..FooBar..FooBarDeep1..FooBarDeepDeep6..FooBarValue2", out);

    std::cout << "\nSingle wildcard: ";
    enumerate_path(pt, "Foo.Bar..FooBar..FooBarDeep1..*..FooBarValue2", out);

    std::cout << "\nTwo wildcards: ";
    enumerate_path(pt, "Foo.Bar..FooBar..*..*..FooBarValue2", out);
}
