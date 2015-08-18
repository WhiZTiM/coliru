#include <iostream>
#include <string>
#include <vector>
#include <functional>

template<typename T>
class Foo0
{
public:
    Foo0(int* copyCount)
    	: m_copyCount(copyCount)
	{
	}

	virtual ~Foo0()
	{
	}

	void operator()() {}

	Foo0(const Foo0& other)
	{
		m_copyCount = other.m_copyCount;
		if (m_copyCount)
			(*m_copyCount)++;
	}

	Foo0& operator=(const Foo0& other)
	{
		if (this != &other)
		{
			m_copyCount = other.m_copyCount;
			if (m_copyCount)
				(*m_copyCount)++;
		}

		return *this;
	}

	Foo0(Foo0&& other) noexcept
	{
		m_copyCount = other.m_copyCount;
		other.m_copyCount = nullptr;
	}

	Foo0& operator=(Foo0&& other) noexcept
	{
		if (this != &other)
		{
			m_copyCount = other.m_copyCount;
			other.m_copyCount = nullptr;
		}

		return *this;
	}

private:
	int* m_copyCount;
	T m_data;
};

struct SmallDataForFoo{};
using Foo = Foo0<SmallDataForFoo>;

struct BigDataForFoo
{
	int m_data[100];
};

using BigFoo = Foo0<BigDataForFoo>;

int main()
{
    int copyCount = 0;

	Foo foo{&copyCount};
	
    auto lambda = [foo] {};
	std::cout << "cc after lambda creation = " << copyCount << std::endl;
    
	std::function<void()> f{std::move(lambda)};
	std::cout << "cc after func creation = " << copyCount << std::endl;

	std::function<void()> f1{std::move(f)};
	std::cout << "cc after func move = " << copyCount << std::endl;

	std::function<void()> f2 = f1;
	std::cout << "cc after func copy ctor = " << copyCount << std::endl;

    return 0;
}
