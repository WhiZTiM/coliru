#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    vector<int> input = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	ofstream file_writen("temp.txt");

	for (unsigned int i = 0U; i < input.size(); ++i) {
		file_writen << input[i] << ' ';
	}
	file_writen.close();

	ifstream file_read1("temp.txt");
	ifstream file_read2("temp.txt");
	vector<int> output1(input.size());
	vector<int> output2(input.size());

	for (unsigned int i = 0U; i < input.size(); ++i) {
		file_read1 >> output1[i];
		file_read2 >> output2[i];
	}

	for (unsigned int i = 0U; i < input.size(); ++i) {
		cout << "ifstream1 value " << i + 1 << ": " << output1[i] << endl;
		cout << "ifstream2 value " << i + 1 << ": " << output2[i] << endl;
	}

	return 0;
}