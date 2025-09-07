#include <time.h>

#include "TuringLog.hpp"


void TuringLog::log(std::string msg, LOG_LEVEL lvl) {
    if (lvl <= TuringLog::logLevel || lvl == RESULT) {
        std::string lvlString = "";
        switch(lvl) {
            
            case ERROR:
            lvlString = "ERROR";
            break;
            case WARNING:
            lvlString = "WARNING";
            break;
            case INFO:
            lvlString = "INFO";
            break;
            case ALL:
            lvlString = "ALL";
            break;
            case RESULT:
            lvlString = "RESULT";
            case NONE:
            break;
        }

        std::cout << "[" << lvlString << "] ";
        if (TuringLog::logLevel == ALL) {
            std::cout << time(NULL) << " ";
        }
        std::cout << msg << std::endl;
    }
}

void TuringLog::setVerbose(LOG_LEVEL lvl) {
    TuringLog::logLevel = lvl;
}

LOG_LEVEL TuringLog::logLevel = WARNING;