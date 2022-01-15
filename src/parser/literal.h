#ifndef JEZYK_Z_CZASEM_LITERAL_H
#define JEZYK_Z_CZASEM_LITERAL_H

#include "expression.h"
#include <string>
#include <memory>
#include <chrono>

using std::chrono::seconds, std::chrono::minutes, std::chrono::hours;
using std::ratio, std::chrono::duration;

namespace parser {
    class Literal : public Expression {
    public:

        Literal() = default;

        Literal(lexer::TimeMoment &tm, ValueType type);

        std::string toString(int depth) override;

        std::unique_ptr<Value> evaluate() override;

        std::unique_ptr<Value> val;
    };
}


#endif //JEZYK_Z_CZASEM_LITERAL_H
