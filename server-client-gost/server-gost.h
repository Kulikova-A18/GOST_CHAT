#ifndef SERVERGOST_H
#define SERVERGOST_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include <errno.h>
#include <malloc.h>
#include <resolv.h>
#include <filesystem>

#include "openssl/ssl.h"
#include "openssl/err.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

#define FAIL    -1
#define MAXLINE 1024
#define PORT 48655

#define SIMMETRIC_KEY "mH70oa3013"

class ClassServerGost {
    public:
        // send.cpp
        std::string check_authorization(std::string login, std::string password, std::string response);
        std::string check_json_message(char *message);

        // data/check-json-data.cpp
        std::string check_data(std::string _message);
        std::string find_json(std::string _login, std::string _password);
        std::string _find(std::string argv1, std::string argv2);

        // data/create-json-data.cpp
        void create_all();

        // EVP/EVP_CIPHER_CTX.cpp
        int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
                    unsigned char *iv, unsigned char *plaintext);
        int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                    unsigned char *iv, unsigned char *ciphertext);

        // EVP/EVP_PKEY.cpp
        unsigned char *create_EVP_PKEY();
        int write_client_pubkey_EVP_PKEY(char *clientkey);
        unsigned char *read_EVP_PKEY();
        std::string send_server_EVP_PKEY();
};

#endif // SERVERGOST_H
