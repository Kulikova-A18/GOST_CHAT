#include "../../gost_chat.h"

string message_client;
char message_client_buf[255];

bool bool_create_EVP_PKEY = false;
bool bool_get_symmetric_key = false;
int result_create_autorization;

// Driver code
int main() {
    if(bool_create_EVP_PKEY == false) {
        // EVP-PKEY
        printf("\n\nEVP-PKEY\n\n");
        message_client = create_handshake();
        strcpy(message_client_buf,message_client.c_str());
        create_EVP_PKEY(message_client_buf);
        bool_create_EVP_PKEY = true;
    }

    if(bool_create_EVP_PKEY == true) {
        message_client = get_symmetric_key();
        strcpy(message_client_buf,message_client.c_str());
        char *result_message_client_buf = create_symmetric_key(message_client_buf);

        printf("%s\n",result_message_client_buf);
    }

    return 0;
}
