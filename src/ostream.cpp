//
// Created by Pierre-Antoine on 20/05/2018.
//

#include "ostream.h"

#include "csp/csp_variable.h"
#include "csp/csp_constraint.h"
#include "csp/algorithm.h"

#include <sstream>

using std::to_string;

//constexpr const char *underline_start = "\033[4m";
//constexpr const char *underline_stop  = "\033[0m";

constexpr const char *underline_start = ">";
constexpr const char *underline_stop = "<";

string edit(const csp::csp_variable &var)
{
    std::stringstream os;

    os
        << std::string("V")
            + to_string(var.get_id())
            + "@"
            + to_string(var.get_available_size())
            + "#"
            + to_string(var.get_constraint_count())
        + "/"+to_string(var.dom_deg())+"/";
    if (var.is_valuated())
    {
        return '<' + string(os.str()) + '>';
    }
    return string(os.str());
}

string edit(const csp::algorithm &var)
{
    return string(var.name);
}

string edit(const csp::csp_constraint &constraint)
{
    std::stringstream os;
    os << constraint.edit() << " [";
    for (auto i = constraint.cbegin(); i < constraint.cend(); std::advance(i, 1))
    {
        if (i != constraint.cbegin())
        {
            os << ",";
        }
        os << **i;
    }
    os << "]";
    return string(os.str());

}

ostream &operator<<(ostream &os, const csp::algorithm &var)
{
    return os << edit(var);
}

ostream &operator<<(ostream &os, const csp::csp_variable &var)
{
    return os << edit(var);
}

ostream &operator<<(ostream &os, const csp_variable_ptr &var)
{
    return os << edit(*var);
}

ostream &operator<<(ostream &os, const csp::csp_constraint &constraint)
{
    return os << edit(constraint);
}