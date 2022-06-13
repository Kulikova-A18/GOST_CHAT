#include "../include/gost_chat.h"
#include "../include/export.h"

ClassClientGost CLIENT_GOST_MESSAGE;
ClassClientGostLog CLIENT_GOST_MESSAGE_LOG;

std::string result_key(char *key_text) {
    std::string result = "", string_text = key_text;

    //kulikova@gost_chat.com
    if(string_text.find("[kulikova@gost_chat.com from maximov@gost_chat.com]") != std::string::npos) {
        std::ifstream ifs("client.json");
        json j = json::parse(ifs);
        std::string key     = j["maximov"].get<std::string>();
        result = key;
    }
    else if(string_text.find("[kulikova@gost_chat.com from konovalov@gost_chat.com]") != std::string::npos) {
        std::ifstream ifs("client.json");
        json j = json::parse(ifs);
        std::string key     = j["konovalov"].get<std::string>();
        result = key;
    }
    
    //maximov@gost_chat.com
    else if(string_text.find("[maximov@gost_chat.com from kulikova@gost_chat.com]") != std::string::npos) {
        std::ifstream ifs("client.json");
        json j = json::parse(ifs);
        std::string key     = j["kulikova"].get<std::string>();
        result = key;
    }
    else if(string_text.find("[maximov@gost_chat.com from konovalov@gost_chat.com]") != std::string::npos) {
        std::ifstream ifs("client.json");
        json j = json::parse(ifs);
        std::string key     = j["konovalov"].get<std::string>();
        result = key;
    }
    
    //konovalov@gost_chat.com
    else if(string_text.find("[konovalov@gost_chat.com from maximov@gost_chat.com]") != std::string::npos) {
        std::ifstream ifs("client.json");
        json j = json::parse(ifs);
        std::string key     = j["maximov"].get<std::string>();
        result = key;
    }
    else if(string_text.find("[konovalov@gost_chat.com from kulikova@gost_chat.com]") != std::string::npos) {
        std::ifstream ifs("client.json");
        json j = json::parse(ifs);
        std::string key     = j["kulikova"].get<std::string>();
        result = key;
    }

    else {
        std::ifstream ifs("client.json");
        json j = json::parse(ifs);
        std::string key     = j["response server"].get<std::string>();
        result = key;
    }

    return result;
}

LIBRARY_API 
int encrypted_message(char *text) {
    setbuf(stdout, NULL);
    try
    {
        try 
        {
            /* get data (login and password) */
            std::ifstream ifs("client.json");
            json j = json::parse(ifs);
            //std::string key     = j["response server"].get<std::string>();
            std::string key     = result_key(text);
            std::string login   = j["login"].get<std::string>();
            
            /* A 256 bit key */
            char strcpy_key[1024] = {0};
            sprintf(strcpy_key, "%s", key.c_str());

            /* create a message form */
            std::string message_text = "";
            j =
                {
                    { "sender", login },
                    { "message" , text }
                };
            message_text = j.dump();
            char ac_client_request[1024] = {0};
            sprintf(ac_client_request, "%s", message_text.c_str());

            /*create secret key - SHARED SECRET*/
            unsigned char secretKey[AES_BLOCK_SIZE * 2] = {0,}; //32
            unsigned char salt[] = {'G','O','S','T','-','C','H','A','T','G','O','S','T'}; // "GOST-CHAT"
            unsigned char *iv = (unsigned char *)"0123456789012345"; /* A 128 bit IV */
            PKCS5_PBKDF2_HMAC_SHA1((const char *)strcpy_key, strlen((char *)strcpy_key),
                              salt, sizeof(salt), 20000 , AES_BLOCK_SIZE * 2, (unsigned char *)secretKey);

            unsigned char *ciphertext;
            size_t plain_len_2 = strlen ((char *)ac_client_request);
            ciphertext = new unsigned char[plain_len_2 + AES_BLOCK_SIZE];
            int ciphertext_len;
            /* Encrypt the plaintext */
            ciphertext_len = CLIENT_GOST_MESSAGE.encrypt((unsigned char *)ac_client_request,
                                            strlen ((char *)ac_client_request), (unsigned char *)secretKey,
                                            iv, ciphertext);

            /* print bio */
            cout << endl;
            BIO_dump_fp (stdout, (const char *)ciphertext, strlen((char *)ciphertext));

            /* send a message broadcast */
            char ac_system[1024] = {0};
            sprintf(ac_system, "echo -n \"%s\" | socat - udp-datagram:255.255.255.255:48654,broadcast", ciphertext);
            system(ac_system);
        }    
        catch (json::parse_error& e)
        {
            CLIENT_GOST_MESSAGE_LOG.string_void = "";
            // output exception information
            char ac[1024] = {0};
            sprintf(ac, "message: %s\nexception id: %s\nbyte position of error: %s", e.what(), e.id, e.byte);
            CLIENT_GOST_MESSAGE_LOG.string_message = ac;
            CLIENT_GOST_MESSAGE_LOG.logger();
        }
    }
    catch(...)
    {
        throw;
    }
    
    return 0;
}

LIBRARY_API 
int decipher_message(char *text) {
    setbuf(stdout, NULL);
    try 
    {    
        try 
        {
            /* get data (login and password) */
            std::ifstream ifs("client.json");
            json j = json::parse(ifs);
            std::string key     = j["response server"].get<std::string>();
            
            /* A 256 bit key */
            char strcpy_key[key.length() + 1];
            strcpy(strcpy_key, key.c_str());

            /*create secret key - SHARED SECRET*/
            unsigned char secretKey[AES_BLOCK_SIZE * 2] = {0,}; //32
            unsigned char salt[] = {'G','O','S','T','-','C','H','A','T'}; // "GOST-CHAT"
            unsigned char *iv = (unsigned char *)"0123456789012345"; /* A 128 bit IV */
            PKCS5_PBKDF2_HMAC_SHA1((const char *)strcpy_key, strlen((char *)strcpy_key),
                                            salt, sizeof(salt),
                                            20000 , AES_BLOCK_SIZE * 2, (unsigned char *)secretKey);

            size_t plain_len = strlen ((char *)text);
            /* Buffer for the decrypted text */
            unsigned char *decryptedtext;
            decryptedtext = new unsigned char[plain_len + AES_BLOCK_SIZE];
            /* fill buffer with zeros */
            memset(decryptedtext,0,plain_len + AES_BLOCK_SIZE);
            int decryptedtext_len;
            /* Decrypt the ciphertext */
            decryptedtext_len = CLIENT_GOST_MESSAGE.decrypt((unsigned char *)text,
                                                    strlen((char *)text), secretKey, iv, decryptedtext);
            /* Add a NULL terminator. We are expecting printable text */
            decryptedtext[decryptedtext_len] = '\0';
            
            char ac_decryptedtext[1024] = {0};
            sprintf(ac_decryptedtext, "%s", decryptedtext);

            /* print bio */
            BIO_dump_fp (stdout, (const char *)ac_decryptedtext, strlen((char *)ac_decryptedtext));
            
            std::string file = "get_message.json";
            ofstream i(file);
            j = json::parse(ac_decryptedtext);

            i << std::setw(4) << j;
        }    
        catch (json::parse_error& e)
        {
            // output exception information
            std::cout << "message: " << e.what() << '\n'
                        << "exception id: " << e.id << '\n'
                        << "byte position of error: " << e.byte << std::endl;
        }
    }
    catch(...)
    {
        throw;
    }
    return 0;
}

LIBRARY_API 
char *get_sender() {
    char* result_argv;
    std::string a = "", line;
    std::ifstream in("get_message.json");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            a += line;
        }
    }
    in.close();
    if(a.find("{") != std::string::npos) {
        
        try
        {
            std::ifstream ifs("get_message.json");
            json j = json::parse(ifs);
            std::string sender     = j["sender"].get<std::string>();

            char* c = const_cast<char*>(sender.c_str());
            result_argv = (char*) malloc(strlen(c)+1);
            strcpy(result_argv,c);
        }
        catch (json::parse_error& e)
        {
            // output exception information
            std::cout << "message: " << e.what() << '\n'
                        << "exception id: " << e.id << '\n'
                        << "byte position of error: " << e.byte << std::endl;
        }
        // ofstream rewrite("get_message.json");
        // rewrite.write("", 0);
        // rewrite.close();
        return result_argv;
    }

    return (char *)" ";
}

LIBRARY_API 
char *get_message() {
    char* result_argv;
    std::string a = "", line;
    std::ifstream in("get_message.json");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            a += line;
        }
    }
    in.close();

    if(a.find("{") != std::string::npos) {
        try
            {  
                std::ifstream ifs("get_message.json");
                json j = json::parse(ifs);
                std::string message     = j["message"].get<std::string>();
            
                char* c = const_cast<char*>(message.c_str());
                result_argv = (char*) malloc(strlen(c)+1);
                strcpy(result_argv,c);
            }
            catch (json::parse_error& e)
            {
                // output exception information
                std::cout << "message: " << e.what() << '\n'
                            << "exception id: " << e.id << '\n'
                            << "byte position of error: " << e.byte << std::endl;
            }

            // ofstream rewrite("get_message.json");
            // rewrite.write("", 0);
            // rewrite.close();
        return result_argv;
    }
    
    return (char *)" ";
}
