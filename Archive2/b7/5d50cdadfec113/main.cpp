#include <cstring>

#include <iostream>

 

char buf[256];

size_t idx = 0;

 

void *malloc(size_t size) {

  void* res = &buf[idx];

  memset(res, 0xFF, size);

  return res;

}

 

void free(void* ptr) {

  (void)ptr;

}

 

int main()

{

  {

    int* i = new int;

    std::cout << *i << std::endl;

  }

 

  {

    int* i = new int();

    std::cout << *i << std::endl;

  }

}
