#include <stdio.h>
#include <string.h>
char* find(char name[], char allNames[][10], int length)
{
    int i=0;
    for (i = 0; i < length; i++) {
        if (strcmp(allNames[i],name)) {
            printf("%i",i);
            return name;
        }
    }
    return NULL;
}

int main(){
  char allNames[][10] = {"cat","dog","frog","log","bog"};
  char name[] = "log";
  int length=5;
  printf("%s",find(name,allNames,length));

}