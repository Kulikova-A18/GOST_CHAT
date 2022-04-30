#include "server-gost.h"

ClassServerGost SERVER_GOST_SERVLET;

bool bool_get_symmetric_key = false;

void ClassServerGost::servlet(SSL* ssl) {
    char buf[MAXLINE] = {0};
    char buf2[MAXLINE] = {0};
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
//        while(1)
//        {
    if(!bool_get_symmetric_key) {
        printf("get message\n");
        bytes = SSL_read(ssl, buf, sizeof(buf)); // get request
        BIO_dump_fp (stdout, (const char *)buf, strlen((char *)buf));
        buf[bytes] = '\0';

        if (bytes < 0) { ERR_print_errors_fp(stderr); }
        else
        {
            SERVER_GOST_SERVLET.write_client_pubkey_EVP_PKEY((char *)buf);

            std::string a = SERVER_GOST_SERVLET.send_server_EVP_PKEY();
            char arr[a.length() + 1];
            strcpy(arr, a.c_str());

            printf("send message\n");
            SSL_write(ssl, arr, sizeof(arr));
            BIO_dump_fp (stdout, (const char *)arr, strlen((char *)arr));

            bool_get_symmetric_key = true;
        }
    }
    memset(buf, 0, sizeof(buf)); // clear buf

    if(bool_get_symmetric_key) {
        unsigned char secretKey[AES_BLOCK_SIZE * 2] = {0,}; //32
        unsigned char salt[] = {'G','O','S','T','-','C','H','A','T'}; // "GOST-CHAT"
        /* A 256 bit key */
        unsigned char *key = (unsigned char *)SERVER_GOST_SERVLET.read_EVP_PKEY();

        /*create secret key - SHARED SECRET*/
        PKCS5_PBKDF2_HMAC_SHA1((const char *)key, strlen((char *)key),
                                      salt, sizeof(salt),
                                      20000 , AES_BLOCK_SIZE * 2, (unsigned char *)secretKey);

        printf("get message\n");
        bytes = SSL_read(ssl, buf2, sizeof(buf2)); // get request
        BIO_dump_fp (stdout, (const char *)buf2, strlen((char *)buf2));
        buf2[bytes] = '\0';

        if (bytes < 0) { ERR_print_errors_fp(stderr); }
        else
        {

            /* A 128 bit IV */
            unsigned char *iv = (unsigned char *)"0123456789012345";


            size_t plain_len = strlen ((char *)buf2);
            /* Buffer for the decrypted text */
            unsigned char *decryptedtext;
            decryptedtext = new unsigned char[plain_len + AES_BLOCK_SIZE];
            /* fill buffer with zeros */
            memset(decryptedtext,0,plain_len + AES_BLOCK_SIZE);
            int decryptedtext_len;
            /* Decrypt the ciphertext */
            decryptedtext_len = SERVER_GOST_SERVLET.decrypt((unsigned char *)buf2, strlen((char *)buf2), key, iv,
                                        decryptedtext);
            /* Add a NULL terminator. We are expecting printable text */
            decryptedtext[decryptedtext_len] = '\0';

            //unsigned char* c = SERVER_GOST_SERVLET.create_decrypt((unsigned char *)buf, secretKey);
            char ac[1024] = {0};
            sprintf(ac, "%s", decryptedtext);

            BIO_dump_fp (stdout, (const char *)ac, strlen((char *)ac));

            char ac_client_request[1024] = {0};
            sprintf(ac_client_request, "%s", SERVER_GOST_SERVLET.check_json_message(ac).c_str());

            //unsigned char* a = SERVER_GOST_SERVLET.create_encrypt(c, secretKey);

            printf("send message\n");
           //SSL_write(ssl, a, sizeof(a));   /* encrypt & send message */
           //BIO_dump_fp (stdout, (const char *)a, strlen((char *)a));
        }
    }

//         }

    sd = SSL_get_fd(ssl);   //get socket connection
    SSL_free(ssl);          //release SSL state
    close(sd);              //close connection
}
