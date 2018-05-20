//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once


#include "../csp_constraint.h"
namespace csp
{
    class csp_constraint_difference
        : public csp_constraint
    {
    protected:
        csp::csp_variable * run_fc_child(std::vector<record>&history) const override;
    public:
        explicit csp_constraint_difference(std::vector<csp_variable *> &vector);
        bool run_constraint() const override;
    };
}

