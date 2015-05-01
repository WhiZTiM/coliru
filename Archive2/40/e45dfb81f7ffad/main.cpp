#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main()
{
   string word = "Hello atepizza!";
   cout << "The string is: " << word << "\n";
   regex substr("[[:w:]]+[[:s:]]+[[:w:]]+[[:punct:]]", regex_constants::icase);
   if(regex_match(word, substr)) {
       cout << "There is punctuation\n";
   }
   else {
       cout << "There is NO punctuation\n";
   }
   
   regex n("[[:w:]]*+[[:s:]]*+[aeiou]+[[:w:]]*+[[:punct:]]", regex_constants::icase);
   if(regex_match(word, n)) {
       cout << "There is a vowel!\n";
   }
   else
   {
       cout << "There is no vowel!\n";
   }
   
   regex sub("www.[[:w:]] +.com", regex_constants::icase);
   if(regex_match(word, sub)) {
       cout << "It is a web address!\n";
   }
   else
   {
       cout << "It is not a web address!\n";
   }
   
   regex s("[[:w:]]+[[:s:]]+ate[[:w:]]+[[:punct:]]", regex_constants::icase);
   if(regex_match(word, s)) {
      cout << "The word ate is contained\n";
   }
   else
   {
       cout << "The word ate is not contained\n";
   }
   
   regex sa("[[:w:]]+[[:s:]]+[[:w:]]+[[:punct:]]", regex_constants::icase);\
   if(regex_match(word, sa)) {
       cout << "There is a space!\n";
   }
   else
   {
       cout << "There is no space!\n";
   }
   
   return 0;
   
   
}
