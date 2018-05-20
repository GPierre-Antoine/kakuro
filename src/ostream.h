//
// Created by Pierre-Antoine on 20/05/2018.
//

#ifndef KAKURO_OSTREAM_H
#define KAKURO_OSTREAM_H

#include <iostream>
#include "csp/csp_variable.h"
#include "csp/constraint/csp_constraint_sum.h"
#include "csp/constraint/csp_constraint_difference.h"
#include "csp/algorithm.h"


namespace csp
{
    std::ostream& operator<<(std::ostream&os, const csp::csp_variable &var);
    std::ostream& operator<<(std::ostream&os, const csp::csp_constraint_sum&constraint);
    std::ostream& operator<<(std::ostream&os, const csp::csp_constraint_difference&constraint);

}

#endif //KAKURO_OSTREAM_H
