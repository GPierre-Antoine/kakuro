//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once


#include <cstddef>
#include <memory>
#include <vector>
#include <functional>

#include "csp_variable.h"
#include "csp_constraint.h"

#include "../typedefs.h"

namespace csp
{
    class algorithm
    {
    protected:
        void record_solution(std::vector<std::vector<std::size_t>> & affectations, const std::vector<csp_variable_ptr> &variables) const;
    public:
        const std::string name;
        const bool stop_at_first_result;
        virtual std::vector<std::vector<size_t>> run(std::vector<csp_variable_ptr> &variables, const std::vector<std::unique_ptr<csp::csp_constraint>>&constraints, heuristic heuristic) const=0;
        explicit algorithm(std::string name, bool stop_at_first_result = true);
    };
}

