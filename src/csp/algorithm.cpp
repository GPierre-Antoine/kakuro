//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "algorithm.h"

void csp::algorithm::record_solution(std::vector<std::vector<std::size_t>> &solutions,
                                     const std::vector<csp::csp_variable> &variables) const
{
    std::vector<std::size_t> solution(variables.size());
    for (const auto &v : variables)
    {
        solution[v.get_id()] = v.get_value();
    }
    solutions.push_back(solution);
}
