#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


    struct FieldProperty
	{
		FieldProperty(const char* fieldName, const type_info& type)
		: fieldName(fieldName)
		, type(type)
		{
		}
		const char* fieldName;
		const type_info& type;
	};


int main()
{
    FieldProperty test("TEST", typeid(int));
    return 0;
}
