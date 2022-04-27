#include "client-gost.h"

ClassClientGost CLIENT_GOST_CTX;

void handleErrors() {
    printf("Error occured");
    return;
}

/* A 128 bit IV */
unsigned char *iv = (unsigned char *)"0123456789012345";

int ClassClientGost::decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
            unsigned char *iv, unsigned char *plaintext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */

    auto cipher = EVP_get_cipherbynid(NID_grasshopper_cbc);
    if (!cipher) {
        //qWarning("[ChatCrypt::decrypt] Could not initialize Grasshopper cipher. Is the GOST library loaded?");
    }

    if(1 != EVP_DecryptInit_ex(ctx,
                               cipher,
                               //EVP_aes_256_cbc(),
                               NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
        handleErrors();

    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len))
        handleErrors();
    plaintext_len += len;

    //EVP_CIPHER
    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}

int ClassClientGost::encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
            unsigned char *iv, unsigned char *ciphertext)
{
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))
        handleErrors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */

    auto cipher = EVP_get_cipherbynid(NID_grasshopper_cbc);
    if (!cipher) {
        printf("[ChatCrypt::decrypt] Could not initialize Grasshopper cipher. Is the GOST library loaded?");
    }

    if(1 != EVP_EncryptInit_ex(ctx,
                               cipher,
                               //EVP_aes_256_cbc(),
                               NULL, key, iv))
        handleErrors();

    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
        handleErrors();
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

unsigned char *ClassClientGost::create_encrypt(unsigned char *plaintext, unsigned char *private_key) {
    size_t plain_len = strlen ((char *)plaintext);

   /*
    * Buffer for ciphertext. Ensure the buffer is long enough for the
    * ciphertext which may be longer than the plaintext, depending on the
    * algorithm and mode.
    */
   unsigned char *ciphertext;

   ciphertext = new unsigned char[plain_len+AES_BLOCK_SIZE];

   int ciphertext_len;

   /* Encrypt the plaintext */
   ciphertext_len = CLIENT_GOST_CTX.encrypt(plaintext, strlen ((char *)plaintext), (unsigned char *)private_key, iv,
                             ciphertext);

   printf("!!!!!!!!11\n");
    return ciphertext;
}

unsigned char *ClassClientGost::create_decrypt(unsigned char *plaintext, unsigned char *private_key) {
    size_t plain_len = strlen ((char *)plaintext);

    /* Buffer for the decrypted text */
    unsigned char *decryptedtext;
    decryptedtext = new unsigned char[plain_len + AES_BLOCK_SIZE];

    /* fill buffer with zeros */
    memset(decryptedtext,0,plain_len + AES_BLOCK_SIZE);

    int decryptedtext_len;

    /* Decrypt the ciphertext */
    decryptedtext_len = CLIENT_GOST_CTX.decrypt(plaintext, strlen((char *)plaintext), (unsigned char *)private_key, iv,
                                decryptedtext);

    /* Add a NULL terminator. We are expecting printable text */
    decryptedtext[decryptedtext_len] = '\0';

    return decryptedtext;
}
