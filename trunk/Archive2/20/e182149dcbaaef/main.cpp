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

template<class KEY, class VALUE>
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
public:
	explicit Cache(size_t _max_size): max_size(_max_size) {}
    template<class FetchFunctor>
	VALUE get(KEY key, FetchFunctor fetchFunctor) {
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

int main() {
	Cache<string, string> cache(10);
	cout << cache.get("http://www.mta.ac.il", fetchUrl) << endl;
	cout << cache.get("1", fetchUrl) << endl;
	cout << cache.get("2", fetchUrl) << endl;
	cout << cache.get("3", fetchUrl) << endl;
	cout << cache.get("4", fetchUrl) << endl;
	cout << cache.get("5", fetchUrl) << endl;
	cout << cache.get("a", fetchUrl) << endl;
	cout << cache.get("b", fetchUrl) << endl;
	cout << cache.get("c", fetchUrl) << endl;
	cout << cache.get("d", fetchUrl) << endl;
	cout << cache.get("e", fetchUrl) << endl;
	cout << cache.get("f", fetchUrl) << endl;
	cout << cache.get("g", fetchUrl) << endl;
	cout << cache.get("h", fetchUrl) << endl;
	return 1;
}