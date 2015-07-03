#include <iostream>
#include <functional>

typedef short (* PTPIOWriteFunc)(unsigned char *bytes, unsigned int size,
    			 void *data);

struct _PTPParams {
    PTPIOWriteFunc write_func;
};

typedef struct _PTPParams PTPParams;

class Device {
public:
int a = 5;
std::function<short(unsigned char *, unsigned int, void *)> _ptpIOWrite =
      [](unsigned char *bytes, unsigned int size, void *data) -> short {
        std::cout << "Ptp Writing, a = " << "\n";
        short b = 15;
        return b;
      };
};

int main() {
    PTPParams params;
    Device device;
    //params.write_func = device._ptpIOWrite.target<short(unsigned char*, unsigned int, void*)>();
    
    std::cout << "converting\n";
    
    auto func = device._ptpIOWrite.target<short(unsigned char*, unsigned int, void*)>();
    if(func == nullptr){
        std::cout << "NULLPTR\n";
    }
    params.write_func = *func;
    
    unsigned char uc = 1;
    unsigned int ui = 512;
    void * p = nullptr;
    
    std::cout << "Type: " << _global.target_type().name() << "\n";
    std::cout << "write_func = " << params.write_func(&uc, ui, p);
}