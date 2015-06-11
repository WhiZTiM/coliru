#include <iostream>
#include <map>
 
 
const std::string MY_PROPERTY_KEY = "Map key";
 
/**
 * This is the class we want to test. The important bit is the way it accesses a map as a property of its template parameter type,
 * and then assumes that whatever comes out of the map is a non-scalar type and supports getStringProperty.
 */
template <typename ImplT>
class ClassToTest {
    ImplT *impl;
	std::string property;
public:
	ClassToTest(ImplT* impl) : impl(impl) {
		std::string value = impl->getMap().at(MY_PROPERTY_KEY).getStringProperty();
 
		std::cout << value << std::endl;
	}
 
	std::string getProperty() const { return property; }
 
};
 
/**
 * This is the type in the map - we can define this type as we wish provided it supports getStringProperty()
 */
class MockMapItem {
	std::string property;
public:
	MockMapItem() {
		std::cout << "OH NO!!! We constructed a new MockMapItem!" << std::endl;
	};
	MockMapItem(const std::string& value) : property(value) {
  		std::cout << "OH NO!!! We constructed a new MockMapItem with a string!" << std::endl;

	}
	MockMapItem(const MockMapItem&) {
		std::cout << "OH NO!!! We copied a MockMapItem!" << std::endl;
	}
 
	std::string getStringProperty() const { return property; }
};
 
/**
 * This is the typedef for the map - the key type should be string and the value type should be a non-scalar type (to match the expectations of the class being tested)
 */
typedef typename std::map<std::string, MockMapItem > ItemMap;
 
/**
 * This is our mock implementation which will be passed to the class being tested as its template parameter (and constructor parameter). 
 * It has to support getMap(), which should return an ItemMap. Otherwise, we can do whatever we like with it.
 */
class MockImpl {
	const ItemMap& mmap;
public:
	MockImpl(ItemMap& map) : mmap(map) {
	}
 
	const ItemMap& getMap() { return mmap; }
};
 
/**
 * The main() method would be a google mock test, but this will do for simplicity
 */
int main(int, char **) {
	MockMapItem map_item("some string value");
	// if mocking, could define some expectations here like EXPECT_CALL(map_item, getStringProperty().Times(Exactly(1)).WillOnce(Return("some string value"));
 
	ItemMap map;
	map.emplace(MY_PROPERTY_KEY, std::move(map_item));
 
	MockImpl mock(map);
	// if mocking, could define some expectations here like EXPECT_CALL(mock, getMap().Times(Exactly(1)).WillOnce(ReturnRef(map));
 
	ClassToTest<MockImpl> thing(&mock);
 
	return 0;
}