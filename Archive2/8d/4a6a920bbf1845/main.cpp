#include <iostream>
#include <utility>
using namespace std;
 
class ABC
{
    public:
	ABC(){cout << "ABC" << endl;}
	~ABC() noexcept {cout << "~ABC" << endl;}
	ABC(ABC const&) {cout << "copy" << endl;}
	ABC(ABC&&) noexcept {cout << "move" << endl;}
	void operator=(ABC const&){cout << "copy=" << endl;}
	void operator=(ABC&&) noexcept {cout << "move=" << endl;}
};
 
int main() {
	std::pair<std::string, ABC> myPair{{}, ABC{}};
	return 0;
}