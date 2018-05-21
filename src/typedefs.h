//
// Created by Pierre-Antoine on 20/05/2018.
//

#ifndef KAKURO_TYPEDEFS_H
#define KAKURO_TYPEDEFS_H


#include <memory>
#include "csp/csp_variable.h"

typedef std::shared_ptr<csp::csp_variable> csp_variable_ptr;


#include <functional>
typedef std::function<bool(const csp_variable_ptr&,const csp_variable_ptr&)> heuristic;

#endif //KAKURO_TYPEDEFS_H
