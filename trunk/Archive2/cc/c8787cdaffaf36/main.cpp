#include <list>

template <typename T>
struct MyCollection
{
    std::list<T> objects;
    
    typename std::list<T>::iterator begin() {
    	return objects.begin();
	}

	typename std::list<T>::const_iterator begin() const {
	//                                            ~~~~^
		return objects.cbegin();
	}

	typename std::list<T>::const_iterator cbegin() const {
		return begin();
	}

	typename std::list<T>::iterator end() {
		return objects.end();
	}

	typename std::list<T>::const_iterator end() const {
	//                                          ~~~~^
		return objects.cend();
	}

	typename std::list<T>::const_iterator cend() const {
		return end();
	}
};

int main()
{
    const MyCollection<int> c{};
    for (const auto& i : c) {}
}
