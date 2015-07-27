#include <string.h>
#include <stdint.h>
#include <stdio.h>

uint32_t kfactor_linear[2][20] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
    {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1},
};

void getkFactorLinearity(uint32_t linearity[2][20]){
    for(uint32_t i = 0; i < 2; i++) {
        memcpy(linearity[i], kfactor_linear[i], sizeof(linearity[i])); 
    }
}

int main(void)
{
    uint32_t thing[2][20];
    getkFactorLinearity(thing);
    for (uint32_t i = 0; i < 2; i++) {
        for (uint32_t j = 0; j < 20; j++) {
            printf("%d ", thing[i][j]);
        }
        printf("\n");
    }
}