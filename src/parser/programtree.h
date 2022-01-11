#ifndef JEZYK_Z_CZASEM_PROGRAMTREE_H
#define JEZYK_Z_CZASEM_PROGRAMTREE_H

#include "phrase.h"
#include "command.h"
#include <vector>
#include <memory>

namespace parser {
    class ProgramTree : public Phrase {
    public:
        inline void addCommand(std::unique_ptr<Command> command) {
            commands.push_back(std::move(command));
        }

        std::string toString() override;

        virtual void execute() override;

    private:
        std::vector<std::unique_ptr<Command>> commands;
    };
}

#endif //JEZYK_Z_CZASEM_PROGRAMTREE_H
