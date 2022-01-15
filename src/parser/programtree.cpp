#include <string>
#include "programtree.h"

namespace parser {
    std::string ProgramTree::toString(int depth) {
        std::string text_rep = "PROGRAM ROOT\n";
        for (auto &c: commands)
            text_rep += c->toString(1);
        return text_rep;
    }

    void ProgramTree::execute() {

    }
}
