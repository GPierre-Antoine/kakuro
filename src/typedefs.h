//
// Created by Pierre-Antoine on 20/05/2018.
//

#ifndef KAKURO_TYPEDEFS_H
#define KAKURO_TYPEDEFS_H

#include <functional>

#include "forward.h"

typedef std::function<long(const csp_variable_ptr &)> heuristic;

#endif //KAKURO_TYPEDEFS_H
