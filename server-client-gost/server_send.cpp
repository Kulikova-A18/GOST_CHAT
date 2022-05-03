#include "server-gost.h"

#include "json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

ClassServerGost SERVER_GOST_SEND;

std::string message_text = "";
json j;

std::string ClassServerGost::check_authorization(std::string login, std::string password, std::string response) {
    j =
        {
            { "sender", "server" },
            { "message" , "response server" },
            { "login", login },
            { "password" , password },
            { "response server" , response },
        };
    message_text = j.dump();
    return message_text;
}

std::string ClassServerGost::check_json_message(char *message) {
    j = json::parse(message);

    std::string LOGIN               = j["login"].get<std::string>();
    std::string PASSWORD            = j["password"].get<std::string>();

    std::string response = "";
    response = SERVER_GOST_SEND.check_data(message);
    response = SERVER_GOST_SEND.check_authorization(LOGIN, PASSWORD, response);
    return response;
}
