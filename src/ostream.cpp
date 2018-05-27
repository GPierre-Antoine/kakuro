//
// Created by Pierre-Antoine on 20/05/2018.
//

#include "ostream.h"

#include "csp/csp_variable.h"
#include "csp/csp_constraint.h"
#include "csp/algorithm.h"

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
            + "/"
            + to_string(var.dom_deg())
            + "/";
    if (var.is_valuated())
    {
        return '<' + string(os.str()) + '>';
    }
    return string(os.str());
}

string edit_value_v(const csp::csp_variable &var)
{
    std::string value;
    if (var.is_valuated())
    {
        value = "{" + std::to_string(var.get_value()) + "}";
    }
    else
    {
        value = "#ERR";
    }

    value += "(" + std::to_string(var.get_available_size()) + ")";

    return std::string("V") + std::to_string(var.get_id()) + value;
}

string edit_domain(const csp::csp_variable &var)
{
    return std::string("V") + std::to_string(var.get_id()) + "" + edit(var.cbegin(), var.cend());
}

string edit(const csp::record &r)
{
    return "{id:"
        + std::to_string(r.get_variable()->get_id())
        + ",ts:"
        + std::to_string(r.timestamp)
        + ",type:"
        + (r.is_manual() ? "M" : "A")
        + "}";
}

string edit(const csp::algorithm &var)
{
    return string(var.name) + " " + (var.stop_at_first_result ? "{first solution only}" : "{all solutions}");
}

string edit(const csp::heuristic &var)
{
    return string(var.name);
}

string edit(const std::size_t &var)
{
    return std::to_string(var);
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
    return os << edit_domain(var);
}

ostream &operator<<(ostream &os, const csp_variable_ptr &var)
{
    return os << edit(*var);
}

ostream &operator<<(ostream &os, const csp::csp_constraint &constraint)
{
    return os << edit(constraint);
}

void os_short(ostream &os, const csp::solution &solution)
{
    os
        << "Ran algorithm "
            + solution.algorithm_info
            + " with heuristic "
            + solution.heuristic_name
            + " in a timelapse of "
            + std::to_string(solution.get_execution_time()) + " CPU time"
        << std::endl;
    os << "Solutions found       : " << solution.get_records().size() << std::endl;
    os << "Constraints tested    : " << solution.get_constraint_count() << std::endl;
    os << "Nodes made            : " << solution.get_node_count();
}

void os_long(ostream &os, const csp::solution &solution)
{
    std::size_t solution_number = 0;
    for (const auto &record:solution.get_records())
    {
        std::string text;
        for (const auto &value:record)
        {
            text += "{" + std::to_string(value) + "}";
        }
        os
            << "Solution #"
            << std::setfill('0')
            << std::setw(3)
            << std::to_string(++solution_number)
            << " : "
            << text
            << std::endl;
    }
}

ostream &operator<<(ostream &os, const csp::solution &solution)
{
    os_short(os, solution);
    //    os_long(os << std::endl, solution);
    return os;
}

std::string tellHistory(const std::vector<csp::record> &history, std::size_t explore)
{
    std::stringstream os;
    if (history.size() > explore)
    {
        auto milestone = std::next(history.rbegin(), explore);
        os
            << "History at index "
            << std::distance(history.rend(), milestone)
            << "  :"
            << edit(history.rbegin(), milestone) << std::endl;
    }
    else
    {
        os << "History : " << edit(history.rbegin(), history.rend()) << std::endl;
    }

    return os.str();
}

string edit_fn(variable_vector::const_iterator first,
               variable_vector::const_iterator second, std::function<string(const csp::csp_variable &)> fn)
{
    std::stringstream os;
    os << "{size:" << std::to_string(std::distance(first, second)) << ",values:[";
    while (first != second)
    {
        os << fn(**first);
        first += 1;
        if (first != second)
        {
            os << ", ";
        }
    }
    os << "]}";
    return os.str();
}

string edit(const const_iter_v &variable)
{
    return edit(**variable);
}