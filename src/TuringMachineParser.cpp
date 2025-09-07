#include <fstream>
#include <algorithm>

#include "TuringMachineParser.hpp"
#include "TuringLog.hpp"



bool TuringMachineParser::p_parseFile() {
    
    std::ifstream f(fname);
    if (!f.is_open()) {
        LOG("error opening file", ERROR);
        return false;
    }
    data = json::parse(f);
    if (data.is_discarded()) {
        LOG("error parsing file", ERROR);
        return false;
    }
    return true;
}

bool TuringMachineParser::p_validate() {

    if (!p_validateParamNum()) {
        return false;
    }

    if (!p_validateGroundRules()) {
        return false;
    }

    if (!p_validateState()) {
        return false;
    }

    if (!p_validateTape()) {
        return false;
    }

    return true;
}


bool TuringMachineParser::p_validateParamNum() {
    if (data["alphabet"] == nullptr) {
        LOG("alphabet not found in machine definition", ERROR);
        return false;
    }
    if (data["tapenum"] == nullptr) {
        LOG("tape number not found in machine definition", ERROR);
        return false;
    }
    if (data["states"] == nullptr) {
        LOG("states not found in machine definition", ERROR);
        return false;
    }
    if (data["accept_states"] == nullptr) {
        LOG("accept states not found in machine definition", ERROR);
        return false;
    }
    if (data["reject_states"] == nullptr) {
        LOG("reject states not found in machine definition", ERROR);
        return false;
    }
    if (data["rules"] == nullptr) {
        LOG("rules not found in machine definition", ERROR);
        return false;
    }

    LOG("All required parameters are provided.", INFO);
    return true;

}

/**
 * @brief validate ground rules and settings of the turing machine.
 */
bool TuringMachineParser::p_validateGroundRules() {

    // verify alphabet. 
    if (!data["alphabet"].is_array()) {
        return false;
    }
    for (auto i : data["alphabet"]) {
        if (!i.is_string()) {
            return false;
        }
        if (i.get<std::string>().length() != 1 ){
            return false;
        }
        // duplicate items will be ignored
        else {
            this->alphabet.insert(i.get<std::string>().at(0));
        }
    }

    LOG("Alphabet created.", INFO);

    /*=========================================================*/

    if (!data["tapenum"].is_number_integer()) {
        return false;
    }
    else {
        int i = data["tapenum"].get<int>();
        if (i < 1) {
            return false;
        }
        this->tapenum = i;
    }

    LOG("tape number validated.", INFO);

    /*=========================================================*/

    if (data["name"] != nullptr && data["name"].is_string()) {
        std::string name = data["name"].get<std::string>();
        this->name = name;
    } 
    else {
        this->name = "Turing Machine";
        if (data["name"] == nullptr) {
            LOG("turing machine name not provided. ", INFO);
        }
        else {
            LOG("turing machine name cannot be recognized. Any other type other than string provided in name field will be ignored. ", INFO);
        }
    }

    /*=========================================================*/

    if (data["blank"] != nullptr && data["blank"].is_string()) {
        std::string blank = data["blank"].get<std::string>();
        if (blank.length() == 1) {
            this->blank = blank.at(0);            
        }
        else {
            this->blank = '_';
            LOG("wrong length provided in blank field - expects 1.", INFO);
        }
    }
    else {
        this->blank = '_';
        if (data["blank"] == nullptr) {
            LOG("blank char not provided. ", INFO);
        }
        else {
            LOG("blank char cannot be recognized. Must be a string of length 1.", INFO);
        }
    }
    this->alphabet.emplace(this->blank);

    /*=========================================================*/

        if (data["agnostic"] != nullptr && data["agnostic"].is_string()) {
        std::string agnostic = data["agnostic"].get<std::string>();
        if (agnostic.length() == 1) {
            this->agnostic = agnostic.at(0);            
        }
        else {
            this->agnostic = '@';
            LOG("wrong length provided in agnostic field - expects 1.", INFO);
        }
    }
    else {
        this->agnostic = '@';
        if (data["agnostic"] == nullptr) {
            LOG("agnostic char not provided. ", INFO);
        }
        else {
            LOG("agnostic char cannot be recognized. Must be a string of length 1.", INFO);
        }
    }
    this->alphabet.emplace(this->agnostic);

    /*=========================================================*/

    return true;
}

/**
 * @brief validate the states and the associated rules of the turing machine.
 */
bool TuringMachineParser::p_validateState() {


    /*============== construct states set =====================*/

    std::set<std::string> stateSet = {};
    std::vector<std::string> stateVec = {};
    std::string initstate;

    // only initial state matters. otherwise, the order doesn't matter.

    if (!data["states"].is_array()) {
        return false;
        for (auto i : data["states"]) {
            if (i.is_string()) {
                std::string i_str = i.get<std::string>();
                if (stateSet.find(i_str) != stateSet.end()) {
                    LOG("Duplicate names found in states. ", ERROR);
                    return false;
                }
                else {
                    stateSet.emplace(i_str);
                    stateVec.push_back(i_str);
                }
                if (i == data["states"][0]) {
                    initstate = i.get<std::string>();
                }
            }
            else {
                LOG("non-string provided in states parameter.", ERROR);
                return false;
            }
        }
    }

    /*============== verify terminate states ===================*/


    std::set<std::string> acceptVec = {};

    std::set<std::string> rejectVec = {};

    if (!data["accept_states"].is_array()) {
        return false;
        for (auto i : data["accept_states"]) {
            if (i.is_string()) {
                std::string i_str = i.get<std::string>();
                // no checks for duplicate accept states 
                this->accept_states.push_back(i_str);
                acceptVec.emplace(i_str);

            }
            else {
                LOG("non-string provided in accept_states parameter.", ERROR);
                return false;
            }
        }
    }

    if (!data["reject_states"].is_array()) {
        return false;
        for (auto i : data["reject_states"]) {
            if (i.is_string()) {
                std::string i_str = i.get<std::string>();
                // no checks for duplicate reject states 
                this->reject_states.push_back(i_str);
                rejectVec.emplace(i_str);

            }
            else {
                LOG("non-string provided in reject_states parameter.", ERROR);
                return false;
            }
        }
    }

    std::vector<std::string> intersec = {};
    std::set_intersection(acceptVec.begin(), acceptVec.end(), rejectVec.begin(), rejectVec.end(), intersec.begin());
    if (intersec.size() != 0) {
        LOG("accept states and reject states cannot overlap.", ERROR);
        return false;
    }


    if (!p_validateRule()) {
        return false;
    }

    // construct state array
    for (auto stateName: stateVec) {
        std::vector<Rule> ruleList = ruleMap[stateName];
        CheckStatus cs = CONTINUE;
        if (acceptVec.find(stateName) != acceptVec.end()) {
            cs = ACCEPT;
        }
        if (rejectVec.find(stateName) != rejectVec.end()) {
            cs = REJECT;
        }
        State state = State(stateName, ruleList, agnostic, cs);
        states.push_back(state);
    }


    return true;

}

/**
 * @brief validate the rules of the turing machine.
 */
bool TuringMachineParser::p_validateRule() {

    // rules -> [rule]
    for (auto rule : data["rules"]) {

        std::string state = "";
        std::vector<char> tapes = {};
        std::vector<Operations> operations = {};
        std::string destination = "";


        // start state 
        if (rule["state"] != nullptr && rule["state"].is_string()) {
            state = rule["state"].get<std::string>();
        }
        else if (rule["state"] == nullptr) {
            LOG("rule must have a state.", ERROR);
            return false;
        }
        else {
            LOG("rule state must be of string type. ", ERROR);
            return false;
        }

        // destination state 
        if (rule["destination"] != nullptr && rule["destination"].is_string()) {
            state = rule["destination"].get<std::string>();
        }
        else if (rule["destination"] == nullptr) {
            LOG("rule must have a destination.", ERROR);
            return false;
        }
        else {
            LOG("rule destination must be of string type. ", ERROR);
            return false;
        }

        // tapes
        if (rule["tapes"] != nullptr && rule["tapes"].is_array()) {
            for (auto i: rule["tapes"]) {
                if (i.is_string()) {
                    std::string i_str = i.get<std::string>();
                    if (i_str.length() != 1) {
                        LOG("tapes expects inputs of strings all of length 1. ", ERROR);
                        return false;
                    } 
                    if (alphabet.find(i_str[0]) == alphabet.end()) {
                        LOG("your tapes must be composed of characters in your alphabet. ", ERROR);
                        return false;
                    }
                    tapes.push_back(i_str[0]);
                }
                LOG("tapes expects inputs of strings all of length 1. ", ERROR);
                return false;
            }
        }
        else {
            LOG("tapes must be an array. ", ERROR);
            return false;
        }

        if (tapes.size() != (size_t)tapenum) {
            LOG("tapes expects exactly as many tapes as your provided tapenum parameter. ", ERROR);
            return false;
        }

        // operations
        if (rule["operations"] != nullptr && rule["operations"].is_array()) {

            // single operation 
            for (auto i: rule["operations"]) {
                if (!i.is_array()) {
                    LOG("elements of operations must be arrays. ", ERROR);
                    return false;
                }
                if (!(i.size() == (size_t)tapenum)) {
                    LOG("each array in operations must be the same size as tapenum.", ERROR);
                    return false;
                }

                std::vector<OP> singleOps = {};
                // single operation on single tape
                for (auto j: i) {
                    if (!j["op"].is_string() || !j["ct"].is_string()) {
                        LOG("operation contains bad input type. expectes all strings with length 1.", ERROR);
                        return false;
                    }
                    std::string opstr = j["op"].get<std::string>();
                    std::string ctstr = j["ct"].get<std::string>();
                    if (opstr.length() != 1 || ctstr.length() != 1) {
                        LOG("operation contains bad input format. expectes all strings with length 1.", ERROR);
                        return false;
                    }
                    char opchar = opstr.at(0);
                    char ctchar = ctstr.at(0);
                    OPCODE opcode;
                    switch(opchar) {
                        case 'W':
                            opcode = W;
                            break;
                        case 'L':
                            opcode = L;
                            break;
                        case 'R':
                            opcode = R;
                            break;
                        case 'P':
                            opcode = P;
                            break;
                        case 'M':
                            opcode = M;
                            break;
                        default:
                            LOG("opcode must be of the following input: W, L, R, P, M. ", ERROR);
                            return false;
                    }
                    OP op = OP{opcode, ctchar};
                    singleOps.push_back(op);
                }
                operations.push_back(singleOps);
            }
        }
        else {
            LOG("operations must be an array. ", ERROR);
            return false;
        }
        Rule r = Rule(tapes, state, destination, operations);

        ruleMap[state].push_back(r);

    }

    return true;
}

bool TuringMachineParser::p_validateTape() {









    return true;

}
