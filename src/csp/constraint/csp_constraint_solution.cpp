//
// Created by Pierre-Antoine on 27/05/2018.
//


#include "csp_constraint_solution.h"

csp::csp_constraint_solution::csp_constraint_solution(size_t id) : csp_constraint(id)
{

}
csp_variable_ptr csp::csp_constraint_solution::run_fc_child() const
{
    auto free = get_last_unvaluated_variable();
    free->restrict(values[free->get_id()]);
    return free;
}
std::string csp::csp_constraint_solution::edit() const
{
    return std::string("Solution");
}
void csp::csp_constraint_solution::resize(std::size_t size)
{
    values.resize(size);
}
void csp::csp_constraint_solution::add(csp_variable_ptr variable)
{
    values[variable->get_id()] = variable->get_value();
    add_variable(variable);
    variable->add_constraint(shared_from_this());
}
bool csp::csp_constraint_solution::run_constraint() const
{
    for (const auto &i:variables)
    {
        if (i->get_value() != values[i->get_id()])
        {
            return true;
        }
    }
    return false;
}
