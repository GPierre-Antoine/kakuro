//
// Created by Pierre-Antoine on 20/05/2018.
//

#include <algorithm>

#include <iostream>
using std::cout;
using std::endl;


#include "csp_constraint_sum.h"

csp::csp_constraint_sum::csp_constraint_sum(std::vector<std::shared_ptr<csp::csp_variable>> &vector, std::size_t sum)
    : csp_constraint(vector), sum(sum)
{

}

bool csp::csp_constraint_sum::run_constraint() const
{
    std::size_t accumulation = 0;
    for (const auto &i:associated_variables)
    {
        accumulation += i->get_value();
    }
    return sum == accumulation;
}
std::shared_ptr<csp::csp_variable> csp::csp_constraint_sum::run_fc_child(std::vector<csp::record> &history) const
{
    auto free = get_last_unvaluated_variable();
    std::size_t partial_sum = 0u;
    for (const auto &i:associated_variables)
    {
        if (i->is_valuated())
        {
            partial_sum += i->get_value();
        }
    }
    std::size_t expected_value = static_cast<std::size_t >(std::max(static_cast<long>(sum - partial_sum), 0l));
    free->restrict_not(expected_value, history);
    return free;
}
std::string csp::csp_constraint_sum::edit() const
{
    auto text= "Sum Constraint ("
        + std::to_string(this->sum)
        + ") "
        + (this->is_valuated() ? "{valuated}" : "{unvaluated}");
    if (this->is_valuated())
    {
        text+= this->is_satisfied() ? "{satisfied}":"{unsatisfied}";
    }
    return text;
}
