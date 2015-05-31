#include <iostream>
#include <time.h>

template<class T>
class Tuple
{
public:
    T data;
	Tuple()
	{
		data = rand() % 10 + 1;
	}
	~Tuple()
	{

	}
	bool operator<(const Tuple &t) const
	{
		if (data < t)
			return true;
		return false;
	}
};


int main()
{
	Tuple<int> t[2];
	srand(time(NULL));
	for (int i = 0; i < 2; i++)
		t[i] = Tuple<int>();

	if (t[0] < t[1])
		std::cout << "it smaller" << std::endl;

	for (int i = 0; i < 2; i++)
		std::cout << i << ": " << t[i].data << std::endl;
}
