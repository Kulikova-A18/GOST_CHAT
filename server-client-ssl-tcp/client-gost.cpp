#include "client-gost.h"

ClassClientGost CLIENT_GOST;

std::string login = "kulikova@gost_chat.com";
std::string password = "7777777777";

int main(int arvc, char *argv[])
{
    std::cout << "=============== data ===============" << std::endl;
    std::cout << "login: " << login << std::endl;
    std::cout << "password: " << password << std::endl;
    std::cout << "====================================" << std::endl << std::endl;

    SSL_CTX *ctx;
    int server;
    SSL *ssl;
    char buf[1024];
    int bytes;
    char *hostname = (char *)"127.0.0.1", *portnum = (char *)"48655";
    char msg[1024];

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
    char ac_client_request[1024] = {0};
    const char *cpRequestMessage = "%s";
    sprintf(ac_client_request, cpRequestMessage, a.c_str());

    printf("send message\n");
    SSL_write(ssl, ac_client_request, strlen(ac_client_request));   /* encrypt & send message */
    BIO_dump_fp (stdout, ac_client_request, strlen(ac_client_request));

    printf("get message\n");
    bytes = SSL_read(ssl, buf, sizeof(buf)-1); /* get reply & decrypt */
    BIO_dump_fp (stdout, buf, strlen(buf));

    buf[bytes] = '\0';
    SSL_free(ssl);        /* release connection state */

    close(server);         /* close socket */
    SSL_CTX_free(ctx);        /* release context */
    return 0;
}
