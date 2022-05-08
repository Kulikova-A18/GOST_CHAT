#include "../include/gost_chat.h"
#include "../include/export.h"

LIBRARY_API 
char *get_user() {
    std::ifstream ifs("client.json");
    json j = json::parse(ifs);
    std::string login     = j["login"].get<std::string>();

    char* result_argv;
    char* c = const_cast<char*>(login.c_str());
    result_argv = (char*) malloc(strlen(c)+1);
    strcpy(result_argv,c);

    return result_argv;
}
