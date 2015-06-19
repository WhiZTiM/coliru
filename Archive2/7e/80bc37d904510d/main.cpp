#include <map>
#include <string>
#include <iostream>

struct MockMapItem {
	std::string property;

	MockMapItem(const std::string& value) : property(value) {
  		std::cout << "We constructed a new MockMapItem with a string!" << std::endl;

	}
};

typedef typename std::map<std::string, const MockMapItem&& > ItemMap;

int main()
{
    MockMapItem map_item("some string value");

	ItemMap themap;
	themap.emplace("something", std::move(map_item));
 
}
