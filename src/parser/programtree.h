#ifndef JEZYK_Z_CZASEM_PROGRAMTREE_H
#define JEZYK_Z_CZASEM_PROGRAMTREE_H

#include "phrase.h"
#include "command.h"

namespace parser {
    class ProgramTree : public Phrase {
    public:
        ProgramTree() { context = std::make_shared<interpreter::Context>(); }

        inline void addCommand(std::unique_ptr<Command> command) {
            commands.push_back(std::move(command));
        }

        std::string toString(int depth = 0) override;

        void execute(std::shared_ptr<interpreter::Context> cont = nullptr) override;

    private:
        std::vector<std::unique_ptr<Command>> commands;
    };
}

#endif //JEZYK_Z_CZASEM_PROGRAMTREE_H
