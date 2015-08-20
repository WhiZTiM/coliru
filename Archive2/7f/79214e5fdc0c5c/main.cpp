#include<stdio.h>
 #include <unistd.h>
 #include <stdlib.h>
 #include <sys/wait.h>

 using namespace std;

 int main(){

      int cpid=fork();

         if(cpid==0){

                printf("%d %d\n",getpid(),getppid());

         }  

         else{

                printf("hello");
                wait(NULL);

         }   

 }