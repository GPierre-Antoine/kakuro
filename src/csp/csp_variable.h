//
// Created by Pierre-Antoine on 19/05/2018.
//


#pragma once

#include <cstddef>
#include <iostream>
#include <vector>
#include <utility>
#include <memory>

#include "../forward.h"

typedef std::vector<std::size_t> domain_t;
namespace csp
{
    class record;

    class csp_variable
    {
    private:
        std::size_t id;

        domain_t domain{1, 2, 3, 4, 5, 6, 7, 8, 9};

        std::size_t domain_start;
        bool valuated;

        constraint_vector constraints;

        typename domain_t::iterator get_free_iterator(const std::size_t &index);
    public:

        void reset();
        explicit csp_variable(const std::size_t &s);
        csp_variable(const csp_variable &other);

        void unvaluate();

        std::size_t get_id() const;

        void assign_first_element_as_value();
        bool is_valuated() const;
        std::size_t get_value() const;

        std::size_t get_available_size() const;
        bool has_empty_domain() const;

        void restrict(const std::size_t &index);
        void restrict_not(const std::size_t &index);

        void restrict_first();
        void release_last(std::size_t);
        void release_all();
        void add_constraint(csp_constraint_ptr);
        constraint_vector &get_constraints();
        std::size_t get_constraint_count() const;

        typename domain_t::const_iterator cbegin() const;
        typename domain_t::const_iterator cend() const;
        double dom_deg() const;
    };
}


#include "compare_variables.h"