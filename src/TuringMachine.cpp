#include "TuringMachine.hpp"
#include "TuringLog.hpp"

void TuringMachine::setMaxIteration(int newVal) {
    this->maxIteration = newVal;
}

CheckStatus TuringMachine::p_executeOneCycle() {

    for (auto it = this->tapes.begin(); it != this->tapes.end(); ++ it) {
        LOG(it->readAll(), ALL);
    }

    State state = stateMap[currentState];
    std::string gotoState;

    // check if the current state and input has a valid destination 
    if (state.checkInput(tapes, gotoState)) {
        this->currentState = stateMap[gotoState].getName();
        CheckStatus status = stateMap[gotoState].status;
        std::string message = "Turing machine arrives at state " + this->currentState;
        LOG(message, RESULT);

        // no further action needed; execution has ended.
        if (status == ACCEPT || status == REJECT) {
            return status;
        }

        if (status == CONTINUE) {

            //stateMap[currentState].dostuff();
            return status;
        }
        return REJECT;

    }
    // no valid destination is found. 
    else {

        std::string message = "Turing machine has no valid destination at the current state " + state.getName();
        LOG(message, RESULT);
        return REJECT_NO_VALID_DESTINATION;
    }
}

CheckStatus TuringMachine::execute() {
    for (int i = 0; i < this->maxIteration; i ++) {
        CheckStatus res = p_executeOneCycle();
        switch (res) {
            case ACCEPT: 
                LOG("Input was accepted.", RESULT);
                return res;
            case REJECT:
            case REJECT_NO_VALID_DESTINATION:
                LOG("Input was rejected.", RESULT);
                return res;
            case CONTINUE:
                break;
            case TIMEOUT:
                LOG("Impossible switch case option", WARNING);
                break;
        }
    }
    LOG("Input failed to reach termination in given cycles.", RESULT);
    return TIMEOUT;
}

       
std::vector<State> TuringMachine::p_getRejectStates(std::vector<State> states) {

    std::vector<State> result = {};
        
    for (std::vector<State>::iterator it = states.begin(); it != states.end(); ++ it) {
        if (it->status == REJECT) {
            result.push_back(*it);
        }
    }
    return result;
}
        
std::vector<State> TuringMachine::p_getAcceptStates(std::vector<State> states) {
    std::vector<State> result = {};
        
    for (std::vector<State>::iterator it = states.begin(); it != states.end(); ++ it) {
        if (it->status == ACCEPT) {
            result.push_back(*it);
        }
    }
    return result;
}
        
std::map<std::string, State> TuringMachine::p_getStateMap(std::vector<State> states) {
    std::map<std::string, State> map = {};
        for (std::vector<State>::iterator it = states.begin(); it != states.end(); ++ it) {

        map.emplace(it->getName(), *it);
        
    }
    return map;
}


