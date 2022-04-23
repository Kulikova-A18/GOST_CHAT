#include "server-gost.h"

ClassServerGost SERVER_GOST_SERVLET;

void ClassServerGost::servlet(SSL* ssl) {
    char buf[1024];
    char reply[1024];
    int sd, bytes;
    const char* HTMLecho= "%s";

    /* do SSL-protocol accept */
    if (SSL_accept(ssl) == FAIL) { ERR_print_errors_fp(stderr); }
    else {
        /* get any certificates */
        SERVER_GOST_SERVLET.show_certs(ssl);
        while(1)
        {
            bytes = SSL_read(ssl, buf, sizeof(buf)); // get request
            if (bytes > 0)
            {
                buf[bytes] = 0;
                printf("Client msg:%s", buf);

                strcpy(reply,buf);
                SSL_write(ssl, reply, strlen(reply));
            }
            else
                ERR_print_errors_fp(stderr);
            }
        }
    sd = SSL_get_fd(ssl);   //get socket connection
    SSL_free(ssl);          //release SSL state
    close(sd);              //close connection
}
