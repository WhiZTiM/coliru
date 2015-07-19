#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

enum Flags { good=0, fail=1, bad=2, eof=4 };

constexpr Flags operator|(Flags f1, Flags f2) { return Flags(int(f1)|int(f2)); }

constexpr int f(Flags x)
{
    switch (x) {
    case bad:         return 0xBAAD;
    case eof:         return 0xE0F;
    case bad|eof:     return 0xBAADE0F;
    default:          return 0x04;
    }
}

int main() {
    int v[f(good)];
	cout << hex << f(good) << '\n';
	cout << f(bad|eof);
	return 0;
}
