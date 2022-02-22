#include "../gost_chat.h"
#include "../export.h"

using namespace std;

/*
list of return:

0 - successfully
1 - all variables are empty
*/

LIBRARY_API
int _sign_in_linux (char *argv1, char *argv2) {
    //_logger_void = "_sign_in_linux()";
    if (!argv1[0] && !argv2[0]) {
        //_logger(_logger_void,"all variables are empty");
        return 1;
    } 
    else 
    {
        int result = find(argv1, argv2);
        if (result == 1) {
            return 2;
        } 
        if (result == 2) {
            return 3;
        }
    }
    return 0;
}
