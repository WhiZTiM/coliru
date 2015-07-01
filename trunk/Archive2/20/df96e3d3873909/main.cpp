#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std; // Don't do this at work

bool anyPalindromeAnagramExists(string& str) {

  // The following horribly sucks but it's meant for plain ASCII. Accepting suggestions.
  vector<int> chars(1 << numeric_limits<unsigned char>::digits, 0);
  for (char c : str) {
    ++chars[c];
  }

  // If there's NO odd series of characters or if there's just ONE
  // odd series of characters (one could go in the middle), a palindrome can be obtained
  bool oddFound = false;
  bool noPalindromePossible = false;
  for (int i : chars) {
    if (i % 2 != 0) {
      if (oddFound == false) {
        oddFound = true;
      }
      else {
        noPalindromePossible = true;
        break;
      }
    }
  }

  return !noPalindromePossible;
}

int main() {

  string str = "aabbabc";

  cout << anyPalindromeAnagramExists(str) << endl;

  str = "abaab";

  cout << anyPalindromeAnagramExists(str) << endl;
}