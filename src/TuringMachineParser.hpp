#include <nlohmann/json.hpp>
#include <set>

#include "TuringMachine.hpp"

using json = nlohmann::json;

class TuringMachineParser {

    private:
        std::string fname;
        json data;

        // turing machine attributes

        std::string name;
        std::vector<State> states;
        std::vector<Tape> tapes;

        std::map<std::string, std::vector<Rule> >ruleMap;
        
        // turing machine ground rules

        std::set<char> alphabet;
        int tapenum;
        char blank;
        char agnostic;
        
        std::vector<std::string> accept_states;
        std::vector<std::string> reject_states;
        

        bool p_parseFile();

        bool p_validate();

        bool p_validateParamNum();

        bool p_validateGroundRules();

        bool p_validateState();

        bool p_validateRule();

        bool p_validateTape();


    public:
        TuringMachineParser(std::string fname): fname(fname), alphabet({}) {}

        bool parse();
        TuringMachine getMachine();


};