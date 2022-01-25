#ifndef JEZYK_Z_CZASEM_TLN_EXCEPTION_H
#define JEZYK_Z_CZASEM_TLN_EXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class tln_exception : public std::exception {
public:
    explicit tln_exception(std::string e_mess) : error_message(std::move(e_mess)) {}

    [[nodiscard]] const char *what() const noexcept override {
        return error_message.c_str();
    }

private:
    const std::string error_message;
};

#endif //JEZYK_Z_CZASEM_TLN_EXCEPTION_H
