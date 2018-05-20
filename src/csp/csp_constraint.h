//
// Created by Pierre-Antoine on 19/05/2018.
//


#pragma once

#include <vector>
#include <initializer_list>

#include "csp_variable.h"
typedef std::vector<csp::csp_variable*> variable_ref;

namespace csp
{
    class csp_constraint
    {
    public:
        const std::size_t sum;
        const variable_ref associated_variables;
        bool associated_variable_are_valuated() const;
        explicit csp_constraint(variable_ref & vector, std::size_t sum = 0);
        bool run_constraint() const;
        bool constraint_diff() const;
        bool constraint_sum() const;
    };

    std::ostream& operator<<(std::ostream&f, const csp::csp_constraint&constraint);
}
