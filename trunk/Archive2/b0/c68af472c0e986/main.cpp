
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING_LEN 5


void hasOverflowed(char u[]){
    if(strlen(u) > MAX_STRING_LEN){
      printf("Buffer Overflow DETECTED\n");
    }else{
      printf("No buffer overflow\n");
    }
}

void originalCode(int c, char *argv[]){
    char oUser[MAX_STRING_LEN];
    printf("user before allocation %s ", oUser);
    printf("Original code ");
   
    //strcpy(oUser,argv[2]);
    //printf("user is: %s\n", user);
    hasOverflowed(oUser);
}

void strnAlt(int c, char *argv[]){
    char saUser[MAX_STRING_LEN];
    printf("user before allocation %s\n\n", saUser);
    printf("strncpy alternate ");

    strncpy(saUser, argv[2], MAX_STRING_LEN);
    //printf("user is: %s\n", user);
    hasOverflowed(saUser);
}

void checksAlt(int c, char *argv[]){
   char caUser[MAX_STRING_LEN];
   printf("user before allocation %s", caUser);
   printf("Checks alternate ");
   if(strlen(argv[2]) > (sizeof(caUser)-1)){
      fprintf(stderr, "%s: username too long (>%lu)\n", argv[2], (unsigned long) (sizeof(caUser) -1));
      
   }else{
     strcpy(caUser, argv[2]);
     //printf("user is: %s\n", user);
   }

   hasOverflowed(caUser);
   printf("user %s", caUser);
}


int main(int argc, char *argv[]) {
    originalCode(argc, argv);
    strnAlt(argc, argv);
    //checksAlt(argc, argv);

    return 0;
}