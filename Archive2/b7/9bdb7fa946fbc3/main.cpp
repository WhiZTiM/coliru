#include <iostream>
#include <iomanip>
#include <sstream>
#include <locale>
#include <cstring>

using namespace std;

template <typename T>
class Bar : public T {
private:
	void Init(const T* money){
		const auto vTablePtrSize = sizeof(void*);

		memcpy(reinterpret_cast<char*>(this) + vTablePtrSize, reinterpret_cast<const char*>(money) + vTablePtrSize, sizeof(T) - vTablePtrSize);
	}
protected:
	typename T::char_type do_decimal_point() const {
		return typename T::char_type(',');
	}

	typename T::char_type do_thousands_sep() const {
		return typename T::char_type('.');
	}
public:
	Bar(){
		Init(&use_facet<T>(cout.getloc()));
	}

	Bar(const T* money){
		Init(money);
	}
};

int main()
{
	cout.imbue(locale("en_US.UTF8"));

    long double value;
	istringstream BarCurency("1.234.567,89");

	BarCurency.imbue(locale(cout.getloc(), new Bar<moneypunct<char>>()));

	BarCurency >> get_money(value);

	cout << value;

	return 0;
}