#ifndef JEZYK_Z_CZASEM_PHRASE_H
#define JEZYK_Z_CZASEM_PHRASE_H

#include "../interpreter/context.h"
#include <string>
#include <memory>

namespace parser {
    class Phrase {
    public:

        virtual std::string toString(int depth) = 0;

        virtual void execute(std::shared_ptr<interpreter::Context> cont) = 0;

    protected:
        std::shared_ptr<interpreter::Context> context;
    };
}

#endif //JEZYK_Z_CZASEM_PHRASE_H
