//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "algorithm.h"

void csp::algorithm::record_solution(std::vector<std::vector<std::size_t>> &affectations,
                                     const std::vector<csp::csp_variable> &variables) const
{
    std::vector<std::size_t> affectation(variables.size());
    for (const auto &v : variables)
    {
        affectation[v.get_id()] = v.get_value();
    }
    affectations.push_back(affectation);
}
