#ifndef __TAPE__
#define __TAPE__

#include <vector>
#include <string>


#define DEFAULT_EMPTY_CHAR '_'

class Tape {

    private:
        std::vector<char> rightTape;
        std::vector<char> leftTape;
        int pos;
        char emptyChar;

        void p_initTapes(std::string initial);
    
    public:
        Tape(): Tape("", DEFAULT_EMPTY_CHAR) {}

        Tape(const std::string& initial): Tape(initial, DEFAULT_EMPTY_CHAR) {}

        Tape(char emptyChar): Tape("", emptyChar) {}

        Tape(const std::string& initial, char emptyChar): rightTape(), leftTape(), pos(0), emptyChar(emptyChar) {
            p_initTapes(initial);
        }

        void moveLeft();
        void moveRight();
        char read();
        void write(char toWrite);


        int length();
        int getPosition();
        std::string readAll();

};

#endif