//
// Created by Pierre-Antoine on 19/05/2018.
//

#include <iostream>
#include <numeric>
#include <stdexcept>
#include <iterator>
#include <utility>
#include <algorithm>
#include "csp_variable.h"
#include <chrono>
#include <thread>
#include <cassert>
#include "algo/record.h"

csp::csp_variable::csp_variable(const std::size_t &s) : id(s), domain_start(0), value(9)
{
}

std::size_t csp::csp_variable::get_id() const
{
    return id;
}

std::size_t csp::csp_variable::get_value() const
{
    if (!is_valuated())
    {
        throw std::runtime_error("Empty Domain for variable " + std::to_string(get_id()));
    }
    return domain[value];
}

bool csp::csp_variable::is_valuated() const
{
    return domain_start <= value && value < domain.size();
}

void csp::csp_variable::restrict_first()
{
    if (domain_start == domain.size())
    {
        return;
    }
    domain_start += 1;
    unvaluate();
}

void csp::csp_variable::release_last()
{
    if (!domain_start)
    {
        return;
    }
    domain_start -= 1;
    unvaluate();
}

typename domain_t::iterator csp::csp_variable::get_free_iterator(const std::size_t &index)
{
    return std::find(std::next(domain.begin(), domain_start), domain.end(), index);
}

std::size_t csp::csp_variable::get_available_size() const
{
    return domain.size() - domain_start;
}

void csp::csp_variable::assign_first_element_as_value()
{
    if (has_empty_domain())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        throw std::runtime_error("Empty domain for variable " + std::to_string(get_id()));
    }
    value = domain_start;
}

void csp::csp_variable::release_all()
{
    domain_start = 0;
    value        = 9;
}

csp::csp_variable::csp_variable(const csp::csp_variable &other)
        : id(other.get_id()), domain_start(other.domain_start), value(other.value)
{

}

bool csp::csp_variable::restrict(const std::size_t &index, std::vector<record> &vector)
{

    auto it = get_free_iterator(index);
    if (it == domain.end())
    {
        //value is locked
        return false;
    }
    auto d = std::next(domain.begin(), domain_start);
    if (it != d)
    {
        std::iter_swap(it, d);
    }
    restrict_first();
    vector.emplace_back(record(record_type::automatic, *this));
    return true;
}

bool csp::csp_variable::restrict_not(const std::size_t &index, std::vector<csp::record> &vector)
{
    auto it = get_free_iterator(index);
    if (it == domain.end())
    {
        while (!has_empty_domain())
        {
            restrict_first();
            vector.emplace_back(record(record_type::automatic, *this));
        }
        return false;
    }
    std::iter_swap(it, std::prev(domain.end(), 1));

    auto size = get_available_size();

    while (size > 1)
    {
        restrict_first();
        size = get_available_size();
        std::cout << __LINE__ << std::endl;
        auto rec = record(record_type::automatic, *this);
        vector.emplace_back(std::move(rec));
        auto size2 = get_available_size();
        assert(size==size2);
    }
    return true;
}

bool csp::csp_variable::has_empty_domain() const
{
    return get_available_size() == 0;
}

typename domain_t::const_iterator csp::csp_variable::cbegin() const
{
    return std::next(domain.cbegin(), domain_start);
}

typename domain_t::const_iterator csp::csp_variable::cend() const
{
    return domain.cend();
}

void csp::csp_variable::unvaluate()
{
    value = domain.size();
}

void csp::csp_variable::reset()
{
    std::sort(domain.begin(), domain.end());
}