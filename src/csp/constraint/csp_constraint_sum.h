//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once


#include "../csp_constraint.h"

namespace csp
{
    class csp_constraint_sum : public csp_constraint
    {
    protected:
        csp_variable_ptr run_fc_child() const override;
    public:
        const std::size_t sum;
        csp_constraint_sum(std::size_t id, size_t sum);
        std::string edit() const override;
        bool run_constraint() const override;
    };
}

