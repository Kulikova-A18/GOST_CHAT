#ifndef CLIENTGOST_H
#define CLIENTGOST_H

#include <iostream>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <resolv.h>

#include "openssl/ssl.h"
#include "openssl/err.h"

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <string.h>

#include <stdio.h>
#include <errno.h>
#include <resolv.h>
#include <netdb.h>

#define FAIL    -1

class ClassClientGost {
    public:
        int open_connection(const char *hostname, int port);
        SSL_CTX* init_CTX(void);

        int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
                    unsigned char *iv, unsigned char *plaintext);
        int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                    unsigned char *iv, unsigned char *ciphertext);

        int create_EVP_PKEY();
        std::string send_client_EVP_PKEY();
        int write_server_pubkey_EVP_PKEY(char *clientkey);
        unsigned char *read_EVP_PKEY();

        unsigned char *create_encrypt(unsigned char *plaintext, unsigned char private_key);
        unsigned char *create_decrypt(unsigned char *plaintext, unsigned char private_key);
};
#endif // CLIENTGOST_H
