#include "TuringMachine.hpp"

#include "TuringLog.hpp"

int main() {

    SET_VERBOSE(ALL);
    std::cout << "=============================================================" << std::endl;
    Rule s0_r0 = Rule({'a', 'b', 'c'}, "s0", "s0", {{}, {}, {}});
    Rule s0_r1 = Rule({'a', 'b', 'd'}, "s0", "s1", {{}, {}, {}});

    Rule s1_r0 = Rule({'a', 'b', 'c'}, "s1", "s0", {{}, {}, {}});
    Rule s1_r1 = Rule({'a', 'c', 'e'}, "s1", "s2", {{}, {}, {}});
    Rule s1_r2 = Rule({'a', 'e', 'f'}, "s1", "s3", {{}, {}, {}});
    Rule s1_r3 = Rule({'a', 'b', 'd'}, "s1", "s2", {{}, {}, {}});

    State s0 = State("s0", {s0_r0, s0_r1}, '@', CONTINUE);
    State s1 = State("s1", {s1_r0, s1_r1, s1_r2, s1_r3}, '@', CONTINUE);
    State s2 = State("s2", {}, '@', ACCEPT);
    State s3 = State("s3", {}, '@', REJECT);

    Tape t0 = Tape("a", '_');
    Tape t1 = Tape("b", '_');
    Tape t2 = Tape("c", '_');

    TuringMachine tm = TuringMachine({s0, s1, s2, s3}, {t0, t1, t2});
    tm.setMaxIteration(5);
    tm.execute();

    std::cout << "=============================================================" << std::endl;
    Tape t3 = Tape("a");
    Tape t4 = Tape("b");
    Tape t5 = Tape("d");

    TuringMachine tm2 = TuringMachine({s0, s1, s2, s3}, {t3, t4, t5});
    tm2.setMaxIteration(5);
    tm2.execute();

    std::cout << "=============================================================" << std::endl;

    Tape t6 = Tape("a");
    Tape t7 = Tape("b");
    Tape t8 = Tape("d");

    TuringMachine tm3 = TuringMachine({s0, s1, s2, s3}, {t6, t7, t8});
    tm3.setMaxIteration(5);
    tm3.execute();

    std::cout << "=============================================================" << std::endl;

    Rule ns0_r0 = Rule({'a'}, "s0", "s1", {{OP{R, 'x'}, OP{W, 'b'}}});
    Rule ns1_r0 = Rule({'b'}, "s0", "s2", {{}});
    State ns0 = State("s0", {ns0_r0}, '@', CONTINUE);
    State ns1 = State("s1", {ns1_r0}, '@', CONTINUE);
    State ns2 = State("s2", {}, '@', ACCEPT);
    Tape t10 = Tape("a", '_');

    TuringMachine tm4 = TuringMachine({ns0, ns1, ns2}, {t10});
    tm4.execute();

    Tape t11 = Tape("_", '_');
    TuringMachine tm5 = TuringMachine({ns0, ns1, ns2}, {t11});
    tm5.execute();

}