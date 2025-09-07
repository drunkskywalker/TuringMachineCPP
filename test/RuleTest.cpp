#include "Rule.hpp"
#include "TuringLog.hpp"


int main() {
    SET_VERBOSE(ALL);
    std::vector<char> matches = {'a', '@'};
    std::string destination = "abcde";
    Rule r = Rule(matches, "0", destination, {{ OP{L, 'a'}, OP{W, 'c'}, OP{R, 'c'}, OP{R, 'c'}, OP{R, 'c'}, OP{W, 'x'} }, {OP{R, ' '}, OP{W, 'c'}}});
    std::string pp = "df";

    Tape t0 = Tape("a");
    Tape t1 = Tape("b");
    std::vector<Tape> tapes = {t0, t1};
    r.checkInput(tapes, pp, '@');
    r.operate(tapes);

    std::cout << "dstination: " << pp << std::endl;

    std::cout << "tape 0: " << tapes[0].readAll() << std::endl;
    std::cout << "tape 1: " << tapes[1].readAll() << std::endl;
    
}