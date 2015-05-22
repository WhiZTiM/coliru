#include <stdio.h>

int main(void) {
  
   int score = 95;
   
   switch (score/10 ) {
    case 10:
    case 9:
      printf(" Have an A %d \n", score);
      break;
    case 8:
      printf(" Have an B %d \n", score);
      break;
    case 7:
      printf(" Have an C %d \n", score);
    case 6:
      printf(" Have an D %d \n", score);
      break;
    default:
      printf(" Have an F %d \n", score);
      break;  
   
  }
   return 0;
}

