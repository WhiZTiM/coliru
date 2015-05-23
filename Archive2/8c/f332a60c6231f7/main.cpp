/* 
    Print Mario Half-Pyramid, where the bottom-left corner of the half pyramid is aligned 
with the left-hand edge of the terminal window. The program must ask a user for the height 
number between 1 and 23, and prompt a user to re-type the input if it is invalid
*/

#include <stdio.h>
//#include <cs50.h>
int main(void)
{
    //  declare variables for printing a pyramid
    char hashtag = 35;
    char space = 32;
    int number = 10;     
   
    //  get a number from a user between 1 and 23    
    do 
    {
        printf("Type a number between 1 and 23: %d\n", number );
    }
    while (number < 1 || number > 23);
    
    // Pyramid printing sequence
    for (int row = 0; row < number; row++)
    {
        int column = 0;
        // print spaces in a row starting with the height number - 1, and then decrement
        // not sure how and where to state this printing pattern
        for (; column < row; column++)
        {
            printf("%c", (char)space);                     
        }

        //print hashtags in a row starting with 2 hashtags, and incrementing +1
       // not sure how and where to insert this printing pattern
        for (; column < number; column++)
        {
            printf("%c", (char)hashtag);
        }
        printf("\n"); 
    }
    return 0;
}
