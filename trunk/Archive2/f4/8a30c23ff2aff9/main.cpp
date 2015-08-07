#include <iostream>
using namespace std;

typedef unsigned short WORD;
typedef unsigned int DWORD;

union CMapFormat {
  struct {
    const WORD mapformat_major;
    const WORD mapformat_minor;
  };
  DWORD mapformat;
 
 static CMapFormat CurrentVersion();
};

#define MAP_FORMAT_VERSION 62

CMapFormat CMapFormat::CurrentVersion() {
  CMapFormat res ={ MAP_FORMAT_VERSION, 0 };
  return res;
}

int main()
{
    return 0;
}