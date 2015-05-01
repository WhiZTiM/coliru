#include <iostream>
#include <string>
#include <regex>
using namespace std;

int main()
{
    string words = "AllOfMyHeroes ateWeirdos.";
    cout << "String is: " << words << "\n";
    regex substr("[[:w:]]+[[:s:]]+[[:w:]]+[[:punct:]]", regex_constants::icase);
    cout << "Contains punctuation: ";
    if(regex_match(words, substr))
        cout << "true\n";
    else
        cout << "false\n";
    
    regex subst("[[:w:]]*+[[:s:]]*+[aeiou]+[[:w:]]*+[[:punct:]]", regex_constants::icase);
    cout << "Contains vowels: ";
    if(regex_match(words, subst))
        cout << "true\n";
    else
        cout << "false\n";
    
    
    regex subs("www.[[:w:]]+.com", regex_constants::icase);
    cout << "Is web address: ";
    if(regex_match(words, subs))
        cout << "true\n";
    else
        cout << "false\n";
        
    string w = "ate";
    regex sub("[[:w:]]+[[:s:]]+ate[[:w:]]+[[:punct:]]", regex_constants::icase);
    cout << "Contains ate: ";
    if(regex_match(words, sub))
        cout << "true\n";
    else
        cout << "false\n";
    
    regex su("[[:w:]]+[[:s:]]+[[:w:]]+[[:punct:]]", regex_constants::icase);
    cout << "Contains whitespace: ";
    if(regex_match(words, su))
        cout << "true\n";
    else
        cout << "false\n";
    
    return 0;
}
