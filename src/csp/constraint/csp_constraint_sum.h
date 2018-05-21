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
        std::shared_ptr<csp::csp_variable> run_fc_child(std::vector<record>&history) const override;
    public:
        const std::size_t sum;
        csp_constraint_sum(std::vector<std::shared_ptr<csp::csp_variable>> &vector, size_t sum);
        std::string edit() const override;
        bool run_constraint() const override;
    };
}

