

#ifndef __RULE__
#define __RULE__


#include <vector>
#include <string>

#include "Tape.hpp"

enum OPCODE {
    L = 0,
    R = 1,
    W = 2,
    P = 3,
    M = 4
};

typedef struct OP {
    OPCODE opCode;
    char toWrite;
} OP;

typedef std::vector<OP> Operations;

class Rule {



        public:

            const std::string ruleId;

        private:
            std::vector<char> match;
            std::string start;
            std::string destination;
            std::vector<Operations> operations;
        public:

            Rule(std::vector<char> matchIn, std::string start, std::string destination, std::vector<Operations> operations): 
                ruleId(std::string(matchIn.begin(), matchIn.end())),
                match(matchIn), 
                start(start),
                destination(destination), 
                operations(operations) {}

            Rule(const Rule &rhs): Rule(rhs.match, rhs.start, rhs.destination, rhs.operations) {}

            bool checkInput(std::vector<Tape> &tapes, std::string &destination, char agnostic);

            bool operate(std::vector<Tape> &tapes);


};

#endif