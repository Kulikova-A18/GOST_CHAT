#include "../gost_chat.h"
#include "../export.h"

using namespace std;

using json = nlohmann::json;

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
std::string ReplaceString(
    std::string subject,
    const std::string& search,
    const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
    return subject;
}

void entrance_audit(
    std::string login,
    std::string password,
    std::string message)
{
    std::string file = "entrance.json";
    std::string line, text;


    std::ifstream _in(file);
    if (!_in.is_open()) {
        std::ofstream o(file);
        o.close();
    }

    std::ifstream in(file);
    if (in.is_open()) {
        while (getline(in, line)) {
            text += line;
        }
    }
    in.close();

    text = ReplaceString(text, "]", "");

    if (text.find("[") != std::string::npos) {
        std::ofstream o(file);
        o << text;
        o.close();
    }
    else {
        std::ofstream o(file);
        o << '[' << std::endl;
        o.close();
    }
    // conversion: person -> json
    std::ofstream o(file, std::ios::app);

    json j_entrance_person =
    {
        { "login", login },
        { "password" , password },
        { "message" , message}
    };
    o << std::setw(4) << j_entrance_person << ',' << std::endl;
    o << ']' << std::endl;
    o.close();
}

void entrance_person_audit(
    int id, 
    std::string surname, 
    std::string name, 
    std::string patronymic, 
    std::string message) 
{
    std::string file = "entrance_person.json";
    std::string line, text;

    std::ifstream _in(file);
    if (!_in.is_open()) {
        std::ofstream o(file);
        o.close();
    }

    std::ifstream in(file);
    if (in.is_open()) {
        while (getline(in, line)) {
            text += line;
        }
    }
    in.close();

    text = ReplaceString(text, "]", " ");

    if (text.find("[") != std::string::npos) {
        std::ofstream o(file);
        o << text << std::endl;
        o.close();
    }
    else {
        std::ofstream o(file);
        o << '[' << std::endl;
        o.close();
    }

    std::ofstream o(file, std::ios::app);
    json j_entrance_person =
    {
        { "id", id },
        { "surname" , surname },
        { "name" , name },
        { "patronymic" , patronymic },
        { "message" , message}
    };
    o << std::setw(4) << j_entrance_person << ',' << std::endl;
    o << ']' << std::endl;
    o.close();
}

std::string find_json(std::string _login, std::string _password) {
    const char* list_person [] = 
    {
        "Moiseev.json" ,
        "Zimin.json",
        "Isaev.json",
        "Guseva.json",
        "Bykova.json",          
        "Romanov.json",
        "Kulikova.json",
        "Doronina.json",
        "Doronin.json",
        "Kryukova.json"
    };

    json j;
    std::string username = "";
    std::string message = "";

    for (int i = 0; i < 8; i++) {
        std::ifstream in(list_person[i]);
        if (in.is_open()) {
            in >> j;
            auto conversion = j.get<ns_checking::person>();
            if (conversion.login == _login && conversion.password == _password) {
                username = conversion.name + conversion.surname;
                message = "successful login";
                entrance_person_audit(conversion.id, conversion.surname, conversion.name, conversion.patronymic, message);
            }
            if (conversion.login == _login && conversion.password != _password) {
                message = "Invalid password";
                entrance_person_audit(conversion.id, conversion.surname, conversion.name, conversion.patronymic, message);
            }
        }
        in.close();
    }

    return username;
}

int find(std::string argv1, std::string argv2) {
    _create_data_linux();

    // argv1 - login
    // argv2 - password
    std::string line, text;
    std::string file = "data.json";
    std::string message = "";

    std::ifstream in(file);
    if (in.is_open()) {
        while (getline(in, line)) {
            text += line;
        }
    }
    in.close();

    if (text.find(argv1) != std::string::npos 
        && text.find(argv2) != std::string::npos) 
    {
        find_json(argv1, argv2);
        message = "successfully";
        entrance_audit(argv1, argv2, message);
    }
    if (text.find(argv1) != std::string::npos
        && text.find(argv2) == std::string::npos)
    {
        find_json(argv1, argv2);
        message = "not successful";
        entrance_audit(argv1, argv2, message);
        return 1;
    }
    if (text.find(argv1) == std::string::npos
        && text.find(argv2) == std::string::npos)
    {
        message = "not successful";
        entrance_audit(argv1, argv2, message);
        return 2;
    }
    return 0;
}
