#include "client-gost.h"

using namespace std;

ClassClientGost CLIENT_GOST;

std::string login = "konovalov@gost_chat.com";
std::string password = "E2WpF6qK";

bool bool_get_symmetric_key = false;

int main(int argc, char *argv[])
{
    std::cout << "=============== data ===============" << std::endl;
    std::cout << "login: " << login << std::endl;
    std::cout << "password: " << password << std::endl;
    std::cout << "====================================" << std::endl << std::endl;

    int sockfd;
    uint8_t buffer[MAXLINE];
    struct sockaddr_in	 servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family             = AF_INET;
    servaddr.sin_port               = htons(PORT);
    servaddr.sin_addr.s_addr        = INADDR_ANY;

    //int len, n;
    int n;
    socklen_t len = sizeof(servaddr);

    // create evp pkey
    CLIENT_GOST.create_EVP_PKEY();

    std::cout << "=============== send message ===============" << std::endl;
    std::string a = CLIENT_GOST.send_client_EVP_PKEY();
    char arr[a.length() + 1];
    strcpy(arr, a.c_str());
    sendto(sockfd, (const char *)arr, strlen(arr), MSG_CONFIRM,
           (const struct sockaddr *) &servaddr, sizeof(servaddr));
    BIO_dump_fp (stdout, (const char *)arr, strlen((char *)arr));
    std::cout << std::endl << std::endl;

    //printf("get message\n");
    std::cout << "=============== get message ===============" << std::endl;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL,
                 (struct sockaddr *) &servaddr, &len);
    buffer[n] = '\0';
    char *cptr = reinterpret_cast<char*>(const_cast<uint8_t*>(buffer));
    BIO_dump_fp (stdout, (const char *)cptr, strlen((char *)cptr));
    CLIENT_GOST.write_server_pubkey_EVP_PKEY((char *)cptr);
    std::cout << std::endl << std::endl;

    unsigned char secretKey[AES_BLOCK_SIZE * 2] = {0,}; //32
    unsigned char salt[] = {'G','O','S','T','-','C','H','A','T'}; // "GOST-CHAT"
    /* A 256 bit key */
    unsigned char *key = (unsigned char *)CLIENT_GOST.read_EVP_PKEY();

    /*create secret key - SHARED SECRET*/
    PKCS5_PBKDF2_HMAC_SHA1((const char *)key, strlen((char *)key),
                                  salt, sizeof(salt),
                                  20000 , AES_BLOCK_SIZE * 2, (unsigned char *)secretKey);

    size_t plain_len = strlen ((char *)CLIENT_GOST.check_authorization(login, password).c_str());
    /*
    * Buffer for ciphertext. Ensure the buffer is long enough for the
    * ciphertext which may be longer than the plaintext, depending on the
    * algorithm and mode.
    */
    unsigned char *ciphertext;
    ciphertext = new unsigned char[plain_len + AES_BLOCK_SIZE];
    int ciphertext_len;
    /* Encrypt the plaintext */
    ciphertext_len = CLIENT_GOST.encrypt(
               (unsigned char *)CLIENT_GOST.check_authorization(login, password).c_str(),
               strlen ((char *)CLIENT_GOST.check_authorization(login, password).c_str()),
               (unsigned char *)secretKey, (unsigned char *)"0123456789012345",
                             ciphertext);

    std::cout << "=============== send message ===============" << std::endl;
    char ciphertext_request[1024] = {0};
    sprintf(ciphertext_request, "%s", ciphertext);
    sendto(sockfd, (const char *)ciphertext_request, strlen(ciphertext_request), MSG_CONFIRM,
          (const struct sockaddr *) &servaddr, sizeof(servaddr));
    BIO_dump_fp (stdout, (const char *)ciphertext, strlen((char *)ciphertext));
    std::cout << std::endl << std::endl;

    std::cout << "=============== get message ===============" << std::endl;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);
    buffer[n] = '\0';
    cptr = reinterpret_cast<char*>(const_cast<uint8_t*>(buffer));
    unsigned char* b = CLIENT_GOST.create_decrypt((unsigned char *)cptr, secretKey);
    BIO_dump_fp (stdout, (char *)b, strlen((char *)b));
    std::cout << std::endl << std::endl;

    CLIENT_GOST.get_authorization((char *)b);

    if(remove("client-pubkey-server.pem")) {
        //printf("Error removing file");
    }
    if(remove("client-pubkey-client.pem")) {
        //printf("Error removing file");
    }

    return 0;
}
