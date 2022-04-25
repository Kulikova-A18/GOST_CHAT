#include "server-gost.h"

// openssl s_client -showcerts -connect 127.0.0.1:8081

// path to cert end private key
char *CERT_PATH = "/etc/ssl/certs/server_gost_ca.pem";
char *KEY_PATH = "/etc/ssl/private/server_gost_privateKey.pem";

ClassServerGost SERVER_GOST;

int is_root() {
    if (getuid() != 0) { return 0; }
    else { return 1; }
}

int main(int arvc, char *argv[])
{   SSL_CTX *ctx;
    int server;
    char *PORT_NUM = (char *)"8081";

    SERVER_GOST.create_EVP_PKEY(); // create public and private evp pkey

    if(!is_root()) {
        printf("This program must be run as root/sudo user!!");
        exit(0);
    }

    SSL_library_init();

    ctx = SERVER_GOST.init_server_CTX();                        //initialize SSL
    SERVER_GOST.load_certificates(ctx, CERT_PATH, KEY_PATH);    //load certs
    server = SERVER_GOST.open_listener(atoi(PORT_NUM));         //create server socket
       struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;

        int err;

        int client = accept(server, (struct sockaddr*)&addr, &len);  //accept connection as usual
        printf("Connection: %s:%d\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        ssl = SSL_new(ctx);             //get new SSL state with context
        SSL_set_fd(ssl, client);        //set connection socket to SSL state
        SERVER_GOST.servlet(ssl);       //service connection

    close(server);              //close server socket
    SSL_CTX_free(ctx);          //release context
}
