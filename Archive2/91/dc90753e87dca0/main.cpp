#include <iostream>
#include <stdexcept>

constexpr bool IsDigit(char c)
{
    return c >= '0' && c <= '9';
}

constexpr bool IsHexDigit(char c)
{
    return IsDigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}

constexpr bool IsHexa(const char* str)
{
    return *str == '\0' ? true :
            IsHexDigit(*str) && IsHexa(str + 1);
}

constexpr bool IsValidRgb(const char* str)
{
    return *str == '#' && IsHexa(str + 1);
}

class Color
{
private:
    const char* m_hex;
    
public:
    constexpr Color(const char* hexColor)
        : m_hex(IsValidRgb(hexColor) ? hexColor : throw new std::logic_error("Invalid hex color string"))
    {
    }
    
    const char* GetHexColor() const
    {
        return m_hex;
    }
};

static constexpr Color c("#FF00FF");

int main()
{
    std::cout << c.GetHexColor() << std::endl;
}
