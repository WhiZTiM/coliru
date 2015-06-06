/*
 ============================================================================
 Name        : EugenTest.c
 Author      : Guillaume Meunier 06/06/2015
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int strLenght(const char * str){
    int len = 0;
    while(str[len++] != '\0');
    return len;
}


char * SumCharsAndDigits(const char * str){
  int localSum = 0;
  int finalSum = 0;
  int len = 0;
  int i = 0;
  int toAdd = 0;
  char * result = (char*)malloc(sizeof(char));;
  len = strLenght(str);

  for( i = 0; i < len; i++){
    if(str[i] >= '0' && str[i] <= '9')
        localSum += (int)(str[i] - '0');
    if(str[i] >= 'a' && str[i] <= 'z')
        localSum += (int)(str[i] - 'a' + 1);
    if(str[i] >= 'A' && str[i] <= 'Z')
        localSum += (int)(str[i] - 'A' + 1);
  }

  while(localSum != 0){
    toAdd = localSum%10;
    finalSum += toAdd;
    localSum /= 10;
        if(localSum == 0 && finalSum > 9)
        {
            localSum = finalSum;
            finalSum = 0;
        }
  }

  result[0] = finalSum + '0';
  return result;


}

char * getWord(const char * str, int wordNumber){
	int startW = 0;
	int stopW = 0;
	int actualWordNum = 0;
	int wordLen = 0;
	int j;
	char * res;
    while(str[startW] == ' '){
		startW++;
	}
	while(actualWordNum != wordNumber){
		if(str[startW++] == ' ' && str[startW] != ' ')
			actualWordNum++;
	}
	stopW = startW;
	while(str[stopW++] != ' ');
	wordLen = stopW - startW - 1;
	res = (char*)malloc(wordLen * sizeof(char));
	for(j=0;j<wordLen;j++){
		res[j] = str[startW+j];
	}

	return res;

}

void PrintWordsSorted(const char * str){
  int nbWords = 0;
  int i = 0;
  int j = 0;
  char ** tokens;
  while(str[i] == ' '){
    i++;
  }
  while(str[i] != '\0')
  {
    if(str[i] == ' ' && str[i+1] != ' ' && str[i+1] != '\0'){
        nbWords++;
    }
	i++;
  }
  i = 0;
  tokens = (char**)malloc(nbWords * sizeof(char*));

  for(i=0;i<nbWords+1;i++){
    tokens[i] = getWord(str,i);
  }
  for(i=0; i < 10; i++ ){
	  for(j=0; j< nbWords+1; j++){
		  if(*SumCharsAndDigits(tokens[j]) == i + '0')
			  printf("%d  - %s \n",i,tokens[j]);
	  }
  }

}

int main(void) {
  const char* str = "mon code est cool !";
  PrintWordsSorted(str);

  return EXIT_SUCCESS;

}
