#include "../client-gost.h"

#include <iostream>
#include <fstream>

EVP_PKEY *pkey = NULL;

// specifying the path to the keys
std::string pubkey_server = "client-pubkey-server.pem";
std::string pubkey_client = "client-pubkey-client.pem";

std::string ClassClientGost::send_client_EVP_PKEY() {
    std::string line = "";
    std::string result = "";

    std::ifstream in(pubkey_client);
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

int ClassClientGost::create_EVP_PKEY() {
    printf("client EVP_PKEY\n");
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
    out = BIO_new_file(pubkey_client.c_str(), "w+");

    if (!out) {
        printf("BIO out is empty\n");
    }

    PEM_write_bio_PUBKEY(out, pkey);
    BIO_flush(out);

    // return to pubkey from client
    return 0;
}

int ClassClientGost::write_server_pubkey_EVP_PKEY(char *clientkey) {
    std::ofstream out;
    out.open(pubkey_server);
    if (out.is_open()) {
        out << clientkey;
    }
    return 0;
}

unsigned char *ClassClientGost::read_EVP_PKEY() {
    /* Read Server's public key */
    FILE *keyfile = fopen(pubkey_server.c_str(), "r");
    EVP_PKEY *peerkey = NULL;
    peerkey = PEM_read_PUBKEY(keyfile, NULL, NULL, NULL);

    printf("server EVP_PKEY\n");
    PEM_write_PUBKEY(stdout, peerkey);

    /* Generate shared secret */
    EVP_PKEY_CTX *ctx;
    unsigned char *skey;
    size_t skeylen;
    ctx = EVP_PKEY_CTX_new(pkey, NULL);

    if (!ctx) {
        //logger_EVP_PKEY.string_message = "CTX is empty";
    }

    if (EVP_PKEY_derive_init(ctx) <= 0) {
        //logger_EVP_PKEY.string_message = "EVP_PKEY_derive_init(): EVP derive initialization failed";
    }

    if (EVP_PKEY_derive_set_peer(ctx, peerkey) <= 0) {
        //logger_EVP_PKEY.string_message = "EVP_PKEY_derive_set_peer(): EVP derive set peer failed";
    }

    /* Determine buffer length */
    if (EVP_PKEY_derive(ctx, NULL, &skeylen) <= 0) {
        //logger_EVP_PKEY.string_message = "EVP_PKEY_derive(): EVP derive failed";
    }
    skey = static_cast<uint8_t *>(OPENSSL_malloc(skeylen));

    if (!skey) {
        //logger_EVP_PKEY.string_message = "OpenSSL Malloc failed";
    }

    if (EVP_PKEY_derive(ctx, skey, &skeylen) <= 0) {
        //logger_EVP_PKEY.string_message = "EVP_PKEY_derive(): Shared key derivation failed";
    }

    printf("shared secret\n");
    //logger_EVP_PKEY.string_message = "SHARED SECRET: ";

    for (size_t i = 0; i < skeylen; i++) {
        printf("%02x", skey[i]);
    }
    printf("\n");
    return (unsigned char *)skey;
}
