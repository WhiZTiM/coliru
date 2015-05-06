    #include <string.h>
    
    class Header
    {
    public:
    
    };
    
    struct structType {
      int a;
      int b;
      float d;
      char c[1500];
    };
    
    class CanData : public Header
    {
    public:
      CanData() {
        type.a = 22;
        type.b = 33;
        type.d = 3.0f;
        memset(&type.c, 0x90, 1500);
      }
      structType type;
    };
    
    int main() {
      Header *pt = new CanData();
      delete pt;
    }