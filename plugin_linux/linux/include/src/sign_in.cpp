#include "../gost_chat.h"
#include "../export.h"

using namespace std;

/*
list of return:

0 - successfully
1 - fields are empty
2 - unsuccessful
*/

std::string message_client;
char message_client_buf[255];

bool bool_create_EVP_PKEY = false;
int result_create_autorization;

int result_sign_in_linux = 0;

LIBRARY_API
int _sign_in_linux (char *argv1, char *argv2) {

    //_logger_void = "_sign_in_linux()";
    if (!argv1[0] && !argv2[0]) {
        //_logger(_logger_void,"all variables are empty");
        return 1;
    } 

    if(bool_create_EVP_PKEY == false) {
        // EVP-PKEY
        printf("\n\nEVP-PKEY\n\n");
        message_client = create_handshake();
        strcpy(message_client_buf,message_client.c_str());
        create_EVP_PKEY(message_client_buf);
        bool_create_EVP_PKEY = true;
    }

    if(bool_create_EVP_PKEY == true) {
            message_client = check_authorization(argv1, argv2);
            strcpy(message_client_buf,message_client.c_str());
            result_create_autorization = create_autorization(message_client_buf);

            switch (result_create_autorization) {
                case 0:
                    printf("successfully\n");
                    result_sign_in_linux = 0;
                    break;
                case 1:
                    printf("unsuccessful\n");
                    result_sign_in_linux = 2;
                    break;
                default:
                    break;
            }
        }
        
    return result_sign_in_linux;
}

std::string read_user = "/home/alyona/gost-chat-server/user.txt";

LIBRARY_API
char *_print_user_linux() {
    std::string line, text;
    
    std::ifstream in(read_user);
     if (in.is_open()) {
        while (getline(in, line)) {
            text += line;
        }
    }
    in.close();
    
    char* c = const_cast<char*>(text.c_str());
    char* result_argv = (char*) malloc(strlen(c)+1); 
    strcpy(result_argv,c);
    
    return result_argv;
}
