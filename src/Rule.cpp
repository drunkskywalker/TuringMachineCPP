#include "Rule.hpp"
#include "TuringLog.hpp"

bool Rule::checkInput(std::vector<Tape> &tapes, std::string &destination, char agnostic) {
    if (tapes.size() != this->match.size()) {
        LOG("number of input tapes does not equal to number of rule expected tapes", ERROR);
        return false;
    }
    std::vector<char>::iterator match_it;
    std::vector<Tape>::iterator input_it;
    for (
            match_it = this->match.begin(), input_it = tapes.begin(); 
            match_it != this->match.end() && input_it != tapes.end();
            ++ match_it, ++ input_it
        ) {
        if (*match_it != input_it->read() && *match_it != agnostic) {

            return false;
        }

    }

    destination = this->destination;
    return true;
}

bool Rule::operate(std::vector<Tape> &tapes){
    if (tapes.size() != this->operations.size()) {
        LOG("number of input tapes does not equal to number of operations", ERROR);
        return false;
    }
    std::vector<Operations>::iterator operation_it;
    std::vector<Tape>::iterator input_it;
    for (
            operation_it = this->operations.begin(), input_it = tapes.begin(); 
            operation_it != this->operations.end() && input_it != tapes.end();
            ++ operation_it, ++ input_it
        ) 
        {
            for (Operations::iterator op_it = operation_it->begin(); op_it != operation_it->end(); ++ op_it) {
                char old;
                switch(op_it->opCode) {
                    case L:
                        LOG("moving left...", ALL);
                        input_it->moveLeft();
                        break;
                    case R:
                        input_it->moveRight();
                        LOG("moving right...", ALL);
                        break;
                    case W:
                        input_it->write(op_it->toWrite);
                        LOG("Writing...", ALL);
                        break;
                    case P:
                        old = input_it->read();
                        old = old + 1;
                        input_it->write(old);
                        LOG("Incrementing...", ALL);
                        break;
                    case M:
                        old = input_it->read();
                        old = old - 1;
                        input_it->write(old);
                        LOG("Decrementing...", ALL);
                        break;
                }
            }
        }

    return true;
}