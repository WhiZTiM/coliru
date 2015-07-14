#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef enum ErrorCode_e
{
    NO_ERROR,
    GENERAL_ERROR,
    UNINITIALIZED_DATA_ACCESS,
    ALLOCATION_ERROR,
    READ_WRITE_ERROR,
    NO_FILESTREAM
} ErrorCode_t;

int main()
{
    ErrorCode_e a = NO_ERROR;
    ErrorCode_t b = NO_ERROR;
}