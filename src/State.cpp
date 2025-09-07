#include "State.hpp"
#include "TuringLog.hpp"


/**
 * generate a map from rule name to rule object
 */
std::map<std::string, Rule> State::p_genRuleMap(std::vector<Rule> rules) {
    std::map<std::string, Rule> map = std::map<std::string, Rule> {};
    for (std::vector<Rule>::iterator it = rules.begin(); it != rules.end(); ++ it) {
        map.emplace(it->ruleId, *it);
    }
    return map;
}

bool State::checkInput(std::vector<Tape> &tapes, std::string &destination) {
    for (std::map<std::string, Rule>::iterator it = this->rules.begin(); it != this->rules.end(); ++ it) {
        if (it->second.checkInput(tapes, destination, this->agnostic)) {
            it->second.operate(tapes);
            std::string msg = "match found in rule " + it->first;
            LOG(msg, RESULT);
            return true;
        }
    }
    std::string msg = "no match found in state " + this->name;
    LOG(msg, RESULT);
    return false;
}

const std::string &State::getName() {
    return this->name;
}