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
        virtual std::shared_ptr<csp::csp_variable> run_fc_child(std::vector<csp::record>& r) const=0;

    public:
        virtual std::string edit()const = 0;
        const std::vector<std::shared_ptr<csp::csp_variable>> associated_variables;

        bool is_valuated() const;
        bool is_satisfied() const;
        bool has_only_one_variable_unvaluated_left() const;

        std::shared_ptr<csp::csp_variable> get_last_unvaluated_variable() const;

        std::shared_ptr<csp::csp_variable> run_fc(std::vector<csp::record>& r) const;

        std::vector<std::shared_ptr<csp::csp_variable>>::const_iterator cbegin() const;
        std::vector<std::shared_ptr<csp::csp_variable>>::const_iterator cend() const;


        explicit csp_constraint(std::vector<std::shared_ptr<csp::csp_variable>> & vector);
        virtual bool run_constraint() const=0;
    };
}
