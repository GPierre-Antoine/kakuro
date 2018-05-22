//
// Created by Pierre-Antoine on 20/05/2018.
//

#include "ostream.h"

#include "csp/csp_variable.h"
#include "csp/csp_constraint.h"
#include "csp/algorithm.h"

constexpr const char *underline_start = "\033[4m";
constexpr const char *underline_stop  = "\033[0m";

using std::ostream;


ostream &operator<<(ostream &os, const csp::algorithm &var)
{
    return os << var.name;
}

ostream &operator<<(ostream &os, const csp::csp_variable &var)
{
    os << std::string("V") + std::to_string(var.get_id()) + "{";
    if (!var.has_empty_domain())
    {
        auto      last = std::prev(var.cend());
        for (auto i    = var.cbegin(); i < last; std::advance(i, 1))
        {
            os << *i << ",";

        }

        if (var.is_valuated())
        {
            os << underline_start << *last << underline_stop;
        }
        else
        {
            os << *last;
        }
    }
    return os << "}";
}

ostream &operator<<(ostream &os, const csp_variable_ptr &var)
{
    return os << *var;
}

ostream &operator<<(ostream &os, const csp::csp_constraint &constraint)
{
    os << constraint.edit() << " [";
    for (auto i = constraint.cbegin(); i < constraint.cend(); std::advance(i, 1))
    {
        if (i != constraint.cbegin())
        {
            os << ",";
        }
        os << **i;
    }
    return os << "]";
}

ostream &operator<<(ostream &os, const std::vector<csp_variable_ptr> &constraint)
{
    for (const auto &i:constraint)
    {
        os << *i << " ";
    }
    return os;
}