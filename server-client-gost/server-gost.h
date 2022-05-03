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
#include <fstream>
#include <ctime>
#include <time.h>

#include "openssl/ssl.h"
#include "openssl/err.h"
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

#define FAIL    -1
#define MAXLINE 1024
#define PORT 48655

#define SIMMETRIC_KEY "mH70oa3013"

using namespace std;

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

class ClassServerGostLog {
    public:
        std::string string_void;
        std::string string_message;
        std::string file_name = "server-gost-chat.log";

        void logger() {
            time_t     now = time(0);
            struct tm  tstruct;
            char       buf[80];
            tstruct = *localtime(&now);
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

            ofstream o(file_name,ios::ate|ios::out|ios::app);
            o << buf << " " << string_void << " " << string_message << std::endl;
            o.close();

            if(string_void == "ClassServerGost::decrypt()" || string_void == "ClassServerGost::encrypt()"
                    || string_void == "ClassServerGost::find_json()")
            {
                printf("\n========== ATTENTION ==========\n");
                printf("%s %s/%s\n", buf, string_void.c_str(), string_message.c_str());
                printf("=================================\n\n");
            }
        }
};

#endif // SERVERGOST_H
