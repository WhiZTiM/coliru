#include <string>

template <typename Tree, typename F, typename Pred/* = bool(*)(Tree const&)*/, typename PathType = std::string>
   void visit_if(Tree& tree, F const& f, Pred const& p, PathType const& path = PathType())
{
    if (p(tree))
        f(path, tree);

    for(auto& child : tree)
        if (path.empty())
            visit_if(child.second, f, p, child.first);
        else
            visit_if(child.second, f, p, path + "." + child.first);
}

template <typename Tree, typename F, typename PathType = std::string>
   void visit(Tree& tree, F const& f, PathType const& path = PathType())
{
    visit_if(tree, f, [](Tree const&){ return true; }, path);
}

#include <boost/property_tree/ptree.hpp>

bool is_leaf(boost::property_tree::ptree const& pt) {
    return pt.empty();
}

#include <iostream>
int main()
{
    using boost::property_tree::ptree;
    auto process = [](ptree::path_type const& path, ptree const& node) {
            std::cout << "leave node at '" << path.dump() << "' has value '" << node.get_value("") << "'\n";
        };

    ptree pt;
    pt.put("some.deeply.nested.values", "just");
    pt.put("for.the.sake.of.demonstration", 42);
    
    visit_if(pt, process, is_leaf);
}
