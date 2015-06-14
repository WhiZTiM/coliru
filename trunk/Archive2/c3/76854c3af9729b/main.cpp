#include <iostream>
using namespace std;

int main(){
    size_t t;
	if (cin>>t) while(t--) {
        size_t n;
        char ch;
    
        static char const* label[] = { "NOT SURE", "INDIAN", "NOT INDIAN" };
        enum                         { not_sure,   indian,   not_indian   } verdict = not_sure;

        if (cin>>n) while(n-- && cin >> ch)
            switch(ch) {
                case 'Y': if (!verdict) verdict = not_indian; break;
                case 'I': if (!verdict) verdict = indian;     break;
            }

		cout << label[verdict] << endl;
	}
}
