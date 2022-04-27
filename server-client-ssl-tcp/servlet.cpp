#include "server-gost.h"

ClassServerGost SERVER_GOST_SERVLET;

void ClassServerGost::servlet(SSL* ssl) {
    char buf[2048];
    char reply[2048];
    int sd, bytes;
    const char* HTMLecho= "%s";

    /* do SSL-protocol accept */
    if (SSL_accept(ssl) == FAIL) { ERR_print_errors_fp(stderr); }
    else {
        /* get any certificates */
        SERVER_GOST_SERVLET.show_certs(ssl);
//        while(1)
//        {
            bytes = SSL_read(ssl, (char *)buf, sizeof((char *)buf)); // get request

            BIO_dump_fp (stdout, (const char *)buf, strlen((char *)buf));

            if (bytes > 0)
            {
                buf[bytes] = 0;
                printf("Client msg: \n%s", (char *)buf);

                //std::string a = (char *)buf;
                //SERVER_GOST_SERVLET.get_authorization(a);
                strcpy(reply,buf);
                if(strcmp((char *)buf,"login password") == 0) {
                    BIO_dump_fp (stdout, (const char *)reply, strlen((char *)reply));
                    BIO_dump_fp (stdout, (const char *)reply, strlen((char *)reply));
                    BIO_dump_fp (stdout, (const char *)reply, strlen((char *)reply));
                } else {
                    BIO_dump_fp (stdout, (const char *)reply, strlen((char *)reply));
                }
                SSL_write(ssl, (char *)reply, strlen((char *)reply));
                BIO_dump_fp (stdout, (const char *)reply, strlen((char *)reply));
            }
            else
                ERR_print_errors_fp(stderr);
//         }
        }
    sd = SSL_get_fd(ssl);   //get socket connection
    SSL_free(ssl);          //release SSL state
    close(sd);              //close connection
}
