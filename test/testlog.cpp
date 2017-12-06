#include "logger.h"
#include <string>
#include <cstdio>

int main() {
    
    Logger::getLogger().log("message to be logged");
    std::string message1 = "logg message 1 ...";
    Logger::getLogger().log(message1);

    int    nNum = 10;
    std::string message2 = "abracadabra";
    LOGGER.log("Password is:%s | Number is:%d | other: %s", message2.c_str(), nNum, "surprise");

    return 0;   
}
