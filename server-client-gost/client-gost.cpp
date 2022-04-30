#include "client-gost.h"

ClassClientGost CLIENT_GOST;

std::string login = "konovalov@gost_chat.com";
std::string password = "E2WpF6qK";

bool bool_get_symmetric_key = false;

int main(int arvc, char *argv[])
{
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

//    std::string a = CLIENT_GOST.check_authorization(login, password);
//    char ac_client_request[1024] = {0};
//    const char *cpRequestMessage = "%s";
//    sprintf(ac_client_request, cpRequestMessage, a.c_str());

//    printf("send message\n");
//    SSL_write(ssl, ac_client_request, strlen(ac_client_request));   /* encrypt & send message */
//    BIO_dump_fp (stdout, ac_client_request, strlen(ac_client_request));

//    printf("get message\n");
//    bytes = SSL_read(ssl, buf, sizeof(buf)-1); /* get reply & decrypt */
//    BIO_dump_fp (stdout, buf, strlen(buf));

//    buf[bytes] = '\0';

    if(!bool_get_symmetric_key) {
        // create evp pkey
        CLIENT_GOST.create_EVP_PKEY();

        std::string a = CLIENT_GOST.send_client_EVP_PKEY();
        char arr[a.length() + 1];
        strcpy(arr, a.c_str());
        printf("send message\n");
        SSL_write(ssl, arr, sizeof(arr));   /* encrypt & send message */

        bytes = SSL_read(ssl, buf, sizeof(buf)-1); /* get reply & decrypt */
        buf[bytes] = '\0';
        if (bytes < 0) { ERR_print_errors_fp(stderr); }

        printf("get message\n");
        CLIENT_GOST.write_server_pubkey_EVP_PKEY((char *)buf);
        bool_get_symmetric_key = true;
    }
    if(bool_get_symmetric_key) {
        unsigned char secretKey[AES_BLOCK_SIZE * 2] = {0,}; //32
        unsigned char salt[] = {'G','O','S','T','-','C','H','A','T'}; // "GOST-CHAT"
        /* A 256 bit key */
        unsigned char *key = (unsigned char *)CLIENT_GOST.read_EVP_PKEY();

        /*create secret key - SHARED SECRET*/
        PKCS5_PBKDF2_HMAC_SHA1((const char *)key, strlen((char *)key),
                                      salt, sizeof(salt),
                                      20000 , AES_BLOCK_SIZE * 2, (unsigned char *)secretKey);
        unsigned char* a = CLIENT_GOST.create_encrypt(
                                (unsigned char *)CLIENT_GOST.check_authorization(login, password).c_str(),secretKey);
        BIO_dump_fp (stdout, (const char *)a, strlen((char *)a));
        SSL_write(ssl, (char *)a, sizeof((char *)a));   /* encrypt & send message */

        bytes = SSL_read(ssl, buf, sizeof(buf)-1); /* get reply & decrypt */
        buf[bytes] = '\0';
        if (bytes < 0) { ERR_print_errors_fp(stderr); }

        unsigned char* b = CLIENT_GOST.create_decrypt((unsigned char *)buf, secretKey);
        BIO_dump_fp (stdout, (char *)b, strlen((char *)b));
        CLIENT_GOST.get_authorization((char *)b);
    }


    SSL_free(ssl);        /* release connection state */
    close(server);         /* close socket */
    SSL_CTX_free(ctx);        /* release context */
    return 0;
}
