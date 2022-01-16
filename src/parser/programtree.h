#ifndef JEZYK_Z_CZASEM_PROGRAMTREE_H
#define JEZYK_Z_CZASEM_PROGRAMTREE_H

#include <utility>

#include "phrase.h"
#include "command.h"
#include "../interpreter/context.h"

namespace parser {
    class ProgramTree : public Phrase {
    public:
        explicit ProgramTree(std::shared_ptr<interpreter::Context> c) : context(std::move(c)) {}

        inline void addCommand(std::unique_ptr<Command> command) {
            commands.push_back(std::move(command));
        }

        std::string toString(int depth) override;

        void execute() override;

    private:
        std::vector<std::unique_ptr<Command>> commands;
        std::shared_ptr<interpreter::Context> context;
    };
}

#endif //JEZYK_Z_CZASEM_PROGRAMTREE_H
