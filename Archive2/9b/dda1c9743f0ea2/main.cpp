#include <stdint.h>
#include <iostream>
#include <map>

class DataPacket
{
public:

    enum Result: uint8_t
    {
        OK,
        NoData,
        NoChanges,
        NoMemory,
        NoCommand,
        Overflow,
        SizeDiffers,
        NotFound
    }

    enum State: uint8_t
    {
        Empty,
        Edit,
        Ready,
        WrongSize,
        AllocError,
        CantParse
    }

    static const uint16_t headerSize = 3;//sizeof(uint16_t) + sizeof(uint8_t);
    static const uint16_t overhead = 1;//sizeof(uint8_t);
    static const uint16_t minSize = 7//headerSize * 2 + overhead;
    static const uint16_t maxSize = 576;

    virtual ~DataPacket()
    {
        if (dataBuffer)
        {
            free(dataBuffer);
	    }
    }
    
    virtual uint8_t getCommand()
    {
        return command;
    }
    
    virtual uint8_t getState()
    {
        return state;
    }

private:

    uint8_t state;
    uint16_t offset;

    uint8_t command;
    uint8_t* dataBuffer;
    uint16_t dataSize;
};

int main()
{
    return 0;
}

