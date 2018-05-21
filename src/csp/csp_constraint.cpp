//
// Created by Pierre-Antoine on 19/05/2018.
//


#include "csp_constraint.h"

bool csp::csp_constraint::is_valuated() const
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

csp::csp_constraint::csp_constraint(std::vector<std::shared_ptr<csp::csp_variable>> &vector) : associated_variables(
    vector)
{

}

bool csp::csp_constraint::has_only_one_variable_unvaluated_left() const
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

std::shared_ptr<csp::csp_variable> csp::csp_constraint::get_last_unvaluated_variable() const
{
    if (!has_only_one_variable_unvaluated_left())
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
std::shared_ptr<csp::csp_variable> csp::csp_constraint::run_fc(std::vector<csp::record> &r) const
{
    if (!has_only_one_variable_unvaluated_left())
    {
        throw std::runtime_error("More than one variable left");
    }
    return run_fc_child(r);
}
bool csp::csp_constraint::is_satisfied() const
{
    return run_constraint();
}
std::vector<std::shared_ptr<csp::csp_variable>>::const_iterator csp::csp_constraint::cbegin() const
{
    return associated_variables.cbegin();
}
std::vector<std::shared_ptr<csp::csp_variable>>::const_iterator csp::csp_constraint::cend() const
{
    return associated_variables.cend();
}

