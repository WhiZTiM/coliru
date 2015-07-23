#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define DATA "Bright star, would I were steadfast as thou art...\n"
#define DATA1 "blabasdsasas\n"
/*
 *  This program creates a pipe, then forks.
 *  The child communicates to the parent over the pipe.
 *  Notice that a pipe is a one-way communications
 *  device. I can write to the output socket  
 *  (sockets[1], the second socket of the array returned 
 *  by  pipe()) and  read from the input socket (sockets[0]), 
 *  but not vice versa.
 */

main()
{
    int sockets[2], child,a;

    /* Create a pipe */
    if (pipe(sockets) < 0) {
        perror("opening stream socket pair");
        exit(10);
    }

    if ((child = fork()) == -1)
        perror("fork");
    else if (child) {
        char buf[1024];

        /*  This is still the parent.
            It reads the child's message. */
        close(sockets[1]);
        if (read(sockets[0], buf, sizeof(buf)) < 0)
            perror("reading message");
        printf("-->%s\n", buf);
        if (read(sockets[0], buf, sizeof(buf)) < 0)
        printf("-->%s\n", buf);
        close(sockets[0]);
    } else {
        /* This is the child.
           It writes a message to its parent. */
        close(sockets[0]);
        if (write(sockets[1], DATA1, sizeof(DATA1)) < 0)
            perror("writing message");
        if (write(sockets[1], DATA1, sizeof(DATA1)) < 0)
            perror("writing message");
//            printf("fffff %i\n",a);
        close(sockets[1]);
    }
}