#include <cstdlib>


unsigned char ** split_background(unsigned char background[],int size, int n_bytes) {
int i=0,j=0,cont=0;
unsigned char **r;
int rows = size / n_bytes;
r=(unsigned char **)malloc(rows*sizeof(unsigned char *));
for (i=0;i<rows;i++){
    r[i] =(unsigned char *)malloc(n_bytes*sizeof(unsigned char));
}   

for (i=0;i<rows;i++) {
    for (j=0;j<n_bytes;j++) {
        r[i][j]='20';
        cont++;

    }
}
return r;
}