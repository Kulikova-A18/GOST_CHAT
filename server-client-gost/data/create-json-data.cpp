#include "../server-gost.h"
#include "../json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

ClassServerGost SERVER_GOST_HASH;

// creating a database
std::string create_json = "data/data_workers.json";

std::string create_json_Kulikova    =   "data/Kulikova.json";
std::string create_json_Maximov     =   "data/Maximov.json";
std::string create_json_Konovalov   =   "data/Konovalov.json";

namespace ns_create {
    struct person {
        int id;                     // id employee
        std::string surname;        // surname employee
        std::string name;           // name employee
        std::string patronymic;     // patronymic employee
        std::string year_of_birth;  // year of birth employee
        std::string position;       // position employee
        std::string login;          // login employee
        std::string password;       // password employee
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
            { "password" , p.password },
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

void create_Kulikova() {
    /* it's a hash*/
    std::string pw_password = "c0WpF6iK", pwhashed_password;
    SERVER_GOST_HASH.create_password_hash(pw_password, pwhashed_password);

    ns_create::person p {0,"Kulikova", "Alyona","Vladimirovna","10/04/2000","developer","kulikova@gost_chat.com", pwhashed_password};
    json j = p;
        std::ofstream o(create_json_Kulikova);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Maximov() {
    /* it's a hash*/
    std::string pw_password = "d3WpF7iK", pwhashed_password;
    SERVER_GOST_HASH.create_password_hash(pw_password, pwhashed_password);

    ns_create::person p {1,"Maximov", "Oleg","Maksimovich","05/10/1999","developer","maximov@gost_chat.com", pwhashed_password};
    json j = p;
        std::ofstream o(create_json_Maximov);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Konovalov() {
    /* it's a hash*/
    std::string pw_password = "E2WpF6qK", pwhashed_password;
    SERVER_GOST_HASH.create_password_hash(pw_password, pwhashed_password);

    ns_create::person p {2,"Konovalov", "Grigory","Semenovich","01/07/1995","tester","konovalov@gost_chat.com", pwhashed_password};
    json j = p;
        std::ofstream o(create_json_Konovalov);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}

void ClassServerGost::create_all() {
    create_Kulikova();
    create_Maximov();
    create_Konovalov();
}
