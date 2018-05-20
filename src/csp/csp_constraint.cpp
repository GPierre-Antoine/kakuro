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
csp::csp_constraint::csp_constraint(variable_ref &vector, std::size_t sum) : sum(sum), associated_variables(vector)
{

}
bool csp::csp_constraint::run_constraint() const
{
    if (sum)
    {
        return constraint_sum();
    }
    return constraint_diff();
}
bool csp::csp_constraint::constraint_sum() const
{
    std::size_t accumulation = 0;
    for (const auto &i:associated_variables)
    {
        accumulation += i->get_value();
    }
    return sum == accumulation;
}
bool csp::csp_constraint::constraint_diff() const
{
    return associated_variables[0]->get_value() != associated_variables[1]->get_value();
}

std::ostream &csp::operator<<(std::ostream &f, const csp::csp_constraint &constraint)
{
    std::string text = "";
    if (constraint.sum)
    {
        text+="Sum Constraint ("+std::to_string(constraint.sum)+") ";
    }
    else
    {
        text+="Diff Constraint ";
    }
    f << text;
    for (const auto &i:constraint.associated_variables)
    {
        f << *i << " ";
    }
    return f;
}
