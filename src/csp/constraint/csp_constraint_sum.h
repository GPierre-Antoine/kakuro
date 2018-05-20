//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once


#include "../csp_constraint.h"
namespace csp
{
    class csp_constraint_sum : public csp_constraint
    {
    public:
        const std::size_t sum;
        csp_constraint_sum(std::vector<csp::csp_variable *> &vector, size_t sum);
        bool run_constraint() const override;
        void run_fc_child(std::vector<record>&history) const override;
    };
}

