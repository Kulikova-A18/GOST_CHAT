#include "server-gost.h"

#include "json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

ClassServerGost SERVER_GOST_SEND;

std::string message_text = "";
json j;

std::string ClassServerGost::check_authorization(std::string login, std::string password, std::string response) {
    if(login == "kulikova@gost_chat.com") {
        j =
            {
                { "sender", "server" },
                { "message" , "response server" },
                { "login", login },
                { "password" , password },
                { "response server" , response },
                { "kulikova" , "" },
                { "maximov" , KULIKOVA_MAXIMOV },
                { "konovalov" , KULIKOVA_KONOVALOV },
            };
    }
    else if(login == "maximov@gost_chat.com") {
        j =
            {
                { "sender", "server" },
                { "message" , "response server" },
                { "login", login },
                { "password" , password },
                { "response server" , response },
                { "kulikova" , KULIKOVA_MAXIMOV },
                { "maximov" , "" },
                { "konovalov" , MAXIMOV_KONOVALOV },
            };
    }
    else if(login == "konovalov@gost_chat.com") {
        j =
            {
                { "sender", "server" },
                { "message" , "response server" },
                { "login", login },
                { "password" , password },
                { "response server" , response },
                { "kulikova" , KULIKOVA_KONOVALOV },
                { "maximov" , MAXIMOV_KONOVALOV },
                { "konovalov" , "" },
            };
    }
    else {
        j =
            {
                { "sender", "server" },
                { "message" , "response server" },
                { "login", login },
                { "password" , password },
                { "response server" , response },
            };
    }
    message_text = j.dump();
    return message_text;
}

std::string ClassServerGost::check_json_message(char *message) {
    try
    {
        std::string response = "";
        if(message[0] == '{') {
            j = json::parse(message);

            std::string LOGIN               = j["login"].get<std::string>();
            std::string PASSWORD            = j["password"].get<std::string>();

            response = SERVER_GOST_SEND.check_data(message);
            response = SERVER_GOST_SEND.check_authorization(LOGIN, PASSWORD, response);
        }
        return response;
    }
    catch (json::parse_error& e)
    {
        // output exception information
        std::cout << "message: " << e.what() << '\n'
                    << "exception id: " << e.id << '\n'
                    << "byte position of error: " << e.byte << std::endl;
    }
}
