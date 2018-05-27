//
// Created by Pierre-Antoine on 21/05/2018.
//

#include "forward.h"
#include "csp/csp_variable.h"
#include "csp/csp_constraint.h"
#include "csp/constraint/csp_constraint_sum.h"
#include "csp/constraint/csp_constraint_difference.h"
#include "csp/constraint/csp_constraint_solution.h"

csp_variable_ptr make_yield_variable(std::size_t var){
    return std::make_shared<csp::csp_variable>(var);
}

std::size_t counter = 0;

csp_constraint_ptr make_yield_c_sum(size_t sum)
{
    return std::make_shared<csp::csp_constraint_sum>(counter++, sum);
}
csp_constraint_ptr make_yield_c_diff()
{
    return std::make_shared<csp::csp_constraint_difference>(counter++);
}

std::shared_ptr<csp::csp_constraint_solution> make_yield_c_solution()
{
    return std::make_shared<csp::csp_constraint_solution>(counter++);
}

