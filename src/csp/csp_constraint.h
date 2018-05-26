//
// Created by Pierre-Antoine on 19/05/2018.
//


#pragma once

#include <vector>
#include <initializer_list>
#include <memory>

#include "csp_variable.h"
#include "algo/record.h"

namespace csp
{
    class csp_constraint
    {
    protected:
        virtual csp_variable_ptr run_fc_child() const=0;
        std::vector<csp_variable_ptr> associated_variables{};
    public:
        const std::size_t id;
        virtual std::string edit()const = 0;

        bool is_valuated() const;
        bool is_satisfied() const;
        bool has_only_one_variable_unvaluated_left() const;

        csp_variable_ptr get_last_unvaluated_variable() const;
        csp_variable_ptr run_fc() const;

        void add_variable(csp_variable_ptr variable);

        std::vector<csp_variable_ptr>::const_iterator cbegin() const;
        std::vector<csp_variable_ptr>::const_iterator cend() const;

        explicit csp_constraint(std::size_t);
        virtual bool run_constraint() const=0;
    };
}
