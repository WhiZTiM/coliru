#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    std::string delimiters = "<= ,.+=";
	std::string line = "this<=is,a.string=testing one";
	std::string line_copy(line);

	auto pos = find_first_of(begin(line_copy), end(line_copy), begin(delimiters), end(delimiters));

	while (pos != line_copy.end()) {
		if (pos != line_copy.end()) {
			if (*pos == '<' && *(pos + 1) == '=') {
				cout << "delimiter: \'";
				cout << string(pos, pos + 2) << "\'" << endl;

				// remove the delimiters from copy string
				line_copy.erase(pos, pos + 2);
			}
			else {
				cout << "delimiter: \'" << *pos << "\'" << endl;

				// remove the delimiters from copy string
				line_copy.erase(pos, pos + 1);
			}
		}
		cout << endl;

		pos = find_first_of(begin(line_copy), end(line_copy), begin(delimiters), end(delimiters));
	}
}