#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>

struct chapter {
    std::string name, link;
};

template <typename Tree, typename Out>
Out find_all_chapters(Tree const& pt, Out out) {
    using namespace boost::property_tree;
    BOOST_FOREACH(typename Tree::value_type const& ch, pt) {
        if (ch.first == "chapter") {
            *out++ = chapter { 
                    ch.second.template get<std::string>("name"),
                    ch.second.template get<std::string>("link")
                };

            out = find_all_chapters(ch.second, out);
        }
    }
    return out;
}

int main() {
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(std::cin, pt, boost::property_tree::xml_parser::trim_whitespace );

    std::vector<chapter> m_chapters;
    find_all_chapters(pt.get_child("xml"), back_inserter(m_chapters));

    for (auto& ch : m_chapters)
        std::cout << "Chapter '" << ch.name << "', link: '" << ch.link << "'\n";
}
