#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cassert>

using namespace std;

size_t gcd(const size_t &a_value, const size_t &b_value)
{
    return (a_value < b_value) ? 
		gcd(b_value, a_value) : 
		((a_value % b_value == 0) ? 
			b_value : 
			gcd(b_value, a_value % b_value));
}

bool are_coprime (size_t a_value, size_t b_value) {
	assert(a_value > 0 && b_value > 0);
	return (a_value<b_value) ? 
		are_coprime(b_value, a_value) : 
		!(a_value % b_value) ? 
			(b_value == 1) : 
			are_coprime (b_value, a_value % b_value);
}

int main() {
	cout << "Exercise 1. Coded by p1e. The one you are looking for is A = 11, B = 4." << endl;
	
	string ciphertext = ""
		"KQEREJEBCPPCJCRKIEACUZBKRVPKRBCIBQCARBJCVFCUP"
		"KRIOFKPACUZQEPBKRXPEIIEABDKPBCPFCDCCAFIEABDKP"
		"BCPFEQPKAZBKRHAIBKAPCCIBURCCDKDCCJCIDFUIXPAFF"
		"ERBICZDFKABICBBENEFCUPJCVKABPCYDCCDPKBCOCPERK"
		"IVKSCPICBRKIJPKABI";

	
	for (size_t a_value = 1; a_value <= 26; a_value++) {
		if (!are_coprime(a_value, 26))
			continue;
		for (size_t b_value = 0; b_value <= 26; b_value++) {
			string plaintext = ciphertext;
			for (size_t index = 0; index < plaintext.size(); index++)
				plaintext[index] = (((plaintext[index] - 'A' - b_value + 26) % 26) * a_value) % 26 + 'A';
			cout << "A: " << setw(2) << a_value;
			cout << ", B: " << setw(2) << b_value;
			cout << ", P: " << plaintext << endl;
		}
	}

	return 1;
}