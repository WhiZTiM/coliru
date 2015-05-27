#include <iostream>
#include <string>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}

#include <iostream>
#include <string>
using namespace std;
//-------------------------------
struct road
{
    string name;
	double length;
	int speed;
};
int main()
{
	road k1, k2, k3;
	k1.name = " Kaunas - Vilnius ";     k1.length = 105.0; k1.speed = 110;
	k2.name = " Kaunas - Atylus ";      k2.length = 65.6;  k2.speed = 90;
	k3.name = " Vilnius - Panevezys ";  k3.length = 136.0; k3.speed = 120;
	cout << k1.name << ", " << k1.length << ", " << k1.speed << ", " << endl;
	cout << k2.name << ", " << k2.length << ", " << k2.speed << ", " << endl;
	cout << k3.name << ", " << k3.length << ", " << k3.speed << ", " << endl;
	cout << "--------------------------------------\n";
};
	struct Auto
	{
		string brand;
		string fuel;
		double consume;
	};	
	int main()
	{
		Auto a1, a2;
		a1.brand = " Opel Meriva ";       a1.fuel = "gasoline";        a1.consume = 7.5;
		a2.brand = " Volkswagen Golf ";   a2.fuel = "diesel";          a2.consume = 6.3;
		cout << " Cars:" << endl;
		cout << a1.brand << ", " << a1.fuel << ", " << a1.consume  << endl;
		cout << a2.brand << ", " << a2.fuel << ", " << a2.consume  << endl;
		return 0;
}