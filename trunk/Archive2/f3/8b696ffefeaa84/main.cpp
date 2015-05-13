#include <iostream>
#include <string>
#include <vector>

class EL {
public:
    EL(std::string str) {}
private:
	std::vector<char> m_characters;
};

class PL {
public:
	template<typename T>
	PL(T&& el) {
		static_assert(std::is_same<typename std::remove_reference<T>::type, EL>::value,
			"Expected EL argument");
		m_el.emplace_back(std::forward<T>(el));
	}

private:
	std::vector<EL> m_el;
};


int main()
{
	std::vector<PL> m_pl;

	m_pl.emplace_back(PL(EL("Hello")));

}
