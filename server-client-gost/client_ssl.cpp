#include "client-gost.h"

int ClassClientGost::open_connection(const char *hostname, int port)
{
    int sd;
    struct hostent *host;
    struct sockaddr_in addr;

    if ((host = gethostbyname(hostname)) == NULL) {        
        perror(hostname);
        abort();
    }

    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);

    if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 )
    {
        close(sd);
        perror(hostname);
        abort();
    }
    return sd;
}

SSL_CTX* ClassClientGost::init_CTX(void)
{
    const SSL_METHOD *method = TLS_client_method();  /* Create new client-method instance */
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    ctx = SSL_CTX_new(method);   /* Create new context */
    if (ctx == NULL) {
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}
