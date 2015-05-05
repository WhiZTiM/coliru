#include <iostream>
#include <string>
 
int main()
{
    char* c_time_string;
	time_t current_time;
	current_time = time(NULL);
	// Convert to local time format. /
    c_time_string = ctime(&current_time);
  // Print to stdout. /
    (void) printf("Current time is %s\n", c_time_string);
}