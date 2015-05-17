

template <typename T, int SIZE = sizeof(T), int ALIGNMENT=alignof(T)>
constexpr void typeInfoError()
{
    static_assert(SIZE == 0, "Intentionally fail. See template parameters above for size and alignment info.");
}

struct SmallString1
{
    char data[4];
};

struct SmallString2
{
    union
    {
        char data[4];
        int asString;
    };
};

struct alignas(int) SmallString3
{
    char data[4];
};

  
int main()
{
    typeInfoError<SmallString1>();
    typeInfoError<SmallString2>();
    typeInfoError<SmallString3>();
}
