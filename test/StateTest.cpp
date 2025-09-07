#include "State.hpp"
#include "TuringLog.hpp"




int main() {
    std::cout << "==================================" << std::endl;
    SET_VERBOSE(ALL);
    std::vector<char> vc0 = {'a', 'b', 'c', '@', 'e'};
    std::vector<char> vc1 = {'a', 'd', 'r', 'h', 's'};
    char agnostic = '@';
    
    Rule r0 = Rule(vc0, "s0", "s1", {{}, {}, {}, {}, {}});
    Rule r1 = Rule(vc1, "s0", "s0", {{}, {}, {}, {}, {}});
    State s0 = State("s0", {r0, r1}, agnostic, CONTINUE);
    
    std::string dst = "";

    Tape ta = Tape("a");
    Tape tb = Tape("b");
    Tape tc = Tape("c");
    Tape t2 = Tape("2");
    Tape te = Tape ("e");

    Tape td = Tape("d");
    Tape tr = Tape("r");
    Tape th = Tape("h");
    Tape ts = Tape("s");
    std::vector<Tape> tapes0 = {ta, tb, tc, t2, te};
    s0.checkInput(tapes0, dst);
    std::cout << "abc2e's destination is " << dst << std::endl;
    std::cout << "==================================" << std::endl;
    std::vector<Tape> tapes1 = {ta, td, tr, th, ts}; 
    s0.checkInput(tapes1, dst);
    std::cout << "vc1's destination is " << dst << std::endl;
    std::cout << "==================================" << std::endl;
    std::vector<Tape> tapes2 = {ta}; 
    s0.checkInput(tapes2, dst);
    std::cout << "a's destination is " << dst << std::endl;

    return 0;
}