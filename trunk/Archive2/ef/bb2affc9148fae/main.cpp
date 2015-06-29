

uint32_t OnesComplementSum(const uint8_t * data, int length, uint32_t sum = 0)
{
    const uint16_t * data = reinterpret_cast<const uint16_t *>(data); // UB, but target CPU explicitly allows this. (and we may assume data is aligned)
    while ((length -= 32) >= 0)
    {
        sum += data[0];
        sum += data[1];
        sum += data[2];
        sum += data[3];
        sum += data[4];
        sum += data[5];
        sum += data[6];
        sum += data[7];
        sum += data[8];
        sum += data[9];
        sum += data[10];
        sum += data[11];
        sum += data[12];
        sum += data[13];
        sum += data[14];
        sum += data[15];
        data += 16;
    }

    length += 32;

    while ((length -= 8) >= 0)
    {
        sum += data[0];
        sum += data[1];
        sum += data[2];
        sum += data[3];
        data += 4;
    }

    length += 8;


    Reduce(sum);


    while ((length -= 2) >= 0)
    {
        sum += *data++;
    }

    if (length == -1)
    {
        // --- Add the last byte
        sum += static_cast<uint16_t>(*(reinterpret_cast<const uint8_t *>(data)));
    }

    Reduce(sum);

    return sum;
}
