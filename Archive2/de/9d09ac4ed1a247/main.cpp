
#include <iostream>
#include <time.h>

template<class T, int n>
class Tuple
{
public:
    T* data;
	Tuple()
	{
		data = new T[n];
		for (int i = 0; i < n; i++)
			data[i] = rand() % 10 + 1;
	}
	~Tuple()
	{

	}
	bool operator>(const Tuple &t) const
	{
		while (data != &data[4])
		{
			if (t.data == &t.data[4] || *t.data < *data) return false;
			else if (*data<*t.data) return true;
			++data; ++t.data;
		}
		return (t.data != &t.data[4]);
	}
};


int main()
{
	Tuple<int, 5> t[2];
	srand(time(NULL));
	for (int i = 0; i < 2; i++)
		t[i] = Tuple<int, 5>();

	if (t[0] > t[1])
		std::cout << "it smaller" << std::endl;

	for (int i = 0; i < 2; i++)
		std::cout << i << ": " << t[i].data << std::endl;
}