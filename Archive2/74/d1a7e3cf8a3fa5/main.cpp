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

class UrlData {
	string content;
	Date expiryDate;
	mutable Date lastAccessedDate;
public:
	UrlData(){}
	UrlData(const string& _content) : content(_content), expiryDate(Date(365)), lastAccessedDate(Date()) {}
	operator const char*() {lastAccessedDate = Date(); return content.c_str();}
	bool expired()const {return Date() > expiryDate;}
	Date lastAccessed()const {return lastAccessedDate;}
};

class Cache {
	map<string, UrlData> urlToContent;
	const size_t max_size;
public:
	explicit Cache(size_t _max_size): max_size(_max_size) {}
	string getUrlContent(const string& url) {
		map<string, UrlData>::iterator urlDataItr = urlToContent.find(url);
		string content;
		if(urlDataItr == urlToContent.end() || urlDataItr->second.expired()) {
			content = fetchUrl(url);
			urlToContent[url] = UrlData(content);
		}
		else {
			content = urlDataItr->second;
		}
		if(oversized()) {
			for(int i=250; oversized() && i>=0; i-=10) {
				removeNotAccessedInLastXdays(i);
			}
		}
		return content;
	}
	bool oversized()const {
		return urlToContent.size() > max_size;
	}
	void removeNotAccessedInLastXdays(int numDays) {
		Date removalPoint(-numDays);
		for(map<string, UrlData>::iterator urlDataItr = urlToContent.begin(); 
			urlDataItr != urlToContent.end(); ) {
				if(removalPoint > urlDataItr->second.lastAccessed()) {
					cout << "removing: " << urlDataItr->second << endl;
					urlDataItr = urlToContent.erase(urlDataItr);
				} else {
					++urlDataItr;
				}
		}
	}
};

int main() {
	Cache cache(10);
	cout << cache.getUrlContent("http://www.mta.ac.il") << endl;
	cout << cache.getUrlContent("1") << endl;
	cout << cache.getUrlContent("2") << endl;
	cout << cache.getUrlContent("3") << endl;
	cout << cache.getUrlContent("4") << endl;
	cout << cache.getUrlContent("5") << endl;
	cout << cache.getUrlContent("a") << endl;
	cout << cache.getUrlContent("b") << endl;
	cout << cache.getUrlContent("c") << endl;
	cout << cache.getUrlContent("d") << endl;
	cout << cache.getUrlContent("e") << endl;
	cout << cache.getUrlContent("f") << endl;
	cout << cache.getUrlContent("g") << endl;
	cout << cache.getUrlContent("h") << endl;
	return 1;
}