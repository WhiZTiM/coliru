#define Line(...) _asm __VA_ARGS__
#define Asm(...) _asm { __VA_ARGS__ }

Asm ( Line (mov al, bl)
      Line (out 0x80, al)
    );
