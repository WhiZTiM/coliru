#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
using namespace std;

int main() {
    ifstream file("words.txt");
	vector<string> words(istream_iterator<string>(file), istream_iterator<string>());
	cout << words.size();
}