//
// Created by Jason Fedorowich on 2024-02-18.
//

#ifndef ODINMATH_EXCEPTION_H
#define ODINMATH_EXCEPTION_H

#include <exception>
#include <string>

namespace OdinMath {

    class InvalidArgument : std::exception {
    private:
        std::string cause;
    public:
        InvalidArgument(std::string cause) {
            this->cause = cause;
        }

        ~InvalidArgument() _NOEXCEPT override;

        const char *what() const _NOEXCEPT override;
    };

    class UnimplementedException : std::exception {
    private:
        std::string cause;
    public:
        UnimplementedException(std::string cause) {
            this->cause = cause;
        }

        ~UnimplementedException() _NOEXCEPT override;

        const char *what() const _NOEXCEPT override;
    };
}

#endif //ODINMATH_EXCEPTION_H
