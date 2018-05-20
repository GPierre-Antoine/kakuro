//
// Created by Pierre-Antoine on 20/05/2018.
//

#include "ostream.h"

std::ostream &csp::operator<<(std::ostream &os, const csp::csp_variable &var)
{
    return os
        << std::string("variable n°")
            + std::to_string(var.get_id())
            + " "
            + (var.is_valuated() ? "{" + std::to_string(var.get_value()) + "}" : " {}");
}

std::ostream &csp::operator<<(std::ostream &os, const csp::csp_constraint_sum &constraint)
{

    os << "Sum Constraint (" + std::to_string(constraint.sum) + ") ";
    for (const auto &i:constraint.associated_variables)
    {
        os << *i << " ";
    }
    return os;
}
std::ostream &csp::operator<<(std::ostream &os, const csp::csp_constraint_difference &constraint)
{
    os << "Diff Constraint ";
    for (const auto &i:constraint.associated_variables)
    {
        os << *i << " ";
    }
    return os;
}