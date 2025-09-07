
#ifndef __TURING_LOG__
#define __TURING_LOG__


#include <string>
#include <iostream>

#define LOG TuringLog::log
#define SET_VERBOSE(a) TuringLog::setVerbose(a);

typedef enum LOG_LEVEL {
    RESULT = -2,
    NONE = -1,
    ERROR = 1,
    WARNING = 2,
    INFO = 3,
    ALL = 4
} LOG_LEVEL;


class TuringLog {
    private:
        static LOG_LEVEL logLevel;
    public:
        static void log(std::string msg, LOG_LEVEL lvl);
        static void setVerbose(LOG_LEVEL lvl);


};

#endif