//
// Created by Pierre-Antoine on 21/05/2018.
//

#include "forward.h"
#include "csp/csp_variable.h"

csp_variable_ptr make_yield(std::size_t var){
    return std::make_shared<csp::csp_variable>(var);
}