#include "../../gost_chat.h"

EVP_PKEY *pkey = NULL;

Class_Logger logger_EVP_PKEY;

// specifying the path to the keys
std::string pubkey_server = "/home/alyona/gost-chat-server/pubkey-server.pem";
std::string pubkey_client = "/home/alyona/gost-chat-server/pubkey-client.pem";

int create_EVP_PKEY() {
    logger_EVP_PKEY.string_void = "create_EVP_PKEY()";

    /* Generate private and public keys */
    EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_id(NID_X25519, NULL);
    EVP_PKEY_keygen_init(pctx);
    EVP_PKEY_keygen(pctx, &pkey);
    EVP_PKEY_CTX_free(pctx);

    /* Print keys to stdout */
    logger_EVP_PKEY.string_message = "CLIENT'S PRIVATE KEY: ";
    logger_EVP_PKEY.logger_server();
    PEM_write_PrivateKey(stdout, pkey, NULL, NULL, 0, NULL, NULL);

    printf("\n");

    logger_EVP_PKEY.string_message = "CLIENT'S PUBKEY: ";
    logger_EVP_PKEY.logger_server();
    PEM_write_PUBKEY(stdout, pkey);

    printf("\n");

    /* Write public key to file */
    BIO *out;
    out = BIO_new_file(pubkey_client.c_str(), "w+");

    if (!out) {
        logger_EVP_PKEY.string_message = "BIO out is empty";
        logger_EVP_PKEY.logger_server();
        printf("BIO out is empty\n");
    }

    PEM_write_bio_PUBKEY(out, pkey);
    BIO_flush(out);

    return 0;
}

int read_EVP_PKEY() {
    logger_EVP_PKEY.string_void = "read_EVP_PKEY()";

    /* Read Server's public key */
    FILE *keyfile = fopen(pubkey_server.c_str(), "r");
    EVP_PKEY *peerkey = NULL;
    peerkey = PEM_read_PUBKEY(keyfile, NULL, NULL, NULL);

    logger_EVP_PKEY.string_message = "CLIENT'S PUBKEY:";
    logger_EVP_PKEY.logger_server();
    PEM_write_PUBKEY(stdout, peerkey);

    /* Generate shared secret */
    EVP_PKEY_CTX *ctx;
    unsigned char *skey;
    size_t skeylen;
    ctx = EVP_PKEY_CTX_new(pkey, NULL);

    if (!ctx) {
        logger_EVP_PKEY.string_message = "CTX is empty";
        logger_EVP_PKEY.logger_server();
    }

    if (EVP_PKEY_derive_init(ctx) <= 0) {
        logger_EVP_PKEY.string_message = "EVP_PKEY_derive_init(): EVP derive initialization failed";
        logger_EVP_PKEY.logger_server();
    }

    if (EVP_PKEY_derive_set_peer(ctx, peerkey) <= 0) {
        logger_EVP_PKEY.string_message = "EVP_PKEY_derive_set_peer(): EVP derive set peer failed";
        logger_EVP_PKEY.logger_server();
    }

    /* Determine buffer length */
    if (EVP_PKEY_derive(ctx, NULL, &skeylen) <= 0) {
        logger_EVP_PKEY.string_message = "EVP_PKEY_derive(): EVP derive failed";
        logger_EVP_PKEY.logger_server();
    }
    skey = static_cast<uint8_t *>(OPENSSL_malloc(skeylen));

    if (!skey) {
        logger_EVP_PKEY.string_message = "OpenSSL Malloc failed";
        logger_EVP_PKEY.logger_server();
    }

    if (EVP_PKEY_derive(ctx, skey, &skeylen) <= 0) {
        logger_EVP_PKEY.string_message = "EVP_PKEY_derive(): Shared key derivation failed";
        logger_EVP_PKEY.logger_server();
    }

    //printf("\nShared secret:\n");
    logger_EVP_PKEY.string_message = "SHARED SECRET: ";
    logger_EVP_PKEY.logger_server();

    for (size_t i = 0; i < skeylen; i++) {
        printf("%02x", skey[i]);
    }

    printf("\n");

    return 0;
}

int create_EVP_PKEY(char * a) {
    create_EVP_PKEY();

    int sockfd;
    uint8_t buffer[MAXLINE];
    struct sockaddr_in	 servaddr;

    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    //int len, n;
    int n;
    socklen_t len = sizeof(servaddr);

    sendto(sockfd, (const char *)a, strlen(a), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);

    buffer[n] = '\0';

    char *cptr = reinterpret_cast<char*>(const_cast<uint8_t*>(buffer));

    if(cptr[0]) {
        read_EVP_PKEY();
    }

    close(sockfd);
    return 0;
}
