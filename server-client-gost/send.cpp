#include "client-gost.h"
#include "json.hpp"

ClassClientGostLog CLIENT_GOST_SEND_LOG;
ClassClientGost CLIENT_GOST_SEND_HASH;

using json = nlohmann::json;
using namespace std;

std::string message_text = "";
json j;

std::string ClassClientGost::check_authorization(std::string login, std::string password) {
    /* it's a hash*/
    std::string pw_password = password, pwhashed_password;
    CLIENT_GOST_SEND_HASH.create_password_hash(pw_password, pwhashed_password);

    j =
        {
            { "sender", "client" },
            { "message" , "check authorization" },
            { "login", login },
            { "password" , pwhashed_password },
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
        CLIENT_GOST_SEND_LOG.string_void = "ClassClientGost::get_authorization()";
        CLIENT_GOST_SEND_LOG.string_message = "is_open(): ERROR";
        CLIENT_GOST_SEND_LOG.logger();
        exit(0);
    }

    i << std::setw(4) << _json;
    i.close();
}
