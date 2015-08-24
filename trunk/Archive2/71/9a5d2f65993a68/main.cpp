#include <stdio.h>
#include <malloc.h>
 
 
typedef struct Trainee
{
    //char Name[20];
    int *Age;
} Trainee;
 
void func(Trainee);
 
int main()
 
{
 
    Trainee Vania;
    Vania.Age = (int*)malloc(sizeof(int));
    *Vania.Age = 12;
    
    printf("\nVania = %p\n\n",&Vania);
    printf("\n%p\n",&Vania.Age);
    printf("\n%p\n",Vania.Age);
    printf("\n%d\n",*Vania.Age);
    
    Trainee Katya;
    Katya.Age = (int*)malloc(sizeof(int));
    *Katya.Age = 22;
    
    printf("\nKatya = %p\n\n",&Katya);
    printf("\n%p\n",&Katya.Age);
    printf("\n%p\n",Katya.Age);
    printf("\n%d\n",*Katya.Age);
 
    Vania = Katya;
 
    printf("\n%p\n",&Vania.Age);
    printf("\n%p\n",Vania.Age);
    printf("\n%d\n",*Vania.Age);
 
    printf("\n*********************************\n");
    func(Vania);
    free(Vania.Age);
    free(Katya.Age);
    return 0;
}
 
void func(Trainee Vania)
 
{
    printf("\nVania = %p\n\n",&Vania);
    printf("\n%p\n",&Vania.Age);
    printf("\n%p\n",Vania.Age);
    printf("\n%d\n",*Vania.Age);
}