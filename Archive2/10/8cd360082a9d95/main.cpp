#include <iostream>
#include <string>


/*Implement derived class for checking if cash is 
sufficient to purchase the product requested*/

class information {};

class cash:public information
{
    public:
    cash(){}

/*Function to display the appropriate 
action onscreen according to user entered amount.*/ 

void check_cash(int product_num);

};


int main()

{   char key = 'p';
    while(key=='y'||key=='Y');

    //If user enters a yes answer, main will be called again

    return 0;
}