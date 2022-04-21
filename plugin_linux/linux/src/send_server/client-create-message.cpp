#include "../../gost_chat.h"

string message_text ="";
json j;

/*
 * 0 - создание ключа для шифрования (диффи хеллфман)
 * 1 - (зашифровано) проверка логина и пароля
 * 2 - (зашифровано) выдача ключа для симметричного шифрования
 * 3 - запись логов от клиента
*/

string create_handshake() {
    j =
        {
            { "sender", "client" },
            { "message" , "create keys" }
        };
    message_text = "0 " + j.dump();
    return message_text;
}

string check_authorization(string login, string password) {
    j =
        {
            { "sender", "client" },
            { "message" , "check authorization" },
            { "login", login },
            { "password" , password }
        };
    message_text = "1 " + j.dump();
    return message_text;
}

string get_symmetric_key() {
    j =
        {
            { "sender", "client" },
            { "message" , "get symmetric key" }
        };
    message_text = "2 " + j.dump();
    return message_text;
}

string get_log(string log) {
    j =
        {
            { "sender", "client" },
            { "message" , log }
        };
    message_text = "3 " + j.dump();
    return message_text;
}
