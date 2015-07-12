//============================================================================
// Name        : IntervalMap.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <stdio.h>

using namespace std;

struct IMDSpecialKey {
    string start;
	string end;
	string transactionCode;
	int priority;
};
struct cmp_str {
	bool operator()(const IMDSpecialKey& lhs, const IMDSpecialKey& rhs) const {
        
        if (lhs.transactionCode < rhs.transactionCode) {
    		
				if (lhs.start < rhs.start) {
					if (lhs.end < rhs.end) {
						return true;
					} else {
						return lhs.start < rhs.start;
					}
				}
				 else {
					return lhs.transactionCode < rhs.transactionCode;
				} 

			}
		return false;

		/*if (lhs.start < rhs.start) {
			if (lhs.end < rhs.end) {
				//if (lhs.priority < rhs.priority) {
					if (lhs.transactionCode < rhs.transactionCode) {
						return true;
					} //else {
						//return lhs.priority < rhs.priority;
					//}
				} else {
					return lhs.end < rhs.end;
				}

			} else if (lhs.end == rhs.end) {
				return lhs.start < rhs.start;
			}
		}
		else if (lhs.start == rhs.start) {
			if (lhs.end < rhs.end) {
				if (lhs.priority < rhs.priority) {
					if (lhs.transactionCode < rhs.transactionCode) {
						return true;
					} else {
						return lhs.priority < rhs.priority;
					}
				} else {
					return lhs.end < rhs.end;
				}

			} else {
				return lhs.start < rhs.start;
			}
		}
		return false;*/
	}
};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	string lala = "LALALA";
	map<IMDSpecialKey, string, cmp_str> mapSample_;

	IMDSpecialKey temp;
	temp.start = "67000000000";
	temp.end = "67999999999";
	temp.priority = 2;
	temp.transactionCode = "00";

	mapSample_.insert(make_pair(temp, "132"));

	temp = {"42101000000","42101099999","01", 2};
	mapSample_.insert(make_pair(temp, "130"));

	temp = {"42101000000","42101099999","00", 2};
	mapSample_.insert(make_pair(temp, "131"));


	temp = {"32100000000","32199999999","11",2};
	mapSample_.insert(make_pair(temp, "129"));

	temp = {"61235000000","61235999999","11",2};
	mapSample_.insert(make_pair(temp, "129"));

	temp = {"62000000000","62999999999","12",2};
	mapSample_.insert(make_pair(temp, "129"));

	temp = {"62010100000","62010199999","14",1};
	mapSample_.insert(make_pair(temp, "129"));

	temp = {"12345600000","12345699999","22", 4};
	mapSample_.insert(make_pair(temp, "128"));
	temp = {"42000000000","42999999999","24", 1};
	mapSample_.insert(make_pair(temp, "131"));

	temp = {"42000000000","42999999999","24", 3};
		mapSample_.insert(make_pair(temp, "135"));

	temp = {"12000000000", "12999999999", "28", 2};
	mapSample_.insert(make_pair(temp, "131"));


	for (auto it : mapSample_) {
		cout << endl<<"[" << it.first.start << "] , [" << it.first.end << "], [" << it.first.transactionCode <<"], [" << it.first.priority <<"], ["
				<< it.second << "]" << endl;
	}

	return 0;

	IMDSpecialKey temp1 = { "42000100000", "42000100000", "24" -1 };
	auto it = mapSample_.find(temp1);
	if (it != mapSample_.end()) {

		cout << endl << "Found for 42101000001 [" << it->first.start << ","
				<< it->first.end << "]" << endl;

	} else {
		cout << "Not found for 42101000001" << endl;
	}

	IMDSpecialKey temp2 = { "12000000001", "12000000001", "12" -1 };
	auto it2 = mapSample_.find(temp2);
	if (it2 != mapSample_.end()) {
		cout << endl << "Found for 12000000001 [" << it2->first.start << ","
				<< it2->first.end << "]" << endl;

	} else {
		cout << "Not found for 12000000001" << endl;
	}

	temp2 = {"62010100000", "62010100000", "14" -1};
	it2 = mapSample_.find(temp2);
	if (it2 != mapSample_.end()) {
		cout << endl << "Found for 62010100000 [" << it2->first.start << ","
				<< it2->first.end << "]" << endl;

	} else {
		cout << "Not found for 62010100000";
	}
	return 0;
}

