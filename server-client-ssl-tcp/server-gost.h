#ifndef SERVERGOST_H
#define SERVERGOST_H

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
        std::string check_authorization(std::string login, std::string password);
        void get_authorization(std::string a);
};

#endif // SERVERGOST_H
