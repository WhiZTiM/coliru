#include <cmath>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Part {
public:
    string name() {
		return "X";
	}
};

class Operation {
public:
	const string name;

	Operation(string _name) : name(_name) {}

	void operate(Part p) {
		cout << "Operation " << name << " on part " << p.name() << endl;
	}
};

class StepManager {
	unordered_map<string, vector<string>> dependencyMap;
public:
	void add_operation(Operation operation, vector<string> prerequisites) {
		// Add your implementation here. This method is called
		// once for each type of operation during setup.
		dependencyMap.insert(make_pair(operation.name, prerequisites));
	}
	void find_operations(string operation_name, unordered_set<string> & list_of_operations)
	{
		auto op = dependencyMap.find(operation_name);

		if(op->second.empty())
		{
			list_of_operations.insert(op->first);
			return;
		}
		else
		{
			for(auto& i: op->second)
			{
				find_operations(i, list_of_operations);
			}
			list_of_operations.insert(op->first);
		}
	}

	void perform_operation(string operation_name, Part p) {
		// Add your implementation here. When this method is called,
		// you must call the 'operate()' method for the named operation,
		// as well as all prerequisites for that operation.

		unordered_set<string> list_of_operations;

		find_operations(operation_name, list_of_operations);

		for(auto& i: list_of_operations)
		{
			Operation o(i);
			o.operate(p);
		}
	}
};

int main() {
	StepManager step_mgr;

	string s;
	while (getline(cin, s)) {
		if(s.empty())
			break;
		if (s[0] == '#')
			continue;

		stringstream ss(s);
		string name, tmp;
		vector<string> prerequisites;

		getline(ss, name, ',');
		while (getline(ss, tmp, ',')) {
			prerequisites.push_back(tmp);
		}

		step_mgr.add_operation(Operation(name), prerequisites);
	}

	step_mgr.perform_operation("final", Part());
}
