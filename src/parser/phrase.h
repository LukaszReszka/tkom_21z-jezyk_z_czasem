#ifndef JEZYK_Z_CZASEM_PHRASE_H
#define JEZYK_Z_CZASEM_PHRASE_H

#include <string>
#include <memory>

namespace parser {
    class Phrase {
    public:

        virtual std::string toString(int depth) = 0;

        virtual void execute() = 0;
    };
}

#endif //JEZYK_Z_CZASEM_PHRASE_H
