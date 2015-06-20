//---------------------------------------
// A cahce example
//---------------------------------------
// Amir Kirsh, amirk@mta.ac.il
//---------------------------------------
#include <map>
#include <string>
#include <iostream>
#include <ctime>

using namespace std;

string fetchUrl(const string& url) {
    // this is just a stub
	return "url content for " + url;
}

class Date {
	long time;
public:
	// assume this returns the current date + daysFromNow.
	// Note that daysFromNow can be negative, zero or positive
	Date(int daysFromNow = 0) : time(clock() + daysFromNow * 24*60*60*1000) {}
	// true if this date is later than other, false otherwise
	bool operator>(const Date& other)const {
		return time > other.time;
	}
};

template<class KEY, class VALUE, class FetchFunctor>
class Cache {
    class ValueHolder {
    public:
        VALUE content;
        ValueHolder() {}
        ValueHolder(VALUE _content) : content(_content), expiryDate(Date(365)), lastAccessedDate(Date()) {}
    	operator VALUE() {lastAccessedDate = Date(); return content;}
    	bool expired()const {return Date() > expiryDate;}
    	Date lastAccessed()const {return lastAccessedDate;}
    private:
        Date expiryDate;
    	mutable Date lastAccessedDate;
    };
	map<KEY, ValueHolder> theCache;
	const size_t max_size;
    FetchFunctor fetchFunctor;
public:
	explicit Cache(size_t _max_size, FetchFunctor _fetchFunctor): max_size(_max_size), fetchFunctor(_fetchFunctor) {}
	VALUE get(KEY key) {
        VALUE value;
		typename map<KEY, ValueHolder>::iterator itr = theCache.find(key);
		if(itr != theCache.end() && !itr->second.expired()) {
		    return itr->second;
        }
		else {
    		VALUE val(fetchFunctor(key));
            theCache[key] = val;
    		if(oversized()) {
    			for(int i=250; oversized() && i>=0; i-=10) {
    				removeNotAccessedInLastXdays(i);
    			}
    		}
        	return val;
		}
	}
	bool oversized()const {
		return theCache.size() > max_size;
	}
	void removeNotAccessedInLastXdays(int numDays) {
		Date removalPoint(-numDays);
		for(typename map<KEY, ValueHolder>::iterator itr = theCache.begin(); 
			itr != theCache.end(); ) {
				if(removalPoint > itr->second.lastAccessed()) {
					cout << "removing: " << itr->second.content << endl;
					itr = theCache.erase(itr);
				} else {
					++itr;
				}
		}
	}
};

template<class KEY, class VALUE, class FetchFunctor>
Cache<KEY, VALUE, FetchFunctor> createCache(size_t _max_size, FetchFunctor _fetchFunctor) {
    return Cache<KEY, VALUE, FetchFunctor>(_max_size, _fetchFunctor);
}

int main() {
    // see a note on the need for the method createCache here:
    // http://stackoverflow.com/questions/7921380/why-arent-class-template-constructor-arguments-automatically-determined
    // and on the trick of providing 2 template parameters for a method that requires 3, read here:
    // http://stackoverflow.com/questions/13554496/partial-template-function-specification-in-c-works-but-why
	auto cache = createCache<string, string>(10, fetchUrl);
	cout << cache.get("http://www.mta.ac.il") << endl;
	cout << cache.get("1") << endl;
	cout << cache.get("2") << endl;
	cout << cache.get("3") << endl;
	cout << cache.get("4") << endl;
	cout << cache.get("5") << endl;
	cout << cache.get("a") << endl;
	cout << cache.get("b") << endl;
	cout << cache.get("c") << endl;
	cout << cache.get("d") << endl;
	cout << cache.get("e") << endl;
	cout << cache.get("f") << endl;
	cout << cache.get("g") << endl;
	cout << cache.get("h") << endl;
	return 1;
}