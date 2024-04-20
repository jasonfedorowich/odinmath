//
// Created by Jason Fedorowich on 2024-02-18.
//

#include "odinmath.h"

namespace OdinMath {
    InvalidArgument::~InvalidArgument() noexcept {

    }

    const char *InvalidArgument::what() const noexcept {
        return cause.c_str();
    }

    UnimplementedException::~UnimplementedException() noexcept {

    }

    const char *UnimplementedException::what() const noexcept {
        return cause.c_str();
    }
}

