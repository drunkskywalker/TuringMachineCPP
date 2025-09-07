#include "Tape.hpp"
#include "TuringLog.hpp"

#include <iostream>

int main() {
    
    SET_VERBOSE(ALL);
    std::cout << "===============================================" << std::endl; 
    std::string initial = "abcdefg";
    Tape t0 = Tape(initial);

    std::cout << t0.getPosition() << std::endl;
    t0.moveLeft();
    t0.moveLeft();
    t0.write('9');
    std::cout << t0.read() << std::endl;
    std::cout << t0.getPosition() << std::endl;
    std::cout << t0.readAll() << std::endl;
    for (int i = 0; i < 10; i ++) {
        t0.moveRight();
    }
    std::cout <<t0.readAll() << std::endl;
    t0.write('x');
    std::cout <<t0.readAll() << std::endl;

    std::cout << "===============================================" << std::endl; 
    Tape t1 = Tape('@');
    t1.moveRight();
    t1.moveRight();
    std::cout << t1.readAll() << std::endl;
    t1.moveLeft();
    t1.moveLeft();
    t1.moveLeft();
    t1.moveLeft();
    t1.moveLeft();
    t1.write('a');
    std::cout << t1.readAll() << std::endl;
    
}