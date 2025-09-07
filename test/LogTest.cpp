#include "TuringLog.hpp"

#include <string>
#include <vector>

int main() {

    std::cout << "initial lvl: WARNING" << std::endl;
    LOG("this line should print", WARNING);
    LOG("this line should print", ERROR);
    LOG("this line should not print", ALL);
    
    std::cout << "current lvl: NONE" << std::endl;
    SET_VERBOSE(NONE);
    LOG("this line should not print", NONE);
    LOG("this line should not print", ERROR);
    LOG("this line should not print", ALL);
    LOG("this line should print", RESULT);
    
    std::cout << "current lvl: ERROR" << std::endl;
    SET_VERBOSE(ERROR);

    LOG("this line should print", ERROR);
    LOG("this line should not print", ALL);
    
    std::cout << "current lvl: ALL" << std::endl;
    SET_VERBOSE(ALL);
    LOG("this line should print", ERROR);
    LOG("this line should print", WARNING);
    LOG("this line should print", INFO);
    LOG("this line should print", ALL);

    return 0;
}