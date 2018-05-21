//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "algorithm.h"

void csp::algorithm::record_solution(std::vector<std::vector<std::size_t>> &affectations,
                                     const std::vector<csp_variable_ptr> &variables) const
{
    std::vector<std::size_t> affectation(variables.size());
    for (const auto &v : variables)
    {
        affectation[v->get_id()] = v->get_value();
    }
    affectations.push_back(affectation);
}
csp::algorithm::algorithm(std::string name, bool stop_at_first_result) : name(name), stop_at_first_result(stop_at_first_result)
{

}
