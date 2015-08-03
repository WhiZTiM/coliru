#include <iostream>
#include <string>
#include <vector>

/*
Given a string like abcdef, rotate or shift the string n
characters where n < the length of the string without allocating a newt
string. Do it in-place. Hint: use multiple swapping
*/
//"abcdefg" ==> "cdefgab"
std::string & rotateString(std::string & str, int n)
{
    int len = str.length();
	for (int i = 0; i < n; i++)
	{
		char ch = str[0];
		for (int j = 0; j < len - 1; j++) 
		{
			str[j]=str[j+1];
		}
		str[len - 1] = ch; 
        std::cout << str <<std::endl;
	}
	return str;
}

//"abcdefg" ==> "gfedcba" ==> "cdefgab"
std::string & rotateString2(std::string & str, int n)
{
    int len = str.length();
    char ch;
    int k;
    
	for (int j = 0; j < len/2; j++) 
	{
        k = len - 1 - j;
        
        ch = str[j];
        str[j] = str[k];
		str[k] = ch;
	}
    
    for (int j = 0; j < (len - n)/2; j++)
    {
        k = len - n - 1 - j;
        
        ch = str[j];
        str[j] = str[k];
    	str[k] = ch;
    }

	return str;
}

int main()
{

    std::string mystr = std::string("abcdefgh");
    
    std::cout << mystr <<std::endl; 
    std::cout << "==>" << rotateString2(mystr, 2) <<std::endl;
}
