//
// Created by Pierre-Antoine on 21/05/2018.
//

#include "forward.h"
#include "csp/csp_variable.h"
#include "csp/csp_constraint.h"
#include "csp/constraint/csp_constraint_sum.h"
#include "csp/constraint/csp_constraint_difference.h"

csp_variable_ptr make_yield_variable(std::size_t var){
    return std::make_shared<csp::csp_variable>(var);
}
csp_constraint_ptr make_yield_c_sum(std::vector<csp_variable_ptr> & variables, size_t sum){
    return std::make_shared<csp::csp_constraint_sum>(variables,sum);
}
csp_constraint_ptr make_yield_c_diff(std::vector<csp_variable_ptr> & variables){
    return std::make_shared<csp::csp_constraint_difference>(variables);
}