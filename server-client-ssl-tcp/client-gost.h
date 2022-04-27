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
#include <fstream>

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
        // client_ssl.cpp
        int open_connection(const char *hostname, int port);
        SSL_CTX* init_CTX(void);

        // send.cpp
        std::string check_authorization(std::string login, std::string password);
        void get_authorization(std::string a);
};

#endif // CLIENTGOST_H
