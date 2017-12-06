#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

#define LOGGER Logger::getLogger()

class Logger
{
public:
    static Logger& getLogger();

    void log(const std::string& sMessage);

    // Variable Length Logger function
    void log(const char* format, ...);

    // << overloaded function to Logs a message
    Logger& operator<<(const std::string& sMessage);


private:
    Logger() {}
    Logger(const Logger&) {};             // copy constructor is private
    Logger& operator=(const Logger&) { return *this; };  // assignment operator is private

    int _vscprintf(const char * format, va_list pargs);
    const std::string currentDateTime();
    
    static Logger* instance_;
    static std::ofstream logfile_;
    static std::string filename_;
};
#endif
