#ifndef __TURINGMACHINE__
#define __TURINGMACHINE__

#include "State.hpp"
#include "Rule.hpp"
#include "Tape.hpp"


#define DEFAULT_MAX_ITERATION_COUNT 300

class TuringMachine {
    private:
        std::map<std::string, State> stateMap;
        std::vector<State> acceptStates;
        std::vector<State> rejectStates;
        State startState;
        std::string currentState = "";

        std::vector<Tape> tapes;

        std::vector<State> p_getRejectStates(std::vector<State> states);
        std::vector<State> p_getAcceptStates(std::vector<State> states);
        std::map<std::string, State> p_getStateMap(std::vector<State> states);
        CheckStatus p_executeOneCycle();
        
        int maxIteration = DEFAULT_MAX_ITERATION_COUNT;

    public: 

        std::string name = "Turing Machine";

        TuringMachine(std::vector<State> states, std::vector<Tape> tapes): 
        stateMap(p_getStateMap(states)), 
        acceptStates(p_getAcceptStates(states)),
        rejectStates(p_getRejectStates(states)),
        startState(states[0]),
        currentState(states[0].getName()),
        tapes(tapes) {}

        void setMaxIteration(int newVal);

        CheckStatus execute();

};

#endif