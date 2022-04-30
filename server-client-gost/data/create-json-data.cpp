#include "../server-gost.h"
#include "../json.hpp"
#include <fstream>

using json = nlohmann::json;
using namespace std;

// creating a database
std::string create_json = "data/data_workers.json";

std::string create_json_Kulikova    =   "data/Kulikova.json";
std::string create_json_Maximov     =   "data/Maximov.json";
std::string create_json_Konovalov   =   "data/Konovalov.json";
std::string create_json_Kiseleva    =   "data/Kiseleva.json";
std::string create_json_Voronin     =   "data/Voronin.json";
std::string create_json_Kasatkina   =   "data/Kasatkina.json";
std::string create_json_Homeland    =   "data/Homeland.json";
std::string create_json_Glebov      =   "data/Glebov.json";
std::string create_json_Grigoriev   =   "data/Grigoriev.json";
std::string create_json_Pavlov      =   "data/Pavlov.json";
std::string create_json_Antipova    =   "data/Antipova.json";
std::string create_json_Ilina       =   "data/Ilina.json";
std::string create_json_Klimov      =   "data/Klimov.json";
std::string create_json_Kulikov     =   "data/Kulikov.json";
std::string create_json_Ilkina      =   "data/Ilkina.json";
std::string create_json_Markov      =   "data/Markov.json";
std::string create_json_Popova      =   "data/Popova.json";
std::string create_json_Sidorov     =   "data/Sidorov.json";
std::string create_json_Siporov     =   "data/Siporov.json";
std::string create_json_Bogdanova   =   "data/Bogdanova.json";

namespace ns_create {
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

void create_Kulikova() {
    ns_create::person p {0,"Kulikova", "Alyona","Vladimirovna","10/04/2000","developer","kulikova@gost_chat.com","c0WpF6iK"};
    json j = p;
        std::ofstream o(create_json_Kulikova);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Maximov() {
    ns_create::person p {1,"Maximov", "Oleg","Maksimovich","05/10/1999","developer","maximov@gost_chat.com","d3WpF7iK"};
    json j = p;
        std::ofstream o(create_json_Maximov);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Konovalov() {
    ns_create::person p {2,"Konovalov", "Grigory","Semenovich","01/07/1995","tester","konovalov@gost_chat.com","E2WpF6qK"};
    json j = p;
        std::ofstream o(create_json_Konovalov);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Kiseleva() {
    ns_create::person p {3,"Kiseleva", "Amelia","Markovna","11/02/1993","team leader","kiseleva@gost_chat.com","0bKncWOJ"};
    json j = p;
        std::ofstream o(create_json_Kiseleva);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Voronin() {
    ns_create::person p {4,"Voronin", "Konstantin","Maksimovich","07/07/1994","technical manager","voronin@gost_chat.com","1eKneWOJ"};
    json j = p;
        std::ofstream o(create_json_Voronin);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Kasatkina() {
    ns_create::person p {5,"Kasatkina", "Amelia","Artemyevna","11/07/1990","developer","kasatkina@gost_chat.com","3bKcmWOJ"};
    json j = p;
        std::ofstream o(create_json_Kasatkina);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Homeland() {
    ns_create::person p {6,"Homeland", "Matvey","Timofeevich","15/11/2000","developer","homeland@gost_chat.com","IcxAOiMz"};
    json j = p;
        std::ofstream o(create_json_Homeland);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Glebov() {
    ns_create::person p {7,"Glebov", "Oleg","Yurievich","05/10/1995","team leader","glebov@gost_chat.com","Ic4A1iMz"};
    json j = p;
        std::ofstream o(create_json_Glebov);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Grigoriev() {
    ns_create::person p {8,"Grigoriev", "Oleg","Pavlovich","12/05/1991","developer","grigoriev@gost_chat.com","XEkB5grs"};
    json j = p;
        std::ofstream o(create_json_Grigoriev);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Pavlov() {
    ns_create::person p {9,"Pavlov", "Matvey","Alekseevich","10/02/2002","team leader","pavlov@gost_chat.com","WWqB3grs"};
    json j = p;
        std::ofstream o(create_json_Pavlov);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Antipova() {
    ns_create::person p {10,"Antipov", "Grigory","Maksimovich","11/02/1997","developer","antipova@gost_chat.com","U20tDVBH"};
    json j = p;
        std::ofstream o(create_json_Antipova);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Ilina() {
    ns_create::person p {11,"Ilina", "Daria","Artemyevna","11/01/2001","tester","ilina@gost_chat.com","UdRtDV23"};
    json j = p;
        std::ofstream o(create_json_Ilina);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Klimov() {
    ns_create::person p {12,"Klimov", "Sergey","Semenovich","01/01/1991","technical manager","ilina@gost_chat.com","vJ30VEgI"};
    json j = p;
        std::ofstream o(create_json_Klimov);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Kulikov() {
    ns_create::person p {13,"Kulikov", "Nikita","Pavlovich","20/01/1997","tester","kulikov@gost_chat.com","qJ60VEgI"};
    json j = p;
        std::ofstream o(create_json_Kulikov);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Ilkina() {
    ns_create::person p {14,"Ilkin", "Grigory","Alekseevich","01/12/1994","developer","ilkina@gost_chat.com","q73j9u6w"};
    json j = p;
        std::ofstream o(create_json_Ilkina);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Markov() {
    ns_create::person p {15,"Markov", "Sergey","Bogdanovich","12/04/1997","tester","markov@gost_chat.com","e71j2u6w"};
    json j = p;
        std::ofstream o(create_json_Markov);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Popova() {
    ns_create::person p {16,"Popova", "Daria","Vladimirovna","12/01/2000","developer","popova@gost_chat.com","c2GnAn3T"};
    json j = p;
        std::ofstream o(create_json_Popova);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Sidorov() {
    ns_create::person p {17,"Sidorov", "Dmitry","Timofeevich","01/04/1997","team leader","sidorov@gost_chat.com","C6re2FlM"};
    json j = p;
        std::ofstream o(create_json_Sidorov);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Siporov() {
    ns_create::person p {18,"Siporov", "Grigory","Timofeevich","01/04/1997","tester","siporov@gost_chat.com","FjNC5M2N"};
    json j = p;
        std::ofstream o(create_json_Siporov);
        o << std::setw(4) << j;
        o.close();

        std::ofstream d(create_json, std::ios::app);
        d << std::setw(4) << j << "\n";
        d.close();
}
void create_Bogdanova() {
    ns_create::person p {19,"Bogdanova", "Amelia","Vladimirovna","10/04/2000","tester","bogdanova@gost_chat.com","3jfC5M2N"};
    json j = p;
        std::ofstream o(create_json_Bogdanova);
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
    create_Kiseleva();
    create_Voronin();
    create_Kasatkina();
    create_Homeland();
    create_Glebov();
    create_Grigoriev();
    create_Pavlov();
    create_Antipova();
    create_Ilina();
    create_Klimov();
    create_Kulikov();
    create_Ilkina();
    create_Markov();
    create_Popova();
    create_Sidorov();
    create_Siporov();
    create_Bogdanova();
}
