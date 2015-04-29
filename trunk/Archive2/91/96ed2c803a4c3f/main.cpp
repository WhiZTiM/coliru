#include <iostream>
#include <cstdlib>
 using namespace std;
 
 // Calling function must free the returned result.
char* exec(const char* command) {
  FILE* fp;
  char* line = NULL;
  // Following initialization is equivalent to char* result = ""; and just
  // initializes result to an empty string, only it works with
  // -Werror=write-strings and is so much less clear.
  char* result = (char*) calloc(1, 1);
  size_t len = 0;

  fflush(NULL);
  fp = popen(command, "r");
  if (fp == NULL) {
    printf("Cannot execute command:\n%s\n", command);
    return NULL;
  }

  while(getline(&line, &len, fp) != -1) {
    // +1 below to allow room for null terminator.
    result = (char*) realloc(result, strlen(result) + strlen(line) + 1);
    // +1 below so we copy the final null terminator.
    strncpy(result + strlen(result), line, strlen(line) + 1);
    free(line);
    line = NULL;
  }

  fflush(fp);
  if (pclose(fp) != 0) {
    perror("Cannot close stream.\n");
  }
  return result;
}
int main()
{
    int* p1 = (int*)std::calloc(4, sizeof(int)); // allocate and zero out an array of 4 int
    int* p2 = (int*)std::calloc(1, sizeof(int[4])); // same, naming the array type directly
    int* p3 = (int*)std::calloc(4, sizeof *p3);   // same, without repeating the type name
 
    if(p2)
        for(int n=0; n<4; ++n) // print the array
            std::cout << "p2[" << n << "] == " << p2[n] << '\n';
 cout << " jebo te\n";
  
    std::free(p1);
    std::free(p2);
    std::free(p3);
}