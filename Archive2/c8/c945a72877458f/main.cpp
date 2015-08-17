#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;

int main(int argc, char **argv) {
    std::vector<int> arr = { 49, 51, 52, 50 };

	std::ofstream fd("foo.txt", std::ios::binary | std::ios::out);

	std::ostream_iterator<char> oi(fd);
	std::copy(arr.begin(), arr.end(), oi);
	fd.close();

	ifstream file_read_wrong("foo.txt", std::ios::binary);
	vector<int> output_wrong(arr.size());

	for (unsigned int i = 0U; i < output_wrong.size() && file_read_wrong; ++i) {
		file_read_wrong.read(reinterpret_cast<char*>(&output_wrong[i]), sizeof(decltype(output_wrong)::value_type));
	}

	for (unsigned int i = 0U; i < output_wrong.size(); ++i) {
		cout << "wrong value " << i + 1 << ": " << output_wrong[i] << endl;
	}

    std::ofstream fp("bar.txt", std::ios::binary);

	for_each(arr.cbegin(), arr.cend(), [&](auto i) { fp.write(reinterpret_cast<char*>(&i), sizeof(decltype(i))); });
	fp.close();

	ifstream file_read_right("bar.txt", std::ios::binary);
	vector<int> output_right(arr.size(), 0);

	for (unsigned int i = 0U; i < output_right.size() && file_read_right; ++i) {
		file_read_right.read(reinterpret_cast<char*>(&output_right[i]), sizeof(decltype(output_right)::value_type));
	}

	for (unsigned int i = 0U; i < output_right.size(); ++i) {
		cout << "right value " << i + 1 << ": " << output_right[i] << endl;
	}

	return 0;
}