#include "server-gost.h"

#include <sys/stat.h>

using namespace std;

ClassServerGost SERVER_GOST;
ClassServerGostLog SERVER_GOST_LOG;

int is_root() {
    if (getuid() != 0) { return 0; }
    else { return 1; }
}

int main(int arvc, char *argv[])
{
    setbuf(stdout, NULL);

    std::string login_admin = "root", password_admin = "root";
    std::cout << "=============== sign in ===============" << std::endl;
    std::cout << "login: " << login_admin << std::endl;
    //std::cin >> login_admin;
    std::cout << "password: ";
    for(int i = 0; i < password_admin.length(); i++) printf("*");
    std::cout << std::endl;
    //std::cin >> password_admin;

    if(login_admin != "root" || password_admin != "root") {
        SERVER_GOST_LOG.string_void = "main()";
        SERVER_GOST_LOG.string_message = "authorization failed";
        SERVER_GOST_LOG.logger();

        std::cout << "\nauthorization failed\n";

        exit(0);
    }

    std::cout << "\n\n";

    struct stat st = {0};
    if (stat("data", &st) == -1) { mkdir("data", 0700); }


    SERVER_GOST.create_all();   // create data about people
    SERVER_GOST.create_EVP_PKEY(); // create public and private evp pkey

    if(!is_root()) {
        SERVER_GOST_LOG.string_void = "main()";
        SERVER_GOST_LOG.string_message = "is_root(): This program must be run as root/sudo user";
        SERVER_GOST_LOG.logger();
        exit(0);
    }

    setbuf(stdout, NULL);
    // Creating socket file descriptor
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        SERVER_GOST_LOG.string_void = "main()";
        SERVER_GOST_LOG.string_message = "socket(): socket creation failed";
        SERVER_GOST_LOG.logger();
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in servaddr, cliaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family         = AF_INET; // IPv4
//    servaddr.sin_addr.s_addr    = INADDR_ANY;
    servaddr.sin_addr.s_addr    = inet_addr("127.0.0.1");
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
//    while(1)
//    {
        std::cout << "=============== get message ===============" << std::endl;
        n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
        buffer[n] = '\0';
        char *cptr = reinterpret_cast<char*>(const_cast<uint8_t*>(buffer));
        BIO_dump_fp (stdout, (const char *)cptr, strlen((char *)cptr));
        std::cout << std::endl << std::endl;

        SERVER_GOST.write_client_pubkey_EVP_PKEY((char *)buffer);

        std::string a = SERVER_GOST.send_server_EVP_PKEY();
        char arr[a.length() + 1];
        strcpy(arr, a.c_str());

        std::cout << "=============== send message ===============" << std::endl;
        sendto(sockfd, (const char *)arr, strlen(arr), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
        BIO_dump_fp (stdout, (const char *)arr, strlen((char *)arr));
        std::cout << std::endl << std::endl;

        unsigned char secretKey[AES_BLOCK_SIZE * 2] = {0,}; //32
        unsigned char salt[] = {'G','O','S','T','-','C','H','A','T'}; // "GOST-CHAT"
        /* A 256 bit key */
        unsigned char *key = (unsigned char *)SERVER_GOST.read_EVP_PKEY();

        /*create secret key - SHARED SECRET*/
        PKCS5_PBKDF2_HMAC_SHA1((const char *)key, strlen((char *)key),
                                      salt, sizeof(salt),
                                      20000 , AES_BLOCK_SIZE * 2, (unsigned char *)secretKey);

        std::cout << "=============== get message ===============" << std::endl;
        n = recvfrom(sockfd, buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
        buffer[n] = '\0';
        cptr = reinterpret_cast<char*>(const_cast<uint8_t*>(buffer));


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

        char ac_client_request[1024] = {0};
        sprintf(ac_client_request, "%s", SERVER_GOST.check_json_message(ac).c_str());


        std::cout << "=============== send message ===============" << std::endl;
        unsigned char *ciphertext;
        size_t plain_len_2 = strlen ((char *)ac_client_request);
        ciphertext = new unsigned char[plain_len_2 + AES_BLOCK_SIZE];
        int ciphertext_len;
        /* Encrypt the plaintext */
        ciphertext_len = SERVER_GOST.encrypt((unsigned char *)ac_client_request,
                                             strlen ((char *)ac_client_request), (unsigned char *)secretKey,
                                             (unsigned char *)"0123456789012345", ciphertext);
        sendto(sockfd, (const char *)ciphertext, strlen((char *)ciphertext), MSG_CONFIRM,
               (const struct sockaddr *)&cliaddr, len);
        BIO_dump_fp (stdout, (const char *)ciphertext, strlen((char *)ciphertext));
        std::cout << std::endl << std::endl;

        // ======== remove pem ========
        if(remove("server-pubkey-server.pem")) {
            SERVER_GOST_LOG.string_void = "main()";
            SERVER_GOST_LOG.string_message = "remove(): Error removing server-pubkey-server.pem";
            SERVER_GOST_LOG.logger();
        }
        if(remove("server-pubkey-client.pem")) {
            SERVER_GOST_LOG.string_void = "main()";
            SERVER_GOST_LOG.string_message = "remove(): Error removing server-pubkey-client.pem";
            SERVER_GOST_LOG.logger();
        }
//    }

    return 0;
}
