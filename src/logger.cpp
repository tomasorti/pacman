#include <sys/time.h>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdarg>

#include "logger.h"

Logger* Logger::instance_ = 0;
std::ofstream Logger::logfile_;
std::string Logger::filename_ = "output.log";

Logger& Logger::getLogger()
{
    if (instance_ == 0) {
        instance_ = new Logger();
        logfile_.open(filename_.c_str(), std::ios::out | std::ios::app);
    }
    return *instance_;
}

int Logger::_vscprintf(const char* format, va_list pargs)
{ 
    int retval; 
    va_list argcopy;
    va_copy(argcopy, pargs); 
    retval = vsnprintf(NULL, 0, format, argcopy); 
    va_end(argcopy); 
    return retval;
}
 
void Logger::log(const std::string& message)
{
    logfile_ <<  currentDateTime() << ": ";
    logfile_ << message << "\n";
}

void Logger::log(const char* format, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);

    logfile_ << currentDateTime() << ": ";
    logfile_ << buffer << "\n";
    va_end(args);
}
 
Logger& Logger::operator<<(const std::string& message)
{
    logfile_ << "\n" << currentDateTime() << ": ";
    logfile_ << message << "\n";
    return *this;
}

const std::string Logger::currentDateTime()
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    int millisec = lrint(tv.tv_usec/1000.0); // Round to nearest millisec
    if (millisec >= 1000) { // Allow for rounding up to nearest second
        millisec -=1000;
        tv.tv_sec++;
    }

    struct tm* mytime;
    mytime = std::localtime(&tv.tv_sec);

    char buf[25];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", mytime);

    char dateTime[50];
    sprintf(dateTime, "%s.%03d", buf, millisec);
    return dateTime;
}
