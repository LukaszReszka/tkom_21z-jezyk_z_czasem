#ifndef JEZYK_Z_CZASEM_COMMAND_H
#define JEZYK_Z_CZASEM_COMMAND_H

#include "phrase.h"
#include <string>

namespace parser {
    class Command : public Phrase {
    public:

        std::string toString() override;

        virtual void execute() override;
    };
}

#endif //JEZYK_Z_CZASEM_COMMAND_H
