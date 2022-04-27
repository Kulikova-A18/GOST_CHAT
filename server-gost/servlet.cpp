#include "server-gost.h"

ClassServerGost SERVER_GOST_SERVLET;

bool bool_get_symmetric_key = false;

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

//        while(1)
//        {
            if(!bool_get_symmetric_key) {
                bytes = SSL_read(ssl, buf, sizeof(buf)); // get request
                if (bytes > 0) {
                    buf[bytes] = 0;
                    printf("Client msg:%s", buf);

                    SERVER_GOST_SERVLET.write_client_pubkey_EVP_PKEY((char *)buf);
                    //strcpy(reply,buf);

                    std::string a = SERVER_GOST_SERVLET.send_server_EVP_PKEY();
                    char arr[a.length() + 1];
                    strcpy(arr, a.c_str());

                    SSL_write(ssl, arr, sizeof(arr));
                }
                else {
                    ERR_print_errors_fp(stderr);
                }
                bool_get_symmetric_key = true;
            }


            if(bool_get_symmetric_key) {
                unsigned char secretKey[AES_BLOCK_SIZE * 2] = {0,}; //32
                unsigned char salt[] = {'G','O','S','T','-','C','H','A','T'}; // "GOST-CHAT"
                /* A 256 bit key */
                unsigned char *key = (unsigned char *)SERVER_GOST_SERVLET.read_EVP_PKEY();

                /*create secret key - SHARED SECRET*/
                PKCS5_PBKDF2_HMAC_SHA1((const char *)key, strlen((char *)key),
                                              salt, sizeof(salt),
                                              20000 , AES_BLOCK_SIZE * 2, (unsigned char *)secretKey);

                bytes = SSL_read(ssl, buf, sizeof(buf)); // get request

                if (bytes > 0) {
                    buf[bytes] = 0;
                    printf("Client msg:%s \n", buf);
                    unsigned char* c = SERVER_GOST_SERVLET.create_decrypt((unsigned char *)buf, secretKey);
                    BIO_dump_fp (stdout, (const char *)c, strlen((char *)c));

                    unsigned char* a = SERVER_GOST_SERVLET.create_encrypt(c, secretKey);
                    BIO_dump_fp (stdout, (const char *)a, strlen((char *)a));

                    SSL_write(ssl, c, sizeof(c));   /* encrypt & send message */
                    BIO_dump_fp (stdout, (const char *)a, strlen((char *)a));

//                    bytes = SSL_read(ssl, buf, sizeof(buf)-1); /* get reply & decrypt */
//                    buf[bytes] = 0;

//                    unsigned char* b = SERVER_GOST_SERVLET.create_decrypt((unsigned char *)buf,
//                                                                  (unsigned char *)SERVER_GOST_SERVLET.read_EVP_PKEY());
//                    BIO_dump_fp (stdout, (const char *)b, strlen((char *)b));

                    //SERVER_GOST_SERVLET.get_authorization((char *)b);
                }
                else {
                    ERR_print_errors_fp(stderr);
                }
            }
            else {
                /* error */
            }
        }
//    }
    sd = SSL_get_fd(ssl);   //get socket connection
    SSL_free(ssl);          //release SSL state
    close(sd);              //close connection
}
