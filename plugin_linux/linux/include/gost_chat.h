#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <ctime>
#include <time.h>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <clocale>

#ifdef _WIN32
#include <Windows.h>
#include <conio.h>
#endif

#include "json.hpp"

int _cleaning_logger_linux();
const std::string currentDateTime();
int _logger_linux(char* argv1, char* argv2);

//Creating elliptic curve (x25519) cryptography key pairs
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <cstdio>

using json = nlohmann::json;

#define PORT     8080
#define MAXLINE 1024

using namespace std;

int create_EVP_PKEY(char * a);
string create_handshake();
string check_authorization(string login, string password);
string get_symmetric_key();
string get_log(string log);
int create_autorization(char *a);
char *create_symmetric_key(char *a);

/*
int _create_data_linux();
void create_Moiseev();
void create_Zimin();
void create_Guseva();
void create_Bykova();
void create_Romanov();
void create_Kulikova();
void create_Doronina();
void create_Doronin();
void create_Kryukova();
std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
void entrance_audit(std::string login, std::string password, std::string message);
void entrance_person_audit(int id, std::string surname, std::string name, std::string patronymic, std::string message);
std::string find_json(std::string _login, std::string _password);
int find(std::string argv1, std::string argv2);
*/

// event logging
class Class_Logger
{
    public:
        std::string string_void;
        std::string string_message;
        std::string file_name = "/home/alyona/gost-chat-server/server-gost-chat.log";

        void logger_server()
        {
            time_t     now = time(0);
            struct tm  tstruct;
            char       buf[80];
            tstruct = *localtime(&now);
            strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

            ofstream o(file_name,ios::ate|ios::out|ios::app);
            o << buf << " " << string_void << " " << string_message << std::endl;
            o.close();

            // print from terminal
            printf("%s %s %s\n", buf, string_void.c_str(), string_message.c_str());
        }
};