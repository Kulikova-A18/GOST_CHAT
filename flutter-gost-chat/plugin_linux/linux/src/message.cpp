#include "../include/gost_chat.h"
#include "../include/export.h"

ClassClientGost CLIENT_GOST_MESSAGE;
ClassClientGostLog CLIENT_GOST_MESSAGE_LOG;

int encrypted_message(char * text) {
    /* get data (login and password) */
    std::ifstream ifs("client.json");
    json j = json::parse(ifs);
    std::string key     = j_message["response server"].get<std::string>();
    std::string login   = j["login"].get<std::string>();
    
    /* A 256 bit key */
    char strcpy_key[key.length() + 1];
    strcpy(strcpy_key, key.c_str());

    /* create a message form */
    std::string message_text = "";
    j =
        {
            { "sender", login },
            { "message" , text },
        };
    message_text = j.dump();
    char ac_client_request[1024] = {0};
    sprintf(ac_client_request, "%s", message_text.c_str());

    /*create secret key - SHARED SECRET*/
    unsigned char secretKey[AES_BLOCK_SIZE * 2] = {0,}; //32
    unsigned char salt[] = {'G','O','S','T','-','C','H','A','T'}; // "GOST-CHAT"
    unsigned char *iv = (unsigned char *)"0123456789012345"; /* A 128 bit IV */
    PKCS5_PBKDF2_HMAC_SHA1((const char *)key, strlen((char *)key),
                                    salt, sizeof(salt),
                                    20000 , AES_BLOCK_SIZE * 2, (unsigned char *)secretKey);

    unsigned char *ciphertext;
    size_t plain_len_2 = strlen ((char *)ac_client_request);
    ciphertext = new unsigned char[plain_len_2 + AES_BLOCK_SIZE];
    int ciphertext_len;
    /* Encrypt the plaintext */
    ciphertext_len = CLIENT_GOST_MESSAGE.encrypt((unsigned char *)ac_client_request,
                                    strlen ((char *)ac_client_request), (unsigned char *)secretKey,
                                    iv, ciphertext);

    /* send a message broadcast */
    char ac_system[1024] = {0};
    sprintf(ac_system, "echo -n \"%s\" | socat - udp-datagram:255.255.255.255:48654,broadcast", ciphertext);
    system(ac_system);
    return 0;
}

char *decipher_message(char * text) {
    char *result_message;

    /* get data (login and password) */
    std::ifstream ifs("client.json");
    json j = json::parse(ifs);
    std::string key     = j_message["response server"].get<std::string>();
    
    /* A 256 bit key */
    char strcpy_key[key.length() + 1];
    strcpy(strcpy_key, key.c_str());

    /*create secret key - SHARED SECRET*/
    unsigned char secretKey[AES_BLOCK_SIZE * 2] = {0,}; //32
    unsigned char salt[] = {'G','O','S','T','-','C','H','A','T'}; // "GOST-CHAT"
    unsigned char *iv = (unsigned char *)"0123456789012345"; /* A 128 bit IV */
    PKCS5_PBKDF2_HMAC_SHA1((const char *)key, strlen((char *)key),
                                    salt, sizeof(salt),
                                    20000 , AES_BLOCK_SIZE * 2, (unsigned char *)secretKey);

    size_t plain_len = strlen ((char *)result_message);
    /* Buffer for the decrypted text */
    unsigned char *decryptedtext;
    decryptedtext = new unsigned char[plain_len + AES_BLOCK_SIZE];
    /* fill buffer with zeros */
    memset(decryptedtext,0,plain_len + AES_BLOCK_SIZE);
    int decryptedtext_len;
    /* Decrypt the ciphertext */
    decryptedtext_len = SERVER_GOST.decrypt((unsigned char *)result_message,
                                            strlen((char *)result_message), secretKey, iv, decryptedtext);
    /* Add a NULL terminator. We are expecting printable text */
    decryptedtext[decryptedtext_len] = '\0';

    char ac_decryptedtext[1024] = {0};
    sprintf(ac_decryptedtext, "%s", decryptedtext);

    // j = json::parse(ac_decryptedtext);
    // std::string sender      = j_message["sender"].get<std::string>();
    // std::string message     = j_message["message"].get<std::string>();

    std::string file = "get_message.json";
    ofstream i(file);
    j = json::parse(a);

    i << std::setw(ac_decryptedtext) << j;
    return result_message;
}
