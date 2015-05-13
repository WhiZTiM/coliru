#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>

struct chapter {
    std::string name, link;
    std::vector<chapter> sub_chapters;
};

void find_all_chapters(boost::property_tree::ptree const& pt, chapter& into) {
    for(auto& ch : pt) {
        if (ch.first == "chapter") {
            into.sub_chapters.push_back({ 
                    ch.second.template get<std::string>("name"),
                    ch.second.template get<std::string>("link"),
                    {}
                });

            find_all_chapters(ch.second, into.sub_chapters.back());
        }
    }
}

void print(chapter const& book_or_chapter, std::string const& indent = "") 
{
    for (auto& ch : book_or_chapter.sub_chapters) {
        std::cout << indent << " - Chapter '" << ch.name << "', link: '" << ch.link << "'\n";
        print(ch, "    " + indent);
    }
}

int main() {
    boost::property_tree::ptree pt;
    boost::property_tree::xml_parser::read_xml(std::cin, pt, boost::property_tree::xml_parser::trim_whitespace );

    chapter book;
    find_all_chapters(pt.get_child("xml"), book);

    print(book);
}
