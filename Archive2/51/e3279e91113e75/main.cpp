
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STRING_LEN 5


void strnAlt(int c, char *argv[]){
    char saUser[MAX_STRING_LEN];
    strncpy(saUser, argv[2], MAX_STRING_LEN);
    
    if (strlen(argv[2]) > MAX_STRING_LEN) {
        //print whatever panic
    } else {
        //print whatever is normal
    }
}

int main() {
    return 0;
}