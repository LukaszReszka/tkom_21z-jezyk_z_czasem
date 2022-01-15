#ifndef JEZYK_Z_CZASEM_PHRASE_H
#define JEZYK_Z_CZASEM_PHRASE_H

namespace parser {
    class Phrase {
    public:

        virtual std::string toString() = 0;

        virtual void execute() = 0;

        inline std::ostream &operator<<(std::ostream &os) {
            return os << toString();
        }
    };
}

#endif //JEZYK_Z_CZASEM_PHRASE_H
