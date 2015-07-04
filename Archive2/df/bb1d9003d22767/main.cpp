#include <stdio.h> 

int main(void)
{
    enum{ MONDAY,
          TUESDAY,
          WEDNESDAY,
          THURSDAY,
          FRIDAY
          
    day_of_the_week=WEDNESDAY;
    
    switch( day_of_the_week ) {
        case MONDAY:
            printf("It is not yet Tuesday\n");
            break;
        case TUESDAY:
            printf("It is not yet Wednesday\n");
            break;
        case WEDNESDAY:
            printf("It is not yet Thursday\n");
            break;
        case THURSDAY:
            printf("It is not yet Friday\n");
            break;
        case FRIDAY:
            printf("It is not yet Saturday\n");
            
    }
}