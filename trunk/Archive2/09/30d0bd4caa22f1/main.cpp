#include <stdio.h>

void my_callback_2(int id, void*)
{
    // avoid warning by not naming the parameter
    printf("%d", id);
}
int main()
{

}