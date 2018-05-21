//
// Created by Pierre-Antoine on 20/05/2018.
//

#ifndef KAKURO_OSTREAM_H
#define KAKURO_OSTREAM_H

#include <iostream>
#include "csp/csp_constraint.h"
#include "typedefs.h"

using std::cout;
using std::endl;

namespace csp
{
    class csp_variable;
    class algorithm;
    class csp_constraint;
}

std::ostream &operator<<(std::ostream &os, const csp::csp_variable &var);
std::ostream &operator<<(std::ostream &os, const csp_variable_ptr &var);
std::ostream &operator<<(std::ostream &os, const csp::algorithm &var);
std::ostream &operator<<(std::ostream &os, const csp::csp_constraint &constraint);
std::ostream &operator<<(std::ostream &os, const std::vector<csp_variable_ptr> &constraint);


#endif //KAKURO_OSTREAM_H
