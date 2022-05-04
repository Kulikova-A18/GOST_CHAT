#include "../server-gost.h"

#include <iostream>
#include <fstream>

EVP_PKEY *pkey = NULL;

// specifying the path to the keys
std::string pubkey_server = "server-pubkey-server.pem";
std::string pubkey_client = "server-pubkey-client.pem";

ClassServerGostLog SERVER_GOST_PKEY_LOG;

std::string ClassServerGost::send_server_EVP_PKEY() {
    std::string line = "";
    std::string result = "";

    std::ifstream in(pubkey_server);
    if (in.is_open()) {
        result += "-----BEGIN PUBLIC KEY-----\n";
        while (getline(in, line)) {
            if(line != "-----BEGIN PUBLIC KEY-----" &&
                    line != "-----END PUBLIC KEY-----"){
                result += line;
            }
        }
        result += "\n-----END PUBLIC KEY-----";
    }
    in.close();
    return result;
}

unsigned char *ClassServerGost::create_EVP_PKEY() {
    SERVER_GOST_PKEY_LOG.string_void = "ClassServerGost::create_EVP_PKEY()";

    std::cout << "=============== server EVP_PKEY ===============" << std::endl;

    /* Generate private and public keys */
    EVP_PKEY_CTX *pctx = EVP_PKEY_CTX_new_id(NID_X25519, NULL);
    EVP_PKEY_keygen_init(pctx);
    EVP_PKEY_keygen(pctx, &pkey);
    EVP_PKEY_CTX_free(pctx);

    /* Print keys to stdout */
    PEM_write_PrivateKey(stdout, pkey, NULL, NULL, 0, NULL, NULL);
    printf("\n");
    PEM_write_PUBKEY(stdout, pkey);

    printf("\n");

    /* Write public key to file */
    BIO *out;
    out = BIO_new_file(pubkey_server.c_str(), "w+");

    if (!out) {
        SERVER_GOST_PKEY_LOG.string_message = "BIO_new_file(): BIO out is empty";
        SERVER_GOST_PKEY_LOG.logger();
    }

    PEM_write_bio_PUBKEY(out, pkey);
    BIO_flush(out);

    // return to pubkey from client
    return (unsigned char *)pkey;
}

int ClassServerGost::write_client_pubkey_EVP_PKEY(char *clientkey) {
    std::ofstream out;
    out.open(pubkey_client);
    if (out.is_open()) {
        out << clientkey;
    }
    return 0;
}

unsigned char *ClassServerGost::read_EVP_PKEY() {
    SERVER_GOST_PKEY_LOG.string_void = "ClassServerGost::read_EVP_PKEY()";

    /* Read Client's public key */
    FILE *keyfile = fopen(pubkey_client.c_str(), "r");
    EVP_PKEY *peerkey = NULL;
    peerkey = PEM_read_PUBKEY(keyfile, NULL, NULL, NULL);

    std::cout << "=============== client EVP_PKEY ===============" << std::endl;
    PEM_write_PUBKEY(stdout, peerkey);
    std::cout << std::endl << std::endl;

    /* Generate shared secret */
    EVP_PKEY_CTX *ctx;
    unsigned char *skey;
    size_t skeylen;

    ctx = EVP_PKEY_CTX_new(pkey, NULL);

    if (!ctx) {
        SERVER_GOST_PKEY_LOG.string_message = "EVP_PKEY_CTX_new(): CTX is empty";
        SERVER_GOST_PKEY_LOG.logger();
    }

    if (EVP_PKEY_derive_init(ctx) <= 0) {
        SERVER_GOST_PKEY_LOG.string_message
                = "EVP_PKEY_derive_init(): EVP derive initialization failed";
        SERVER_GOST_PKEY_LOG.logger();
    }

    if (EVP_PKEY_derive_set_peer(ctx, peerkey) <= 0) {
        SERVER_GOST_PKEY_LOG.string_message
                = "EVP_PKEY_derive_set_peer(): EVP derive set peer failed";
        SERVER_GOST_PKEY_LOG.logger();
    }

    /* Determine buffer length */
    if (EVP_PKEY_derive(ctx, NULL, &skeylen) <= 0) {
        SERVER_GOST_PKEY_LOG.string_message = "EVP_PKEY_derive(): EVP derive failed";
        SERVER_GOST_PKEY_LOG.logger();
    }

    skey = static_cast<uint8_t *>(OPENSSL_malloc(skeylen));

    if (!skey) {
        SERVER_GOST_PKEY_LOG.string_message = "OPENSSL_malloc(): OpenSSL Malloc failed";
        SERVER_GOST_PKEY_LOG.logger();
    }

    if (EVP_PKEY_derive(ctx, skey, &skeylen) <= 0) {
        SERVER_GOST_PKEY_LOG.string_message = "EVP_PKEY_derive(): Shared key derivation failed";
        SERVER_GOST_PKEY_LOG.logger();
    }

    std::cout << "=============== shared secret ===============" << std::endl;
    for (size_t i = 0; i < skeylen; i++) {
        printf("%02x", skey[i]);
    }

    printf("\n\n");
    return skey;
}
