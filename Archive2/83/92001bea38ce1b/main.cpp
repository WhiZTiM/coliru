#include <unistd.h>
#include <sys/types.h> 
#include <stdio.h>
#include <stdlib.h>

 

void print_exit()
{
       printf("the exit pid:%d\n",getpid() );
}

int main () 
{ 
   pid_t pid; 
   atexit( print_exit );      //注册该进程退出时的回调函数
      pid=fork(); 
        if (pid < 0) 
                printf("error in fork!"); 
        else if (pid == 0) 
                printf("i am the child process, my process id is %d\n",getpid()); 
        else 
        {
               printf("i am the parent process, my process id is %d\n",getpid()); 
              sleep(2);
              wait();
       }

}
