//
// Created by Pierre-Antoine on 19/05/2018.
//


#include "csp_constraint.h"

bool csp::csp_constraint::is_valuated() const
{
    for (const auto &i : variables)
    {
        if (!i->is_valuated())
        {
            return false;
        }
    }
    return true;
}

csp::csp_constraint::csp_constraint(std::size_t id) : id(id)
{

}

bool csp::csp_constraint::has_only_one_variable_unvaluated_left() const
{
    std::size_t counter{0};
    for (const auto &i:variables)
    {
        if (!i->is_valuated())
        {
            ++counter;
        }
    }
    return counter == 1;
}
bool csp::csp_constraint::has_a_empty_variable() const
{
    for (const auto &variable:variables)
    {
        if (variable->has_empty_domain())
        {
            return true;
        }
    }
    return false;
}

csp_variable_ptr csp::csp_constraint::get_last_unvaluated_variable() const
{
    if (!has_only_one_variable_unvaluated_left())
    {
        throw std::runtime_error("More than one variable left");
    }
    for (auto &i:variables)
    {
        if (!i->is_valuated())
        {
            return i;
        }
    }
    // impossible
    return nullptr;
}
csp_variable_ptr csp::csp_constraint::run_fc() const
{
    if (!has_only_one_variable_unvaluated_left())
    {
        throw std::runtime_error("More than one variable left");
    }
    return run_fc_child();
}
bool csp::csp_constraint::is_satisfied() const
{
    return run_constraint();
}
std::vector<csp_variable_ptr>::const_iterator csp::csp_constraint::cbegin() const
{
    return variables.cbegin();
}
std::vector<csp_variable_ptr>::const_iterator csp::csp_constraint::cend() const
{
    return variables.cend();
}
void csp::csp_constraint::add_variable(csp_variable_ptr variable)
{
    variables.push_back(variable);
}

