#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    std::string cmd ;
    while( std::cout << "Shell$ " && std::getline( std::cin, cmd ) && cmd != "exit" )
    {
        if( pid_t pid = fork() ) 
        {
            if( pid == -1 ) std::cerr << "fork failed\n" ;
            else
            {
                int status ; 
                wait( &status ) ; 
                std::cout << "***status: " << status << '\n' ;
            }
        }
        
        else 
        {
            std::cout << cmd << '\n' << std::flush ;
            
            // "If the -c option is present, then commands are read from string" - bash man page
            if( execlp( "/bin/bash", "/bin/bash", "-c", cmd.c_str(), (char*)nullptr ) == -1 ) 
                std::cerr << "exec failed\n" ;
        }
    }
}