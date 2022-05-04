#include "client-gost.h"
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

std::string message_text = "";
json j;

std::string ClassClientGost::check_authorization(std::string login, std::string password) {
    j =
        {
            { "sender", "client" },
            { "message" , "check authorization" },
            { "login", login },
            { "password" , password },
            { "response server" , "" },
        };
    message_text = j.dump();
    return message_text;
}

void ClassClientGost::get_authorization(std::string a) {
    std::string file = "client.json";
    ofstream i(file);
    json _json = json::parse(a);

    if(!i.is_open()) {
        exit(0);
    }
    i << std::setw(4) << _json;
    i.close();
}
