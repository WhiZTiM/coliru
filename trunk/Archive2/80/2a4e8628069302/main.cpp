#include <iostream>

// Please implement swap below such that it takes two strings as input and swaps their values
void swap(const char* stringA , const char* stringB )
{
    const char**temp ;
    temp = &stringB;
    stringB = stringA;
    stringA = *temp;

}

// Aside from passing values into swap(), do not modify the rest of the function
int main( int argc, char** argv )
{
  const char* stringA = "The cow jumped over the moon";
  const char* stringB = "The dish ran away with the spoon";

  std::cout << stringA << std::endl;
  std::cout << stringB << std::endl;

  swap(stringA, stringB);

  std::cout << stringA << std::endl;
  std::cout << stringB << std::endl;
}

