#include "client-gost.h"

ClassClientGost CLIENT_GOST;

unsigned char secretKey[AES_BLOCK_SIZE*2] = {0,}; //32
unsigned char salt[] = {'G','O','S','T','-','C','H','A','T'}; // "GOST-CHAT"

int main(int count, char *strings[])
{
    /* A 256 bit key */
    unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

    /*create secret key - SHARED SECRET*/
    PKCS5_PBKDF2_HMAC_SHA1((const char *)key, strlen((char *)key),
                                  salt, sizeof(salt),
                                  20000 , AES_BLOCK_SIZE*2, (unsigned char *)secretKey);

    SSL_CTX *ctx;
    int server;
    SSL *ssl;
    char buf[1024];
    int bytes;
    char *hostname = (char *)"127.0.0.1", *portnum = (char *)"8081";
    char msg[1024];

    printf("HELLO!!\n");
    SSL_library_init();
    //hostname=strings[1];
    //portnum=strings[2];

    ctx = CLIENT_GOST.init_CTX();
    server = CLIENT_GOST.open_connection(hostname, atoi(portnum));
    printf("HELLO!!\n");
    ssl = SSL_new(ctx);      /* create new SSL connection state */
    if(!ctx) {
        ERR_print_errors_fp(stderr);    //throw or return an error
    }
    SSL_set_fd(ssl, server);    /* attach the socket descriptor */
    if ( SSL_connect(ssl) == FAIL )   /* perform the connection */
        ERR_print_errors_fp(stderr);
    else
    {
        printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
        while(1)
        {
            printf("Client:");
            fgets(msg,sizeof(msg),stdin);
                   /* get any certs */
            SSL_write(ssl, msg, strlen(msg));   /* encrypt & send message */
            bytes = SSL_read(ssl, buf, sizeof(buf)-1); /* get reply & decrypt */
            buf[bytes] = 0;
            printf("SERVER:%s", buf);
        }
        SSL_free(ssl);        /* release connection state */
    }
    close(server);         /* close socket */
    SSL_CTX_free(ctx);        /* release context */
    return 0;
}
