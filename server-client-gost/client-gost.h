#ifndef CLIENTGOST_H
#define CLIENTGOST_H

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
#include <malloc.h>
#include <resolv.h>
#include <errno.h>

#include "openssl/ssl.h"
#include "openssl/err.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

#define FAIL    -1
#define MAXLINE 1024
#define PORT 48655

using namespace std;

class ClassClientGost {
    public:
        // client_ssl.cpp
        int open_connection(const char *hostname, int port);
        SSL_CTX* init_CTX(void);

        // send.cpp
        std::string check_authorization(std::string login, std::string password);
        void get_authorization(std::string a);

        // EVP/client_EVP_CIPHER_CTX.cpp
        int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
                    unsigned char *iv, unsigned char *plaintext);
        int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                    unsigned char *iv, unsigned char *ciphertext);

        unsigned char *create_encrypt(unsigned char *plaintext, unsigned char *private_key);
        unsigned char *create_decrypt(unsigned char *plaintext, unsigned char *private_key);

        // EVP/client_EVP_PKEY.cpp
        int create_EVP_PKEY();
        std::string send_client_EVP_PKEY();
        int write_server_pubkey_EVP_PKEY(char *clientkey);
        unsigned char *read_EVP_PKEY();
};

class ClassClientGostLog {
    public:
        std::string string_void;
        std::string string_message;
        std::string file_name = "gost-chat.log";

        void logger() {
            time_t     now = time(0);
            struct tm  tstruct;
            char       buf[80];
            tstruct = *localtime(&now);
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

            ofstream o(file_name,ios::ate|ios::out|ios::app);
            o << buf << " " << string_void << " " << string_message << std::endl;
            o.close();

            // print from terminal
            //printf("%s %s/%s\n", buf, string_void.c_str(), string_message.c_str());
        }
};

#endif // CLIENTGOST_H
