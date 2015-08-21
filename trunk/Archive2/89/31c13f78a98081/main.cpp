#include <iostream>
#include <string>
#include <vector>

#define UT_ASSERT_NO_EXPLANATION(X) assertion_handler(X, "")
#define UT_ASSERT_EXPLAIN(X, Y) assertion_handler(X,Y)

#define GET_MACRO_UT_ASSERT(_1,_2, NAME,...) NAME
#define UT_ASSERT(...) GET_MACRO_UT_ASSERT(__VA_ARGS__, UT_ASSERT_EXPLAIN, UT_ASSERT_NO_EXPLANATION)(__VA_ARGS__)

using namespace std;

void assertion_handler(string expression, string explanation) {
     cout << "Assertion Failure: " << expression;
     if (!explanation.empty()) {
      cout << "Explanation: " << explanation;   
     }
     cout << endl;
}

int main()
{
    UT_ASSERT("a < b", "When the clock strikes 12, a should be less than b");
    
    UT_ASSERT("!point.invalid()");
}
