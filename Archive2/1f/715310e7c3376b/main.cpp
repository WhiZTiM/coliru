
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <errno.h>
#include <cstdlib>
#include <string.h>

#define PACKED( __Declaration__ ) __Declaration__ __attribute__((__packed__))

using namespace std;

PACKED(typedef struct test {
    uint8_t cmd;
	uint16_t nvItem;
	uint8_t data[128];
}) test_t;

const char hex_trans[] =
    "................................ !\"#$%&'()*+,-./0123456789"
    ":;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklm"
    "nopqrstuvwxyz{|}~...................................."
    "....................................................."
    "........................................";

void hexdump(unsigned char *data, unsigned int amount) {
	unsigned int    dp, p;  /* data pointer */
	for (dp = 1; dp <= amount; dp++) {
		fprintf(stderr, "%02x ", data[dp - 1]);
		if ((dp % 8) == 0)
			fprintf(stderr, " ");
		if ((dp % 16) == 0) {
			fprintf(stderr, "| ");
			p = dp;
			for (dp -= 16; dp < p; dp++)
                fprintf(stderr, "%c", hex_trans[data[dp]]);
			fflush(stderr);
			fprintf(stderr, "\n");
		}
		fflush(stderr);
	}
	// tail
	if ((amount % 16) != 0) {
		p = dp = 16 - (amount % 16);
		for (dp = p; dp > 0; dp--) {
			fprintf(stderr, "   ");
			if (((dp % 8) == 0) && (p != 8))
				fprintf(stderr, " ");
			fflush(stderr);
		}
		fprintf(stderr, " | ");
		for (dp = (amount - (16 - p)); dp < amount; dp++)
            fprintf(stderr, "%c", hex_trans[data[dp]]);
		fflush(stderr);
	}
	fprintf(stderr, "\n");

	return;
}

int main()
{
	long conv = std::stoul("A1000023F46F56", nullptr, 16);

	test_t t;
	
	memset(&t, 0x00, sizeof(t));
	
    t.cmd = 0x44;
    
    memcpy(&t.data, &conv, sizeof(conv));

	hexdump((uint8_t*)&t, sizeof(t));

	return 0;
}

