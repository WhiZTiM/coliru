#include <iostream>
#include <locale>
#include <sstream>
#include <iomanip>
using namespace std;

class Foo : public std::moneypunct<char> {
protected:
    char_type do_decimal_point() const {
        cout << "Hit Foo::do_decimal_point\n";
        return ',';
    }
    char_type do_thousands_sep() const {
        cout << "Hit Foo::do_thousands_sep\n";
        return '.';
    }
};

int main()
{
    cout.imbue(locale(locale("en_US.UTF8"), new Foo));

    const moneypunct<char>* temp = &use_facet<std::moneypunct<char>>(cout.getloc());

    cout << temp->decimal_point() << endl << temp->thousands_sep() << endl;

    istringstream USCurency("1,234.56 -1,234.56 1.234,56 -1.234,56");
    USCurency.imbue(cout.getloc());

    long double value;

    USCurency >> get_money(value, true);

    return 0;
}