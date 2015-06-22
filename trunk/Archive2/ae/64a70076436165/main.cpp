#include <stdio.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/bio.h>


int main(int argc, char *argv[])
{
    BIO *bio = BIO_new_fp(stdout, BIO_NOCLOSE);
    RSA* rsa = RSA_generate_key(2048, 65537, NULL, NULL);

    // public key
    unsigned char *key = NULL;
    int res = i2d_RSAPublicKey(rsa, &key);
    for (int i=0; i<res;)
    {
        BIO_printf(bio, "%02X ", key[i]);
        if (++i % 16 == 0)
            BIO_printf(bio, "\n");
    }
    BIO_printf(bio, "\n\n");
    OPENSSL_free(key);
    key = NULL;
    
    // private key
    res = i2d_RSAPrivateKey(rsa, &key);
    for (int i=0; i<res;)
    {
        BIO_printf(bio, "%02X ", key[i]);
        if (++i % 16 == 0)
            BIO_printf(bio, "\n");
    }
    BIO_printf(bio, "\n");
    OPENSSL_free(key);
    
    RSA_free(rsa);
    BIO_free_all(bio);

    return 0;
}