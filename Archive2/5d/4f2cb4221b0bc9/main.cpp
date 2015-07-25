#include <iostream>
#include <bitset>

struct __attribute__ ((packed)) BMPHeader
{
    // BMP header
    uint16_t magic;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t dataOffset;

    // DIB header
    uint32_t dibHeaderLength;
    uint32_t width;
    uint32_t height;
    uint16_t numColourPlanes;
    uint16_t bitsPerPixels;
    uint32_t biBitFields;
    uint32_t dataSize;
    uint32_t physicalWidth;
    uint32_t physicalHeight;
    uint32_t numPaletteColours;
    uint32_t numImportantColours;
};

int main()
{
    std::cout << sizeof(BMPHeader) << '\n';
}
