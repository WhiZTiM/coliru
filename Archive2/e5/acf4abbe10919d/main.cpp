#include <cstdio>
#include<string.h>
#include<stdlib.h>

// Please implement swap below such that it takes two strings as input and swaps their values

void swap( const char* strA, const char* strB)

{
    char *tempA = (char *)malloc((strlen(strA) + 1) * sizeof(char));
    char *tempB = (char *)malloc((strlen(strB) + 1) * sizeof(char));
    char *temp3 = (char *)malloc(200 * sizeof(char));

  strcpy(tempA, strA);
  strcpy(tempB, strB);
  
  strcpy(temp3, tempA);
  strcpy(tempA, tempB);
  strcpy(tempB, temp3);
  
 
}


// Aside from passing values into swap(), do not modify the rest of the function

int main( int argc, char** argv )

{

  const char* stringA = "The cow jumped over the moon";

  const char* stringB = "The dish ran away with the spoon";


  printf( "%s\n", stringA );

  printf( "%s\n", stringB );


  swap(stringA, stringB);


  printf( "%s\n", stringA );

  printf( "%s\n", stringB );

}