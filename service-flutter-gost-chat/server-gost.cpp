#include "server-gost.h"

using namespace std;

ClassServerGost SERVER_GOST;

int main(int arvc, char *argv[])
{
    setbuf(stdout, NULL);

    // Creating socket file descriptor
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in servaddr, cliaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family         = AF_INET; // IPv4
    servaddr.sin_addr.s_addr    = INADDR_ANY;
    servaddr.sin_port           = htons(PORT);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        exit(EXIT_FAILURE);
    }

    socklen_t len = sizeof(servaddr);
    len = sizeof(cliaddr);  //len is value/resuslt

    int n;
    uint8_t buffer[MAXLINE];

    /* start */
    while(1)
    {
        unsigned char secretKey[AES_BLOCK_SIZE * 2] = {0,}; //32
        unsigned char salt[] = {'G','O','S','T','-','C','H','A','T','G','O','S','T','-','C','H'}; // "GOST-CHAT"
        /* A 256 bit key */
        unsigned char *key = (unsigned char *)SIMMETRIC_KEY;

        /*create secret key - SHARED SECRET*/
        PKCS5_PBKDF2_HMAC_SHA1((const char *)key, strlen((char *)key),
                                      salt, sizeof(salt),
                                      20000 , AES_BLOCK_SIZE * 2, (unsigned char *)secretKey);

        std::cout << "=============== get message ===============" << std::endl;
        n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
        buffer[n] = '\0';
        char *cptr = reinterpret_cast<char*>(const_cast<uint8_t*>(buffer));

        unsigned char *iv = (unsigned char *)"0123456789012345"; /* A 128 bit IV */
        size_t plain_len = strlen ((char *)buffer);
        /* Buffer for the decrypted text */
        unsigned char *decryptedtext;
        decryptedtext = new unsigned char[plain_len + AES_BLOCK_SIZE];
        /* fill buffer with zeros */
        memset(decryptedtext,0,plain_len + AES_BLOCK_SIZE);
        int decryptedtext_len;
        /* Decrypt the ciphertext */
        decryptedtext_len = SERVER_GOST.decrypt((unsigned char *)buffer,
                                                strlen((char *)buffer), secretKey, iv, decryptedtext);
        /* Add a NULL terminator. We are expecting printable text */
        decryptedtext[decryptedtext_len] = '\0';

        char ac[1024] = {0};
        sprintf(ac, "%s", decryptedtext);

        BIO_dump_fp (stdout, (const char *)ac, strlen((char *)ac));
        std::cout << std::endl << std::endl;
        try
        {
            std::string file = "/home/alyona/GOST_CHAT/flutter-gost-chat/get_message.json";
            ofstream i(file);
            json j = json::parse(ac);

            i << std::setw(4) << j;
        }
        catch (json::parse_error& e)
        {
            // output exception information
            std::cout << "message: " << e.what() << '\n'
                        << "exception id: " << e.id << '\n'
                        << "byte position of error: " << e.byte << std::endl;
        }
    }

    return 0;
}
