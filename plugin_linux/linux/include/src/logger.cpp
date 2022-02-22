#include "../gost_chat.h"
#include "../export.h"

using namespace std;

int _cleaning_logger_linux() {
    ofstream o("st_client_gui.log");
    return 0;
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}


int _logger_linux(char* argv1, char* argv2) {
    if (!argv1[0] && !argv2[0])
        return 1;
    else {
        ofstream o("gost_chat.log", ios::ate | ios::out | ios::app);
        o << currentDateTime() << " " << argv1 << " " << argv2 << std::endl;
    }
    return 0;
}