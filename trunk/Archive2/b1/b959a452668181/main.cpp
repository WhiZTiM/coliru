#include <iostream>
#include <iomanip>
#include <sstream>
#include <locale>
#include <cstring>

using namespace std;

template <typename T>
class Foo : public T {
protected:
    typename T::string_type m_grouping;
	typename T::string_type m_curr_symbol;
	typename T::string_type m_positive_sign;
	typename T::string_type m_negative_sign;
	int m_frac_digits;
	typename T::pattern m_pos_format;
	typename T::pattern m_neg_format;

	typename T::char_type do_decimal_point() const {
		return typename T::char_type(',');
	}

	typename T::char_type do_thousands_sep() const {
		return typename T::char_type('.');
	}

	typename T::string_type do_grouping() const {
		return m_grouping;
	}

	typename T::string_type do_curr_symbol() const {
		return m_curr_symbol;
	}

	typename T::string_type do_positive_sign() const {
		return m_positive_sign;
	}

	typename T::string_type do_negative_sign() const {
		return m_negative_sign;
	}

	int do_frac_digits() const {
		return m_frac_digits;
	}

	typename T::pattern do_pos_format() const {
		return m_pos_format;
	}

	typename T::pattern do_neg_format() const {
		return m_neg_format;
	}
public:
	Foo(const T& defaultFacet) : m_grouping(defaultFacet.grouping()),
		                         m_curr_symbol(defaultFacet.curr_symbol()),
								 m_positive_sign(defaultFacet.positive_sign()),
								 m_negative_sign(defaultFacet.negative_sign()),
								 m_frac_digits(defaultFacet.frac_digits()),
								 m_pos_format(defaultFacet.pos_format()),
								 m_neg_format(defaultFacet.neg_format()) {}
};

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

	istringstream USCurency("1.234,56"); USCurency.imbue(locale(cout.getloc(), new Foo<moneypunct<char>>(use_facet<moneypunct<char>>(cout.getloc()))));
	//istringstream USCurency("1,234.56");

	long double value;

	USCurency >> get_money(value);

	cout << value;

	istringstream BarCurency("1.234.567,89");

	BarCurency.imbue(locale(cout.getloc(), new Bar<moneypunct<char>>()));

	BarCurency >> get_money(value);

	cout << value;

	return 0;
}