#include <windows.h>

int main()
{
    char hardware_info[1000];
    DWORD dwGPU = 0;
    DWORD dwCPU = 0;
    wsprintf(hardware_info, "%ul+%ul", dwGPU, dwCPU);
}