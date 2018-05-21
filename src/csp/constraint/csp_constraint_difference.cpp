//
// Created by Pierre-Antoine on 20/05/2018.
//

#include "csp_constraint_difference.h"
csp::csp_constraint_difference::csp_constraint_difference(std::vector<csp_variable_ptr> &vector) :
    csp_constraint(vector)
{
    if (associated_variables.size()!=2){
        throw std::runtime_error("Not wrong number of variables");
    }
}
bool csp::csp_constraint_difference::run_constraint() const
{
    return associated_variables[0]->get_value() != associated_variables[1]->get_value();
}

csp_variable_ptr csp::csp_constraint_difference::run_fc_child() const
{
    auto free = get_last_unvaluated_variable();
    for (auto i:associated_variables){
        if (i->is_valuated()){
            free->restrict(i->get_value());
        }
    }
    return free;
}
std::string csp::csp_constraint_difference::edit() const
{
    return std::string("Diff Constraint ") + (this->is_valuated() ? "{valuated}":"{unvaluated}");
}