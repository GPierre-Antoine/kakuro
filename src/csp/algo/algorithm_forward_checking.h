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
        std::vector<std::vector<size_t>> run(std::vector<std::shared_ptr<csp::csp_variable>> &variables,
                                             const std::vector<std::unique_ptr<csp::csp_constraint>> &constraints,
                                             const std::function<bool(const csp_variable_ptr &,
                                                                      const csp_variable_ptr &)> &heuristic) const override;

        explicit algorithm_forward_checking(bool stop_at_first_result = true);

        void rollback_assignations(const csp::csp_variable &variable, std::vector<record> &vector) const;
        void rollback_assignations(const std::shared_ptr<csp_variable> &variable, std::vector<record> &vector) const;

        void release_automatic_assignations(std::vector<record> &vector) const;
    };
}

