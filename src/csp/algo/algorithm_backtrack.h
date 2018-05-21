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
        std::vector<std::vector<size_t>> run(std::vector<std::shared_ptr<csp::csp_variable>> &variables, const std::vector<std::unique_ptr<csp::csp_constraint>>&constraints,
                                                     const std::function<bool(const csp_variable_ptr&,const csp_variable_ptr&)> & heuristic) const override;
        explicit algorithm_backtrack(bool stop_at_first_result = true);
    };
}

