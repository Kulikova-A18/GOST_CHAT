#include "client-gost.h"

ClassClientGost CLIENT_GOST;

std::string login = "login";
std::string password = "password";

int main(int arvc, char *argv[])
{
    SSL_CTX *ctx;
    int server;
    SSL *ssl;
    char buf[2048];
    int bytes;
    char *hostname = (char *)"127.0.0.1", *portnum = (char *)"8081";
    char msg[2048];

    SSL_library_init();
    ctx = CLIENT_GOST.init_CTX();
    server = CLIENT_GOST.open_connection(hostname, atoi(portnum));
    ssl = SSL_new(ctx);      /* create new SSL connection state */
    //throw or return an error
    if(!ctx) { ERR_print_errors_fp(stderr); }
    SSL_set_fd(ssl, server);    /* attach the socket descriptor */
    /* perform the connection */
    if (SSL_connect(ssl) == FAIL) { ERR_print_errors_fp(stderr); }

    printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
    std::string a = CLIENT_GOST.check_authorization(login, password);
    char ac_client_request[2048] = {0};
    const char *cpRequestMessage = "%s %s";
    // construct reply
    sprintf(ac_client_request, cpRequestMessage, login.c_str(),password.c_str());


    SSL_write(ssl, (char *)ac_client_request, strlen((char *)ac_client_request));   /* encrypt & send message */
    BIO_dump_fp (stdout, (const char *)ac_client_request, strlen((char *)ac_client_request));

    bytes = SSL_read(ssl, (char *)buf, sizeof((char *)buf)-1); /* get reply & decrypt */
    BIO_dump_fp (stdout, (const char *)buf, strlen((char *)buf));

    buf[bytes] = 0;
    SSL_free(ssl);        /* release connection state */

    close(server);         /* close socket */
    SSL_CTX_free(ctx);        /* release context */
    return 0;
}
