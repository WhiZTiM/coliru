
#include <iostream>
#include <time.h>

template<class T, int n>
class Tuple
{
public:
    T *podaci;
	Tuple()
	{
		podaci = new T[n];
		for (int i = 0; i < n; i++)
			podaci[i] = rand() % 10 + 1;
	}
	Tuple(T *input)
	{
		podaci = new T[n];
		for (int i = 0; i < n; i++)
			podaci[i] = input[i];
	}
	~Tuple()
	{

	}
	bool operator<(const Tuple &t) const
	{
		int it = 0;
		while (podaci != &podaci[4])
		{
			if (t.podaci == &t.podaci[4] || t.podaci[it] > podaci[it]) return false;
			else if (podaci[it] > t.podaci[it]) return true;
			it++;
		}
		return (t.podaci != &t.podaci[4]);
	}
	bool operator>(const Tuple &t) const
	{
		int it = 0;
		while (podaci != &podaci[4])
		{
			if (t.podaci == &t.podaci[4] || t.podaci[it] < podaci[it]) return false;
			else if (podaci[it] < t.podaci[it]) return true;
			it++;
		}
		return (t.podaci != &t.podaci[4]);
	}
};

template<class T>
void sort(T *x, int N)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			if (x[j] < x[j + 1])
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
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < N; j++)
			std::cout << t[i].podaci[j] << ",";
		std::cout << std::endl;
	}
}

int main()
{
	Tuple<int, 5> t[10];
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
		t[i] = Tuple<int, 5>();
	
	print(t, 5);
	sort(t, 10);
	std::cout << "\nSorted\n" << std::endl;
	print(t, 5);
}