//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once


#include "../algorithm.h"
namespace csp
{
    class algorithm_backtrack : public algorithm
    {
    public:
        std::vector<std::vector<size_t>> run(std::vector<csp_variable_ptr> &variables, const std::vector<std::unique_ptr<csp::csp_constraint>>&constraints,
                                             heuristic heuristic) const override;
        explicit algorithm_backtrack(bool stop_at_first_result = true);
    };
}

