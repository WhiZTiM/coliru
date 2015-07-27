#include <string.h>
#include <stdint.h>
#include <stdio.h>

uint32_t kfactor_linear[2][20] = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
};

void getkFactorLinearity(uint32_t linearity[2][20]){
    memcpy(linearity, kfactor_linear, sizeof(linearity)); 
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