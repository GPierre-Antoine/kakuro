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
        csp_variable_ptr run_fc_child() const override;
    public:
        explicit csp_constraint_difference(std::size_t id);
        std::string edit() const override;
        bool run_constraint() const override;
    };
}

