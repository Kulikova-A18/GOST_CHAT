#ifndef SERVERGOST_H
#define SERVERGOST_H

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <errno.h>
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

#define FAIL    -1
#define MAXLINE 1024

#define SIMMETRIC_KEY "mH70oa3013"

class ClassServerGost {
    public:
        //servlet.cpp
        void servlet(SSL* ssl);
        //ssl.cpp
        int open_listener(int port);
        SSL_CTX* init_server_CTX(void);
        void load_certificates(SSL_CTX* ctx, char* CertFile, char* KeyFile);
        void show_certs(SSL* ssl);

        // send.cpp
        std::string check_authorization(std::string login, std::string password, std::string response);
        std::string check_json_message(char *message);

        // data/check-json-data.cpp
        std::string check_data(std::string _message);
        std::string find_json(std::string _login, std::string _password);
        std::string _find(std::string argv1, std::string argv2);

        // data/create-json-data.cpp
        void create_all();
};

#endif // SERVERGOST_H
