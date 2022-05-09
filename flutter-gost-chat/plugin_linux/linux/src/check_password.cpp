#include "../include/gost_chat.h"
#include "../include/export.h"

using namespace std;

ClassClientGostLog CLIENT_GOST_CHECK_PASS_LOG;

bool isspecial(char c)
{
    return (c == '~' || c == '!' || c == '@' || c == '#' ||
            c == '$' || c == '%' || c == '^' || c == '&' ||
            c == '*' || c == '_' || c == '-' || c == '+' ||
            c == '=' || c == '|' || c == '\'' || c == '(' ||
            c == ')' || c == '{' || c == '}' || c == '[' ||
            c == ']' || c == ':' || c == '"' || c == '<' ||
            c == '>' || c == ',' || c == '.' || c == '?' ||
            c == '/');
}

LIBRARY_API
int _password_check_linux(char *password) {
    CLIENT_GOST_CHECK_PASS_LOG.string_void = "_password_check_linux()";

    int result_password_check = 0;

    bool hasSpace = false;          // store bool value
    int upperCharCounter = 0;       // store the int value
    int lowerCharCounter = 0;       // store the int value
    int digitCharCounter = 0;       // store the int value 
    int specialCharCounter = 0;     //store the int value

    // goes through the string password until the end
    for (int i = 0; i < strlen(password); i++) 
    {
        if (isspace(password[i])) {
            hasSpace = true;
        }
        // if any upper case letter found, upperCharCounter increment by 1
        else if (isupper(password[i])) {    
            upperCharCounter++;
        }
        // if any lower case letter found, lowerCharCounter increment by 1
        else if (islower(password[i])) {    
            lowerCharCounter++;
        }
        // if any digit is found, digitCharCounter increment by 1
        else if (isdigit(password[i])) {    
            digitCharCounter++;
        }
        // char should be special char, hence, specialCharCounter increment by 1
        else if(isspecial(password[i]) == true) {          
            specialCharCounter++;
        }
    }

    if (strlen(password) < 8) {
        // The password must be at least 8 characters long
        result_password_check = 2;

        CLIENT_GOST_CHECK_PASS_LOG.string_message = "The password must be at least 8 characters long";
        CLIENT_GOST_CHECK_PASS_LOG.logger();  
    }
    // check if bool is true, if so, execute statement below 
    else if (hasSpace != false) {  
        // Password must not contain space     
        result_password_check = 3; 

        CLIENT_GOST_CHECK_PASS_LOG.string_message = "Password must not contain space";
        CLIENT_GOST_CHECK_PASS_LOG.logger(); 
    }
    // check if upperCharCounter is equal to 0, if so, execute statement below
    else if (upperCharCounter == 0) { 
        // Password must contain at least 1 upper case letter       
        result_password_check = 4; 

        CLIENT_GOST_CHECK_PASS_LOG.string_message = "Password must contain at least 1 upper case letter";
        CLIENT_GOST_CHECK_PASS_LOG.logger(); 
    }
    // check if lowerCharCounter is equal to 0, if so, execute statement below
    else if (lowerCharCounter == 0) {  
        // Password must contain at least 1 lower case letter         
        result_password_check = 5; 

        CLIENT_GOST_CHECK_PASS_LOG.string_message = "Password must contain at least 1 lower case letter";
        CLIENT_GOST_CHECK_PASS_LOG.logger(); 
    }
    // check if digitCharCounter is equal to 0, if so, execute statement below
    else if (digitCharCounter == 0) {    
        // Password must contain at least 1 number       
        result_password_check = 6;

        CLIENT_GOST_CHECK_PASS_LOG.string_message = "Password must contain at least 1 number";
        CLIENT_GOST_CHECK_PASS_LOG.logger(); 
    }
    // check if digitCharCounter is equal to 0, if so, execute statement below
    else if (specialCharCounter != 0) {    
        // Password must contain at least 1 special character       
        result_password_check = 7; 

        CLIENT_GOST_CHECK_PASS_LOG.string_message = "Password must contain at least 1 special character";
        CLIENT_GOST_CHECK_PASS_LOG.logger(); 
    }
    else {
        result_password_check = 0;
    }

    return result_password_check;
}
