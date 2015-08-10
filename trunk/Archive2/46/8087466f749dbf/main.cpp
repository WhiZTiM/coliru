
#include <stdio.h>

extern "C" {
    
    struct Data {
      unsigned char type;
      char filename[];
    } __attribute__((__packed__));

    
}

const struct Data data = {4,"file.txt"};
int main()
{
    printf("File: %s Size: %d",data.filename,(int) sizeof(data.filename));
}
