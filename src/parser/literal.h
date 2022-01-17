#ifndef JEZYK_Z_CZASEM_LITERAL_H
#define JEZYK_Z_CZASEM_LITERAL_H

#include "expression.h"
#include "../interpreter/context.h"
#include <string>
#include <memory>
#include <chrono>

using std::chrono::seconds, std::chrono::minutes, std::chrono::hours;
using std::ratio, std::chrono::duration;

namespace parser {
    class Literal : public Expression {
    public:

        explicit Literal(std::shared_ptr<interpreter::Context> c);

        Literal(lexer::TimeMoment &tm, ValueType type, std::shared_ptr<interpreter::Context> c);

        std::string toString(int depth) override;

        std::shared_ptr<Value> evaluate() override;

        std::unique_ptr<Value> val;

    private:
        std::shared_ptr<interpreter::Context> context;
    };
}


#endif //JEZYK_Z_CZASEM_LITERAL_H
