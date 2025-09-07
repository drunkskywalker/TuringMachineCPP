
#ifndef __STATE__
#define __STATE__

#include <vector>
#include <string>
#include <map>

#include "TuringLog.hpp"
#include "Rule.hpp"


#define DEFAULT_AGNOSTIC_CHAR '@'

enum CheckStatus {
    CONTINUE = 0,
    ACCEPT = 1,
    REJECT = 2,
    // not a valid status to be set for a state, but a global status
    REJECT_NO_VALID_DESTINATION = -1,
    TIMEOUT = -2
};

class State {

    private:
        std::string name;
        std::map<std::string, Rule> rules;
        char agnostic;


        std::map<std::string, Rule> p_genRuleMap(std::vector<Rule> rules);


    public:

        const CheckStatus status;

        
        State():State("placeholder", {}, DEFAULT_AGNOSTIC_CHAR, CONTINUE) {
            LOG("you are not supposed to be here: State class's default initializer invoked", ERROR);
        }
        State(std::string name, std::vector<Rule> rules): State(name, rules, DEFAULT_AGNOSTIC_CHAR, CONTINUE) {};
        State(std::string name, std::vector<Rule> rules, char agnostic, CheckStatus status): name(name), rules(p_genRuleMap(rules)), agnostic(agnostic), status(status) {}
       
        /**
         * returns true if a destination can be found. else return false.
         */
        bool checkInput(std::vector<Tape> &tapes, std::string &destination);

        const std::string &getName();


};

#endif