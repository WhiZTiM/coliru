#include <cstdio>

// Please implement swap below such that it takes two strings as input and swaps their values
void swap( )
{
}

// Aside from passing values into swap(), do not modify the rest of the function
int main( int argc, char** argv )
{
  const char* stringA = "The cow jumped over the moon";
  const char* stringB = "The dish ran away with the spoon";

  printf( "%s\n", stringA );
  printf( "%s\n", stringB );

  swap();

  printf( "%s\n", stringA );
  printf( "%s\n", stringB );
}