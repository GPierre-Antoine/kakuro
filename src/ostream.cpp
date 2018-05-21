//
// Created by Pierre-Antoine on 20/05/2018.
//

#include "ostream.h"

#include "csp/csp_variable.h"
#include "csp/csp_constraint.h"
#include "csp/algorithm.h"

std::ostream &operator<<(std::ostream &os, const csp::algorithm &var)
{
    return os << var.name;
}

std::ostream &operator<<(std::ostream &os, const csp::csp_variable &var)
{
    os
        << std::string("V")
            + std::to_string(var.get_id())
            + (var.is_valuated() ? "(" + std::to_string(var.get_value()) + ")" : "");
    os << "{";
    for (auto i = var.cbegin(); i < var.cend(); std::advance(i, 1))
    {
        if (i!=var.cbegin())
        {
            os << ",";
        }
        os << *i;
    }
    return os << "}";
}

std::ostream &operator<<(std::ostream &os, const csp::csp_constraint &constraint)
{
    os << constraint.edit() << " [";
    for (auto i = constraint.cbegin(); i < constraint.cend(); std::advance(i, 1))
    {
        if (i!=constraint.cbegin())
        {
            os << ",";
        }
        os << **i;
    }
    return os << "]";
}

std::ostream &operator<<(std::ostream &os, const std::vector<csp_variable_ptr> &constraint)
{
    for (const auto&i:constraint){
        os << *i << " ";
    }
    return os;
}