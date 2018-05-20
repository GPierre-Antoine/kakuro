//
// Created by Pierre-Antoine on 19/05/2018.
//


#pragma once

#include <vector>
#include <initializer_list>

#include "csp_variable.h"
#include "algo/record.h"

namespace csp
{
    class csp_constraint
    {
    public:
        const std::vector<csp::csp_variable*> associated_variables;

        bool associated_variable_are_valuated() const;
        bool one_variable_left_unvaluated() const;

        csp_variable* get_unvaluated_variable() const;

        void run_fc(std::vector<csp::record>& r) const;
        virtual void run_fc_child(std::vector<csp::record>& r) const=0;

        explicit csp_constraint(std::vector<csp::csp_variable*> & vector);
        virtual bool run_constraint() const=0;
    };
}
