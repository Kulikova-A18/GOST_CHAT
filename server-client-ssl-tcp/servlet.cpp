#include "server-gost.h"

ClassServerGost SERVER_GOST_SERVLET;

void ClassServerGost::servlet(SSL* ssl) {
    char buf[MAXLINE] = {0};
    char reply[MAXLINE] = {0};
    int sd, bytes;
    const char* HTMLecho= "%s";

    /* do SSL-protocol accept */
    if (SSL_accept(ssl) == FAIL) {
        ERR_print_errors_fp(stderr);
        exit(0);
    }
    /* get any certificates */
    SERVER_GOST_SERVLET.show_certs(ssl);

    bytes = SSL_read(ssl, buf, sizeof(buf)); // get request
    buf[bytes] = '\0';

    printf("get message\n");
    BIO_dump_fp (stdout, (const char *)buf, strlen((char *)buf));

    if (bytes > 0)
    {
       char ac_client_request[1024] = {0};
       const char *cpRequestMessage = "%s";
       sprintf(ac_client_request, cpRequestMessage, SERVER_GOST_SERVLET.check_json_message(buf).c_str());
       strcpy(reply,(char *)ac_client_request);

        printf("send message\n");
        SSL_write(ssl, (char *)reply, strlen((char *)reply));
        BIO_dump_fp (stdout, (const char *)reply, strlen((char *)reply));
    }
    else { ERR_print_errors_fp(stderr); }

    sd = SSL_get_fd(ssl);   //get socket connection
    SSL_free(ssl);          //release SSL state
    close(sd);              //close connection
}
