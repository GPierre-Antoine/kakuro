//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "algorithm_forward_checking.h"
std::vector<std::vector<size_t>> csp::algorithm_forward_checking::run(std::vector<csp::csp_variable> &variables,
                                                                      const std::vector<csp::csp_constraint> &constraints) const
{
    for (auto&i:variables)
        i.release_all();

    auto it_variable = variables.begin();
    std::vector<std::vector<size_t>> solutions;
    return  solutions;
}
