#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

struct Person {
    int age;
    bool passed;
    enum Condition { Alive, Dead } condition;

    friend std::ostream& operator<<(std::ostream& os, Condition c) {
        switch (c) {
            case Alive : return os << "Alive";
            case Dead  : return os << "Dead";
        }
        throw "failure"; //TODO
    }
};

struct Order {
    struct Item {
        std::string serialnumber, name;
        Person person;
        int quantity;
    };

    std::vector<Item> items;
};

using Tree = boost::property_tree::ptree;

Tree make_tree(Person const& p) {
    Tree pt;
    pt.put("<xmlattr>.age", p.age);
    pt.put("<xmlattr>.passed", p.passed?"Yes":"No");
    pt.put_value(p.condition);

    return pt;
}

Tree make_tree(Order::Item const& p) {
    Tree pt;
    pt.put("SN",     p.serialnumber);
    pt.put("NAME",   p.name);
    pt.put_child("Person", make_tree(p.person));
    pt.put("QTY",    p.quantity);

    return pt;
}

Tree make_tree(Order const& p) {
    Tree pt;
    Tree& order = pt.put_child("ORDER", {});
    for (auto& item : p.items)
        order.add_child("ITEM", make_tree(item));

    return pt;
}

#include <iostream>
/*
 *  <ORDER>
 *    <ITEM>
 *      <SN>132487A-J</SN>
 *      <NAME>crank casing</NAME>
 *      <Person age="12" passed="Yes">Alive</Person>
 *      <QTY>1</QTY>
 *    </ITEM>
 *  </ORDER>
 *
 */

int main() {
    Order const order {
        {
            Order::Item {
                "132487A-J", "crank casing", 
                Person { 12, true, Person::Alive },
                1
            },
        }
    };
    
    using namespace boost::property_tree;
    auto settings = xml_parser::xml_writer_make_settings<std::string>(' ', 4, "utf-8");
    write_xml(std::cout, make_tree(order), settings);
}
