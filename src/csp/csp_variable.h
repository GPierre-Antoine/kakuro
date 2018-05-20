//
// Created by Pierre-Antoine on 19/05/2018.
//


#pragma once

#include <cstddef>
#include <iostream>
#include <vector>

typedef std::vector<std::size_t> domain_t;

namespace csp
{
    class csp_variable
    {
    private:
        std::size_t id;

        domain_t domain{1, 2, 3, 4, 5, 6, 7, 8, 9};

        typename domain_t::const_iterator value{nullptr};
        typename domain_t::iterator domain_start;

        typename domain_t::iterator get_free_iterator(const std::size_t &index);
        typename domain_t::iterator get_locked_iterator(const std::size_t &index);
    public:
        explicit csp_variable(const std::size_t &s);

        std::size_t get_id() const;
        typename std::pair<domain_t::const_iterator, domain_t::const_iterator> get_domain() const;

        void set_value(const std::size_t &index);
        void get_first_as_value();
        std::size_t get_value() const;
        bool is_valuated() const;

        std::size_t get_available_domain_size() const;
        void restrict(const std::size_t &index);
        void restrict_first();
        void release(const std::size_t &index);
        void release_last();
        void release_all();
    };

    std::ostream &operator<<(std::ostream &f, const csp::csp_variable &var);
}
