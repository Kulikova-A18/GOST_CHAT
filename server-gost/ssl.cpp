#include "server-gost.h"

int ClassServerGost::open_listener(int PORT) {
    int sd;
    struct sockaddr_in addr;

    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
        perror("can't bind port");
        abort();
    }
    if ( listen(sd, 10) != 0 ) {
        perror("Can't configure listening port");
        abort();
    }
    return sd;
}

SSL_CTX* ClassServerGost::init_server_CTX(void) {
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    SSL_library_init();
    SSL_load_error_strings();

    OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
    SSL_load_error_strings();   /* load all error messages */
    method = TLS_server_method();  /* create new server-method instance */
    ctx = SSL_CTX_new(method);   /* create new context from method */
    if ( ctx == NULL )
    {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void ClassServerGost::load_certificates(SSL_CTX* ctx, char* CERT_FILE, char* PRIVATE_KEY_FILE) {
    /* set the local certificate from CERT_FILE */
    if (SSL_CTX_use_certificate_file(ctx, CERT_FILE, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* set the private key from PRIVATE_KEY_FILE (may be the same as CERT_FILE) */
    if (SSL_CTX_use_PrivateKey_file(ctx, PRIVATE_KEY_FILE, SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        abort();
    }
}

void ClassServerGost::show_certs(SSL* ssl) {
    X509 *CERT;
    char *line;
    /* Get certificates (if available) */
    CERT = SSL_get_peer_certificate(ssl);
    if (CERT != NULL) {
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(CERT), 0, 0);
        printf("Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(CERT), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);
        X509_free(CERT);
    }
    else
        printf("No certificates.\n");
}
