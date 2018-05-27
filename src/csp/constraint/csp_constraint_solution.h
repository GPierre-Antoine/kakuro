//
// Created by Pierre-Antoine on 27/05/2018.
//


#pragma once


#include "../csp_constraint.h"

namespace csp
{
    class csp_constraint_solution
        : public csp::csp_constraint, public std::enable_shared_from_this<csp_constraint_solution>
    {
        std::vector<std::size_t> values;
    protected:
        csp_variable_ptr run_fc_child() const override;
    public:
        void resize(std::size_t size);
        void add(csp_variable_ptr variable);
        std::string edit() const override;
        explicit csp_constraint_solution(size_t);
        bool run_constraint() const override;

    };
}

