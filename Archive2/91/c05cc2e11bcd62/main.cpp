#include <chrono>
#include <future>
#include <iostream>
#include <vector>

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;

vector<int> build()
{
    // extremly slow build
	vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	this_thread::sleep_for(3s);

	return v;
}

int main() {
	auto future = async(launch::async, build);

	cout << "le chargement a commencé, j'attends une seconde avant de demander le résultat\n";
	this_thread::sleep_for(1s);

	cout << "Je demande le résultat maintenant\n";
	auto before = high_resolution_clock::now();
	vector<int> result = future.get();
	auto now = high_resolution_clock::now();

	cout << "Résultat obtenu après : " << duration_cast<milliseconds>(now - before).count() << "ms\n";	
	
	return 0;
}