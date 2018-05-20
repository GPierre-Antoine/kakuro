//
// Created by Pierre-Antoine on 19/05/2018.
//


#include <iostream>
#include "csp_constraint.h"
bool csp::csp_constraint::associated_variable_are_valuated() const
{
    for (const auto &i : associated_variables)
    {
        if (!i->is_valuated())
        {
            return false;
        }
    }
    return true;
}

csp::csp_constraint::csp_constraint(std::vector<csp::csp_variable *> &vector) : associated_variables(vector)
{

}

bool csp::csp_constraint::one_variable_left_unvaluated() const
{
    std::size_t counter{0};
    for (const auto &i:associated_variables)
    {
        if (!i->is_valuated())
        {
            ++counter;
        }
    }
    return counter == 1;
}

csp::csp_variable *csp::csp_constraint::get_unvaluated_variable() const
{
    if (!one_variable_left_unvaluated())
    {
        throw std::runtime_error("More than one variable left");
    }
    for (auto &i:associated_variables)
    {
        if (!i->is_valuated())
        {
            return i;
        }
    }
    // impossible
    return nullptr;
}
void csp::csp_constraint::run_fc(std::vector<csp::record> &r) const
{
    if (!one_variable_left_unvaluated())
    {
        throw std::runtime_error("More than one variable left");
    }
    run_fc_child(r);
}

