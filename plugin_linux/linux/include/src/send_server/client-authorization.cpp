#include "../../gost_chat.h"

string message_successfully = "";
string message_unsuccessful = "";

int result_autorization;

int create_autorization(char *a) {
    json j;

    j =
        {
            { "sender", "server" },
            { "message" , "successfully" }
        };
   message_successfully = j.dump();

   j =
        {
            { "sender", "server" },
            { "message" , "unsuccessful" }
        };
    message_unsuccessful = j.dump();

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

    if(cptr == message_successfully) {
        result_autorization = 0;
    }
    if(cptr == message_unsuccessful) {
        result_autorization = 1;
    }

    close(sockfd);

    return result_autorization;
}
