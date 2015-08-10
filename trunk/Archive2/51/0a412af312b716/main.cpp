#include <iostream>
#include <vector>
#include <functional>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

using FilterContainer = std::vector<std::function<bool(int)>>;

int computeDivisor()
{
    return (rand() % 100) + 1;
}

void addDivisorFilter(FilterContainer &filters)
{
	auto divisor = computeDivisor();
	cout << typeid(divisor).name() << " = " << divisor << "\n";
	// danger! ref to divisor will dangle!
	filters.emplace_back([&divisor](int value) { return value % divisor == 0; });
}

bool divBy4(int value)
{
	return value % 4 == 0;
}

class DivisorGetter
{
public:
    DivisorGetter()
	{
		divisor = (rand() % 100) + 1;
	}
	void addFilter(FilterContainer &filters) const;
private:
	int divisor; // used in Widget's filter
};

void DivisorGetter::addFilter(FilterContainer &filters) const
{
    filters.emplace_back([=](int value) { return value % divisor == 0; });
}

int main()
{
	srand(time(NULL));

	FilterContainer filters;
	
	filters.emplace_back(divBy4);
	
	//addDivisorFilter(filters);
    {
        DivisorGetter dg;
	    dg.addFilter(filters);
    }
    
	auto testValues = { 1, 2, 3, 4, 0 };
	for (auto& v : testValues)
	{
		cout << "test value: " << v << "\t";
		for (auto f: filters)
		{
			cout << f(v) << " ";
		}
		cout << "\n";
	}
	cout << "\njob done\n";
	return 0;
}