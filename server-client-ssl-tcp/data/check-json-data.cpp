#include "../server-gost.h"
#include "../json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

ClassServerGost SERVER_GOST_DATA;

std::string check_json = "data/data_workers.json";

std::string check_json_Kulikova    =   "data/Kulikova.json";
std::string check_json_Maximov     =   "data/Maximov.json";
std::string check_json_Konovalov   =   "data/Konovalov.json";
std::string check_json_Kiseleva    =   "data/Kiseleva.json";
std::string check_json_Voronin     =   "data/Voronin.json";
std::string check_json_Kasatkina   =   "data/Kasatkina.json";
std::string check_json_Homeland    =   "data/Homeland.json";
std::string check_json_Glebov      =   "data/Glebov.json";
std::string check_json_Grigoriev   =   "data/Grigoriev.json";
std::string check_json_Pavlov      =   "data/Pavlov.json";
std::string check_json_Antipova    =   "data/Antipova.json";
std::string check_json_Ilina       =   "data/Ilina.json";
std::string check_json_Klimov      =   "data/Klimov.json";
std::string check_json_Kulikov     =   "data/Kulikov.json";
std::string check_json_Ilkina      =   "data/Ilkina.json";
std::string check_json_Markov      =   "data/Markov.json";
std::string check_json_Popova      =   "data/Popova.json";
std::string check_json_Sidorov     =   "data/Sidorov.json";
std::string check_json_Siporov     =   "data/Siporov.json";
std::string check_json_Bogdanova   =   "data/Bogdanova.json";

namespace ns_checking {
    struct person {
        int id; // id employee
        std::string surname; // surname employee
        std::string name; // name employee
        std::string patronymic; // patronymic employee
        std::string year_of_birth; // year of birth employee
        std::string position; // position employee
        std::string login; // login employee
        std::string password; // password employee
    };

    void to_json(json& j, const person& p) {
        j = json
        {
            { "id", p.id },
            { "surname" , p.surname },
            { "name" , p.name },
            { "patronymic" , p.patronymic },
            { "year of birth" , p.year_of_birth },
            { "position" , p.position },
            { "login" , p.login },
            { "password" , p.password }

        };
    }
    void from_json(const json& j, person& p) {
        j.at("id").get_to(p.id);
        j.at("surname").get_to(p.surname);
        j.at("name").get_to(p.name);
        j.at("patronymic").get_to(p.patronymic);
        j.at("year of birth").get_to(p.year_of_birth);
        j.at("position").get_to(p.position);
        j.at("login").get_to(p.login);
        j.at("password").get_to(p.password);

    }
}

std::string ClassServerGost::check_data(std::string _message) {
    std::string _result = "";

    if(_message.empty()) {
        _result = "Invalid password";
    }

    json j_message = json::parse(_message);
    std::string _login = j_message["login"].get<std::string>();
    std::string _password = j_message["password"].get<std::string>();

    _result = SERVER_GOST_DATA._find(_login, _password);

    return _result;
}


#define length(array) ((sizeof(array)) / (sizeof(array[0])))

std::string ClassServerGost::find_json(std::string _login, std::string _password) {
    const char* list_person [] =
    {
        check_json_Kulikova.c_str(),
        check_json_Maximov.c_str(),
        check_json_Konovalov.c_str(),
        check_json_Kiseleva.c_str(),
        check_json_Voronin.c_str(),
        check_json_Kasatkina.c_str(),
        check_json_Homeland.c_str(),
        check_json_Glebov.c_str(),
        check_json_Grigoriev.c_str(),
        check_json_Pavlov.c_str(),
        check_json_Antipova.c_str(),
        check_json_Ilina.c_str(),
        check_json_Klimov.c_str(),
        check_json_Kulikov.c_str(),
        check_json_Ilkina.c_str(),
        check_json_Markov.c_str(),
        check_json_Popova.c_str(),
        check_json_Sidorov.c_str(),
        check_json_Siporov.c_str(),
        check_json_Bogdanova.c_str()
    };

    json j;
    std::string message = "";

    for (int i = 0; i < length(list_person); i++) {
        std::ifstream in(list_person[i]);
        if (in.is_open()) {
            in >> j;
            auto conversion = j.get<ns_checking::person>();
            if (conversion.login == _login && conversion.password == _password) {
                message = SIMMETRIC_KEY;
            }
            if (conversion.login == _login && conversion.password != _password) {
                message = "Invalid password";
            }
        }
        in.close();
    }

    return message;
}

std::string ClassServerGost::_find(std::string argv1, std::string argv2) {
    // argv1 - login
    // argv2 - password
    std::string line, text;
    std::string file = check_json;
    std::string message = "";

    std::ifstream in(file);
    if (in.is_open()) {
        while (getline(in, line)) {
            text += line;
        }
    }
    in.close();

    if (text.find(argv1) != std::string::npos && text.find(argv2) != std::string::npos) {
        message = SERVER_GOST_DATA.find_json(argv1, argv2);
    }
    if (text.find(argv1) == std::string::npos || text.find(argv2) == std::string::npos) {
        message = "Invalid password";
    }
    return message;
}
