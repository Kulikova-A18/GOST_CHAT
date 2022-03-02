#include "../gost_chat.h"
#include "../export.h"

using json = nlohmann::json;

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

void create_Moiseev() {
    ns_create::person p {0,"Moiseev", "Samuil","Yulianovich","01/07/1995","tester","moiseev@gost_chat.ru","2CEBsDWZpJui0t"};
    json j = p;
    std::ofstream o("Moiseev.json");
    o << std::setw(4) << j;
    o.close();
    
    std::ofstream d("data.json", std::ios::app);
    d << std::setw(4) << j;
    d.close();
}
void create_Zimin() {
    ns_create::person p {1,"Zimin", "Varlaam","Danilovich","11/07/1990","developer","zimin@gost_chat.ru","td5EdLseze2r9y"};
    json j = p;
    std::ofstream o("Zimin.json");
    o << std::setw(4) << j;
    o.close(); 
    
    std::ofstream d("data.json", std::ios::app);
    d << std::setw(4) << j << ",";
    d.close();
}
void create_Guseva() {
    ns_create::person p {2,"Guseva", "Eris","Davidovna","17/01/1998","technical manager","guseva@gost_chat.ru","UQMdK2KMidq9wi"};
    json j = p;
    std::ofstream o("Guseva.json");
    o << std::setw(4) << j;
    o.close();
    
    std::ofstream d("data.json", std::ios::app);
    d << std::setw(4) << j << ",";
    d.close();
}
void create_Bykova() {
    ns_create::person p {3,"Bykova", "Faya","Stanislavovna","05/10/1993","developer","bykova@gost_chat.ru","BprrD0jmhHMEwE"};
    json j = p;
    std::ofstream o("Bykova.json");
    o << std::setw(4) << j;
    o.close();
    
    std::ofstream d("data.json", std::ios::app);
    d << std::setw(4) << j << ",";
    d.close();
}
void create_Romanov() {
    ns_create::person p {4,"Romanov", "Akim","Aleksandrovich","05/10/1999","developer","romanov@gost_chat.ru","tUf99axPMTvBhB"};
    json j = p;
    std::ofstream o("Romanov.json");
    o << std::setw(4) << j;
    o.close();
    
    std::ofstream d("data.json", std::ios::app);
    d << std::setw(4) << j << ",";
    d.close();
}
void create_Kulikova() {
    ns_create::person p {5,"Kulikova", "Alyona","Vladimirovna","10/04/2000","developer","kulikova@gost_chat.ru","BprrD7jmhHEEwE"};
    json j = p;
    std::ofstream o("Kulikova.json");
    o << std::setw(4) << j;
    o.close();
    
    std::ofstream d("data.json", std::ios::app);
    d << std::setw(4) << j << ",";
    d.close();
}
void create_Doronina() {
    ns_create::person p {6,"Doronina", "Sasha","Vladimirovna","1/04/1997","tester","dorina@gost_chat.ru","Bpr1D7jmhHEEwE"};
    json j = p;
    std::ofstream o("Doronina.json");
    o << std::setw(4) << j;
    o.close();
    
    std::ofstream d("data.json", std::ios::app);
    d << std::setw(4) << j << ",";
    d.close();
}
void create_Doronin() {
    ns_create::person p {7,"Doronin", "Maxim","Vladimirov","1/04/1997","team leader","dorin@gost_chat.ru","Bp12D7jmhHEEwE"};
    json j = p;
    std::ofstream o("Doronin.json");
    o << std::setw(4) << j;
    o.close();
    
    std::ofstream d("data.json", std::ios::app);
    d << std::setw(4) << j << ",";
    d.close();
}
void create_Kryukova() {
    ns_create::person p {8,"Kryukova", "Alyona","Vladimirovna","10/04/2000","developer","kryukova@gost_chat.ru","Bp17D7jmhHEEwE"};
    json j = p;
    std::ofstream o("Kryukova.json");
    o << std::setw(4) << j;
    o.close();
    
    std::ofstream d("data.json", std::ios::app);
    d << std::setw(4) << j << ",";
    d.close();
}


int _create_data_linux() {
    create_Moiseev();
    create_Zimin();
    create_Guseva();
    create_Bykova();
    create_Romanov();
    create_Kulikova();
    create_Doronina();
    create_Doronin();
    create_Kryukova();
    return 0;
}
