#include <iostream>
#include <string>
#include <ctime>

template<class T, int N>
class Tuple
{
public:
    T *podaci;
	int n;

	Tuple()
	{
		n = N;
		podaci = new T[n];
		if (std::is_same<T, int>())
			generateNumber();
		if (std::is_same<T, std::string>())		
			generateString();
	}
	~Tuple(){}

	bool operator<(const Tuple &t) const
	{
		int it = 0;
		while (it != n)
		{
			if (it == n || t.podaci[it] < podaci[it])
				return false;
			else if (podaci[it] < t.podaci[it])
				return true;
			it++;
		}
		return (it != n);
	}
	bool operator>(const Tuple &t) const
	{
		int it = 0;
		while (it != n)
		{
			if (it == n || t.podaci[it] > podaci[it])
				return false;
			else if (podaci[it] > t.podaci[it]) 
				return true;
			it++;
		}
		return (it != n);
	}

	void generateNumber()
	{
		for (int i = 0; i < n; i++)
			podaci[i] = rand() % 10 + 1;
	}
	void generateString()
	{
		static const char alphanum[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";

		for (int i = 0; i < n; ++i)
			podaci[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
		//podaci[n-1] = 0;
	}
};

template<class T>
void sort(T *x, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			if (x[j] > x[j + 1])
			{
				T temp = x[j + 1];
				x[j + 1] = x[j];
				x[j] = temp;
			}
		}
	}
}

template<class T>
void print(T *t, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < t->n; j++)
			std::cout << t[i].podaci[j];
		std::cout << std::endl;
	}
}

int main()
{
	Tuple<int, 10> t[20];
	srand(time(NULL));
	for (int i = 0; i < 20; i++)
		t[i] = Tuple<int, 10>();
	
	print(t, 20);
	sort(t, 20);
	std::cout << "\nSorted\n" << std::endl;
	print(t, 20);


	std::cout << "\nString\n" << std::endl;
	Tuple<std::string, 10> s[20];
	for (int i = 0; i < 20; i++)
		s[i] = Tuple<std::string, 10>();

	print(s, 20);
	sort(s, 20);
	std::cout << "\nSorted\n" << std::endl;
	print(s, 20);

}