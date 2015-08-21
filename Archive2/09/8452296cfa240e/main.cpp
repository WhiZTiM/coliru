#include <string.h>
#include <iostream>

typedef unsigned long long CardInstanceId;
const CardInstanceId INVALID_CARDINSTANCE_ID = -1;

        // Until client is fixed, we need to limit string version of the id to 14 characters plus \0, so 46-bits.
        // To account for current max values in M15 PS4 PROD, we would ideally have at least 27-bit for userNumber and 21-bit for cardsCreated.
        // For now we will accommodate the max cardsCreated per user and reduce the possible max for userNumber:
        // using 25-bits for userNumber and 21-bits for cardsCreated.
        inline CardInstanceId MapToClientCardInstanceId(CardInstanceId serverCardInstanceId)
        {
            if (serverCardInstanceId == 0)
            {
                return 0;
            }

            const unsigned long long userNumber   = (serverCardInstanceId & 0xFFFFFFFF00000000) >> 32;
            const unsigned long long cardsCreated = (serverCardInstanceId & 0x00000000FFFFFFFF);

            // Confirm userNumber does not overflow 25-bits
            if (userNumber > 0x1FFFFFF)
            {
                return INVALID_CARDINSTANCE_ID;
            }

            // Confirm cardsCreated does not overflow 21-bits
            if (cardsCreated > 0x1FFFFF)
            {
                return INVALID_CARDINSTANCE_ID;
            }

            return ((userNumber << 25) | cardsCreated);
        }

        inline CardInstanceId MapToServerCardInstanceId(CardInstanceId clientCardInstanceId)
        {
            if (clientCardInstanceId == 0)
            {
                return 0;
            }

            const unsigned long long userNumber   = (clientCardInstanceId & 0xFFFFFFFFFFE00000) >> 25;
            const unsigned long long cardsCreated = (clientCardInstanceId & 0x00000000001FFFFF);

            return ((userNumber << 32) | cardsCreated);
        }


int main(int argc, char *argv[])
{
    CardInstanceId bad_client_id = 1923182381228341923;
    
    std::cout << MapToClientCardInstanceId(bad_client_id) << std::endl;

    return 0;
}