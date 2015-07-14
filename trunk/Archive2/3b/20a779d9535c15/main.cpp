#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>

template<class T, class _Pr>
T unstable_remove_if(T first, T last, _Pr p)
{
    while (1) {
		while ((first != last) && !p(*first)) {
			++first;
		}
		if (first == last--) break;
		while ((first != last) && p(*last)) {
			--last;
		}
		if (first == last) break;
		*first++ = std::move(*last);
	}
	return first;
}

template<class T, class V>
T unstable_remove(T first, T last, V const& v)
{
    while (1) {
		while ((first != last) && !(*first == v)) {
			++first;
		}
		if (first == last--) break;
		while ((first != last) && (*last == v)) {
			--last;
		}
		if (first == last) break;
		*first++ = std::move(*last);
	}
	return first;
}

int main()
{
    std::string str1 = "Text with some   spaces";
    str1.erase(std::remove(str1.begin(), str1.end(), ' '),
               str1.end());
    std::cout << "Stable:   " << str1 << '\n';
 
    std::string str1a = "Text with some   spaces";
    str1a.erase(unstable_remove(str1a.begin(), str1a.end(), ' '),
               str1a.end());
    std::cout << "Unstable: " << str1a << '\n';
 
    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(std::remove_if(str2.begin(), 
                              str2.end(),
                              [](char x){return std::isspace(x);}),
               str2.end());
    std::cout << "Stable:   " << str2 << '\n';
 
    std::string str2a = "Text\n with\tsome \t  whitespaces\n\n";
    str2a.erase(unstable_remove_if(str2a.begin(), 
                              str2a.end(),
                              [](char x){return std::isspace(x);}),
               str2a.end());
    std::cout << "Unstable: " << str2a << '\n';
}