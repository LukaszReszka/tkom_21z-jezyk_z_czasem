#include <memory>
#include <utility>
#include "operatoroperation.h"
#include "tln_exception.h"
#include "literal.h"

namespace parser {
    OperatorOperation::OperatorOperation(OperatorType &t, std::unique_ptr<Expression> first_op,
                                         std::unique_ptr<Expression> second_op, std::shared_ptr<interpreter::Context> c)
            : type(t), first_operand(std::move(first_op)), second_operand(std::move(second_op)),
              context(std::move(c)) {}

    OperatorOperation::OperatorOperation(std::unique_ptr<Expression> op, std::shared_ptr<interpreter::Context> c)
            : type(UNARY_MINUS), first_operand(std::move(op)), context(std::move(c)) {}

    std::string OperatorOperation::toString(int depth) {
        std::string hyphens;
        for (int i = 0; i < depth; ++i)
            hyphens += "-";
        std::string text_rep = hyphens + "Operator ";
        hyphens += "-";
        if (type == OperatorType::PLUS)
            text_rep += "PLUS";
        else if (type == OperatorType::MINUS)
            text_rep += "MINUS";
        else if (type == OperatorType::MULTIPLY)
            text_rep += "MULTIPLY";
        else if (type == OperatorType::DIVIDE)
            text_rep += "DIVIDE";
        else if (type == OperatorType::UNARY_MINUS)
            text_rep += "UNARY_MINUS";
        else if (type == OperatorType::OR)
            text_rep += "OR";
        else if (type == OperatorType::AND)
            text_rep += "AND";
        else if (type == OperatorType::EQUAL)
            text_rep += "EQUAL";
        else if (type == OperatorType::NOT_EQUAL)
            text_rep += "NOT_EQUAL";
        else if (type == OperatorType::GREATER)
            text_rep += "GREATER";
        else if (type == OperatorType::GREATER_EQUAL)
            text_rep += "GREATER_EQUAL";
        else if (type == OperatorType::LESS)
            text_rep += "LESS";
        else if (type == OperatorType::LESS_EQUAL)
            text_rep += "LESS_EQUAL";
        else if (type == OperatorType::ASSIGN)
            text_rep += "ASSIGN";

        text_rep += "\n" + hyphens + "First Operand:\n" + first_operand->toString(depth + 2);
        if (type != OperatorType::UNARY_MINUS)
            text_rep += hyphens + "Second Operand:\n" + second_operand->toString(depth + 2);

        return text_rep;
    }

    std::shared_ptr<Value> OperatorOperation::evaluate() {
        std::shared_ptr<Value> left_value, right_value;
        if (type != ASSIGN)
            left_value = first_operand->evaluate();

        if (type != UNARY_MINUS)
            right_value = second_operand->evaluate();

        if (type == ASSIGN)
            assign(right_value);
        else if (type == PLUS)
            return checkTypesAndPerformOperation(left_value, right_value);
        else if (type == UNARY_MINUS)
            return negation(left_value);
        else if (type == EQUAL)
            checkSymmetrically(left_value, right_value);
        //else if (type == MINUS)
        //    return subtraction(left_value, right_value);
        //else if (type == MULTIPLY)
        //    return multiplication(left_value, right_value);
        //else
        // ...

        return {};
    }

    std::shared_ptr<Value>
    OperatorOperation::checkTypesAndPerformOperation(std::shared_ptr<Value> val1, std::shared_ptr<Value> val2) {
        std::shared_ptr<Value> returned_val;

        returned_val = checkSymmetrically(val1, val2);
        if (returned_val->type != ValueType::NONE)
            return returned_val;

        returned_val = checkSymmetrically(val2, val1, true);
        if (returned_val->type != ValueType::NONE)
            return returned_val;

        throw tln_exception("Cannot use operator with specified operands\n");
    }

    std::shared_ptr<Value>
    OperatorOperation::checkSymmetrically(std::shared_ptr<Value> val1, std::shared_ptr<Value> val2, bool swappedArgs) {
        std::shared_ptr<Value> returned_val = std::make_shared<Value>();

        if (val1->type == ValueType::INT && val2->type == ValueType::DOUBLE) {

            if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                returned_val->type = ValueType::BOOL;
                if (type == OperatorType::EQUAL) {
                    returned_val->value.boolean = (val1->value.integer_numb == val2->value.double_numb);
                } else if (type == OperatorType::NOT_EQUAL) {
                    returned_val->value.boolean = (val1->value.integer_numb != val2->value.double_numb);
                } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                           (swappedArgs && type == OperatorType::LESS)) {
                    returned_val->value.boolean = (val1->value.integer_numb > val2->value.double_numb);
                } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                           (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                    returned_val->value.boolean = (val1->value.integer_numb >= val2->value.double_numb);
                } else if ((!swappedArgs && type == OperatorType::LESS) ||
                           (swappedArgs && type == OperatorType::GREATER)) {
                    returned_val->value.boolean = (val1->value.integer_numb < val2->value.double_numb);
                } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                           (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                    returned_val->value.boolean = (val1->value.integer_numb <= val2->value.double_numb);
                }
            } else if (type == OperatorType::PLUS) {
                returned_val->type = ValueType::DOUBLE;
                returned_val->value.double_numb = val1->value.integer_numb + val2->value.double_numb;
            } else if (type == OperatorType::MINUS) {
                returned_val->type = ValueType::DOUBLE;
                returned_val->value.double_numb = val1->value.integer_numb - val2->value.double_numb;
            }

        } else if (val1->type == ValueType::INT_S || val1->type == ValueType::TIME_PERIOD) {
            if (val2->type == ValueType::INT_MIN) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_s == val2->value.int_min);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_s != val2->value.int_min);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_s > val2->value.int_min);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_s >= val2->value.int_min);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_s < val2->value.int_min);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_s <= val2->value.int_min);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::INT_S;
                    returned_val->value.int_s = val1->value.int_s + val2->value.int_min;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::INT_S;
                    returned_val->value.int_s = val1->value.int_s - val2->value.int_min;
                }

            } else if (val2->type == ValueType::INT_H) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_s == val2->value.int_h);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_s != val2->value.int_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_s > val2->value.int_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_s >= val2->value.int_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_s < val2->value.int_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_s <= val2->value.int_h);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::INT_S;
                    returned_val->value.int_s = val1->value.int_s + val2->value.int_h;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::INT_S;
                    returned_val->value.int_s = val1->value.int_s - val2->value.int_h;
                }

            } else if (val2->type == ValueType::DOUBLE_S) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_s == val2->value.double_s);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_s != val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_s > val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_s >= val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_s < val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_s <= val2->value.double_s);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.int_s + val2->value.double_s;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.int_s - val2->value.double_s;
                }
            } else if (val2->type == ValueType::DOUBLE_MIN) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_s == val2->value.double_min);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_s != val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_s > val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_s >= val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_s < val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_s <= val2->value.double_min);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.int_s + val2->value.double_min;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.int_s - val2->value.double_min;
                }
            } else if (val2->type == ValueType::DOUBLE_H) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_s == val2->value.double_h);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_s != val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_s > val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_s >= val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_s < val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_s <= val2->value.double_h);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.int_s + val2->value.double_h;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.int_s - val2->value.double_h;
                }
            }

        } else if (val1->type == ValueType::INT_MIN) {
            if (val2->type == ValueType::INT_H) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_min == val2->value.int_h);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_min != val2->value.int_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_min > val2->value.int_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_min >= val2->value.int_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_min < val2->value.int_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_min <= val2->value.int_h);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::INT_MIN;
                    returned_val->value.int_min = val1->value.int_min + val2->value.int_h;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::INT_MIN;
                    returned_val->value.int_min = val1->value.int_min - val2->value.int_h;
                }

            } else if (val2->type == ValueType::DOUBLE_S) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_min == val2->value.double_s);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_min != val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_min > val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_min >= val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_min < val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_min <= val2->value.double_s);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.int_min + val2->value.double_s;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.int_min - val2->value.double_s;
                }
            } else if (val2->type == ValueType::DOUBLE_MIN) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_min == val2->value.double_min);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_min != val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_min > val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_min >= val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_min < val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_min <= val2->value.double_min);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::DOUBLE_MIN;
                    returned_val->value.double_min = val1->value.int_min + val2->value.double_min;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::DOUBLE_MIN;
                    returned_val->value.double_min = val1->value.int_min - val2->value.double_min;
                }
            } else if (val2->type == ValueType::DOUBLE_H) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_min == val2->value.double_h);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_min != val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_min > val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_min >= val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_min < val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_min <= val2->value.double_h);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::DOUBLE_MIN;
                    returned_val->value.double_min = val1->value.int_min + val2->value.double_h;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::DOUBLE_MIN;
                    returned_val->value.double_min = val1->value.int_min - val2->value.double_h;
                }
            }

        } else if (val1->type == ValueType::INT_H) {
            if (val2->type == ValueType::DOUBLE_S) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_h == val2->value.double_s);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_h != val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_h > val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_h >= val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_h < val2->value.double_s);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_h <= val2->value.double_s);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.int_h + val2->value.double_s;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.int_h - val2->value.double_s;
                }
            } else if (val2->type == ValueType::DOUBLE_MIN) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_h == val2->value.double_min);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_h != val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_h > val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_h >= val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_h < val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_h <= val2->value.double_min);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::DOUBLE_MIN;
                    returned_val->value.double_min = val1->value.int_h + val2->value.double_min;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::DOUBLE_MIN;
                    returned_val->value.double_min = val1->value.int_h - val2->value.double_min;
                }
            } else if (val2->type == ValueType::DOUBLE_H) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.int_h == val2->value.double_h);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.int_h != val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.int_h > val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_h >= val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.int_h < val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.int_h <= val2->value.double_h);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::DOUBLE_H;
                    returned_val->value.double_h = val1->value.int_h + val2->value.double_h;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::DOUBLE_H;
                    returned_val->value.double_h = val1->value.int_h - val2->value.double_h;
                }
            }

        } else if (val1->type == ValueType::DOUBLE_S) {
            if (val2->type == ValueType::DOUBLE_MIN) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.double_s == val2->value.double_min);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.double_s != val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.double_s > val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.double_s >= val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.double_s < val2->value.double_min);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.double_s <= val2->value.double_min);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.double_s + val2->value.double_min;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.double_s - val2->value.double_min;
                }
            } else if (val2->type == ValueType::DOUBLE_H) {
                if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                    returned_val->type = ValueType::BOOL;
                    if (type == OperatorType::EQUAL) {
                        returned_val->value.boolean = (val1->value.double_s == val2->value.double_h);
                    } else if (type == OperatorType::NOT_EQUAL) {
                        returned_val->value.boolean = (val1->value.double_s != val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                               (swappedArgs && type == OperatorType::LESS)) {
                        returned_val->value.boolean = (val1->value.double_s > val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                               (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                        returned_val->value.boolean = (val1->value.double_s >= val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS) ||
                               (swappedArgs && type == OperatorType::GREATER)) {
                        returned_val->value.boolean = (val1->value.double_s < val2->value.double_h);
                    } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                               (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                        returned_val->value.boolean = (val1->value.double_s <= val2->value.double_h);
                    }
                } else if (type == OperatorType::PLUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.double_s + val2->value.double_h;
                } else if (type == OperatorType::MINUS) {
                    returned_val->type = ValueType::DOUBLE_S;
                    returned_val->value.double_s = val1->value.double_s - val2->value.double_h;
                }
            }
        } else if (val1->type == ValueType::DOUBLE_MIN && val2->type == ValueType::DOUBLE_H) {
            if (type >= OperatorType::EQUAL && type <= OperatorType::LESS_EQUAL) {
                returned_val->type = ValueType::BOOL;
                if (type == OperatorType::EQUAL) {
                    returned_val->value.boolean = (val1->value.double_min == val2->value.double_h);
                } else if (type == OperatorType::NOT_EQUAL) {
                    returned_val->value.boolean = (val1->value.double_min != val2->value.double_h);
                } else if ((!swappedArgs && type == OperatorType::GREATER) ||
                           (swappedArgs && type == OperatorType::LESS)) {
                    returned_val->value.boolean = (val1->value.double_min > val2->value.double_h);
                } else if ((!swappedArgs && type == OperatorType::GREATER_EQUAL) ||
                           (swappedArgs && type == OperatorType::LESS_EQUAL)) {
                    returned_val->value.boolean = (val1->value.double_min >= val2->value.double_h);
                } else if ((!swappedArgs && type == OperatorType::LESS) ||
                           (swappedArgs && type == OperatorType::GREATER)) {
                    returned_val->value.boolean = (val1->value.double_min < val2->value.double_h);
                } else if ((!swappedArgs && type == OperatorType::LESS_EQUAL) ||
                           (swappedArgs && type == OperatorType::GREATER_EQUAL)) {
                    returned_val->value.boolean = (val1->value.double_min <= val2->value.double_h);
                }
            } else if (type == OperatorType::PLUS) {
                returned_val->type = ValueType::DOUBLE_MIN;
                returned_val->value.double_min = val1->value.double_min + val2->value.double_h;
            } else if (type == OperatorType::MINUS) {
                returned_val->type = ValueType::DOUBLE_MIN;
                returned_val->value.double_min = val1->value.double_min - val2->value.double_h;
            }
        }

        if (type == OperatorType::MINUS && swappedArgs && returned_val->type != ValueType::NONE)
            return negation(returned_val);
        else
            return returned_val;
    }

    std::shared_ptr<Value>
    OperatorOperation::checkSameTypes(std::shared_ptr<Value> val1, std::shared_ptr<Value> val2) {
        std::shared_ptr<Value> returned_val = std::make_shared<Value>();
        if (val1->type == ValueType::INT && val2->type == ValueType::INT) {
            returned_val->type = ValueType::BOOL;
            returned_val->value.boolean = val1->value.integer_numb != val2->value.integer_numb;
        } else
            throw tln_exception("Cannot use checkTypesAndPerformOperation with specified operands\n");
        return returned_val;
    }

    void OperatorOperation::assign(std::shared_ptr<Value> val) {
        std::unique_ptr<Literal> literal = reinterpret_cast<std::unique_ptr<Literal> &&>(first_operand);

        if (literal->val->type != ValueType::VARIABLE)
            throw tln_exception("Cannot assign value to non-variable\n");

        context->addVariable(literal->val->value_str, std::move(val));
    }


    std::shared_ptr<Value> OperatorOperation::negation(std::shared_ptr<Value> val) {
        if (val->type == ValueType::INT) {
            val->value.integer_numb *= -1;
        } else if (val->type == ValueType::DOUBLE) {
            val->value.double_numb *= -1;
        } else if (val->type == ValueType::INT_S || val->type == ValueType::TIME_PERIOD) {
            val->value.int_s *= -1;
        } else if (val->type == ValueType::INT_MIN) {
            val->value.int_min *= -1;
        } else if (val->type == ValueType::INT_H) {
            val->value.int_h *= -1;
        } else if (val->type == ValueType::DOUBLE_S) {
            val->value.double_s *= -1;
        } else if (val->type == ValueType::DOUBLE_MIN) {
            val->value.double_min *= -1;
        } else if (val->type == ValueType::DOUBLE_H) {
            val->value.double_h *= -1;
        } else
            throw tln_exception("Cannot use negation with specified operand\n");

        return val;
    }

}