#include <openssl/md5.h>
#include <iostream>
#include <iomanip>

// Print the MD5 sum as hex-digits.
void print_md5_sum(unsigned char* md) {
    for(unsigned i=0; i <MD5_DIGEST_LENGTH; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(md[i]);
    }
}

#include <string>
#include <vector>
#include <fstream>

int main(int argc, char *argv[]) {
    using namespace std;
    vector<string> const args(argv+1, argv+argc);

    for (auto& fname : args) {

        char file_buffer[4096];

        MD5_CTX ctx;
        MD5_Init(&ctx); // (unsigned char*) file_buffer, file_size, result);

        ifstream ifs(fname, std::ios::binary);

        while (ifs.read(file_buffer, sizeof(file_buffer)) || ifs.gcount()) {
            MD5_Update(&ctx, file_buffer, ifs.gcount());
        }
        unsigned char digest[MD5_DIGEST_LENGTH] = {};
        MD5_Final(digest, &ctx);

        print_md5_sum(digest);
        std::cout << "\t" << fname << "\n";
    }
}
