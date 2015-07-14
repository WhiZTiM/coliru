#include <cstdio>
#include <cstring>

// Three _very_ cryptographically secure hash functions
unsigned int h1(unsigned int hash, const char* msg, unsigned int len)
{
    while(len--) hash = (hash*33) + msg[len];
	return hash;
}

unsigned int h2(unsigned int hash, const char* msg, unsigned int len)
{
	while(len--) hash = (hash*127) ^ msg[len];
	return hash;
}

unsigned int h3(unsigned int hash, const char* msg, unsigned int len)
{
	while(len--) hash ^= ((hash>>3) + (hash<<15)) * msg[len];
	return hash;
}


const unsigned int salt_for_rng = 13579;

const unsigned int salt_for_h1  = 12345;
const unsigned int salt_for_h2  = 54321;
const unsigned int salt_for_h3  = 98765;


// A random number generator
unsigned int puny_bbs_generator(unsigned int seed) { return (seed*seed) % 101273; }


unsigned int do_gen_key(const char* password, unsigned int len)
{
	unsigned int choose = h1(salt_for_rng, password, len);
	unsigned int hash   = h2(salt_for_h2,  password, len);

	for(unsigned int i = 0; i < 1000000; ++i)
	{
		// The thing here is that you can't tell in advance which algorithm to load into your FPGA (it depends on
		// the password, which just what you're trying to find out!).
		// You'll have to do this switch a million times, which is trivial for a CPU, less so for FPGAs or GPUs.
		// A somewhat better (and more stateful, more GPU-costly) generator would help, obviously.
		switch((choose = puny_bbs_generator(choose)) % 3)
		{
			case 0:
				hash     = h1(salt_for_h1,  (const char*) &hash,   sizeof(hash));
				break;
			case 1:
				hash     = h2(salt_for_h2,  (const char*) &hash,   sizeof(hash));
				break;
			case 2:
				hash     = h3(salt_for_h3,  (const char*) &hash,   sizeof(hash));
				break;
		}
	}

	return hash;
}

int main()
{
	printf("%u\n", do_gen_key("unguessable", strlen("unguessable")));
	return 0;
}
