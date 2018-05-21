//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once

#include "../algorithm.h"
#include "record.h"

namespace csp
{

    class algorithm_forward_checking
            : public algorithm
    {
        void restrict(csp_variable_ptr variable, std::vector<csp::record> &history) const;

    public:
        std::vector<std::vector<size_t>> run(std::vector<csp_variable_ptr> &variables,
                                             const std::vector<std::unique_ptr<csp::csp_constraint>> &constraints,
                                             heuristic heuristic) const override;

        explicit algorithm_forward_checking(bool stop_at_first_result = true);

        void rollback_assignations(const csp::csp_variable &variable, std::vector<record> &history) const;
        void rollback_assignations(const csp_variable_ptr & variable, std::vector<record> &history) const;

        void release_automatic_assignations(std::vector<record> &vector) const;
    };
}

