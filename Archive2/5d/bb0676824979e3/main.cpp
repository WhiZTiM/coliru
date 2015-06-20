#include<stdio.h>
void main(int argc, char *argv[])
{
    int pid;
    pid=fork();
    if(pid<0){fprint(stderr, "ciao");exit(-1)}
    else if(pid==0){execlp("/bin/ls","ls", NULL);}
    else{ wiat(NULL);
    printf("HELLO"); exit(0);}
}