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
#include "csp_constraint.h"
#include <chrono>
#include <thread>
#include <cassert>
#include "algo/record.h"

#include "../ostream.h"

csp::csp_variable::csp_variable(const std::size_t &s) : id(s), domain_start(0), valuated(false)
{
}

double csp::csp_variable::dom_deg() const
{
    return static_cast<double>(get_available_size())/std::max(1ul,get_constraint_count());
}

std::size_t csp::csp_variable::get_id() const
{
    return id;
}

std::size_t csp::csp_variable::get_value() const
{
    if (!is_valuated())
    {
        throw std::runtime_error("Unvaluated variable " + std::to_string(get_id()) + " : " + edit(*this));
    }
    return *(std::next(domain.begin(),domain_start));
}

bool csp::csp_variable::is_valuated() const
{
    return !has_empty_domain() && valuated;
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
    if (domain_start == 0)
    {
        return;
    }
    domain_start -= 1;
    valuated=false;
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
        throw std::runtime_error("Empty domain for variable " + std::to_string(get_id()) + " : " + edit(*this));
    }
    valuated = true;
}

void csp::csp_variable::release_all()
{
    domain_start = 0;
    unvaluate();
}

csp::csp_variable::csp_variable(const csp::csp_variable &other)
    : id(other.get_id()), domain_start(other.domain_start), valuated(other.valuated), constraints()
{

}

void csp::csp_variable::restrict(const std::size_t &index)
{

    auto it = get_free_iterator(index);
    if (it == domain.end())
    {
        //value is locked
        return;
    }
    auto d = std::next(domain.begin(), domain_start);
    if (it != d)
    {
        std::iter_swap(it, d);
    }
    restrict_first();
}

void csp::csp_variable::restrict_not(const std::size_t &index)
{
    auto it = get_free_iterator(index);
    auto correction = 1;
    if (it == domain.end())
    {
        correction = 0;
    }
    else
    {
        std::iter_swap(it, std::prev(domain.end()));
    }

    while (get_available_size() - correction)
    {
        restrict_first();
    }

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

void csp::csp_variable::reset()
{
    std::sort(domain.begin(), domain.end());
    unvaluate();
}

std::size_t csp::csp_variable::get_constraint_count() const
{
    return reduce<typename constraint_vector::const_iterator, std::size_t, csp_constraint_ptr>(constraints.cbegin(), constraints.cend(), 0u, [](unsigned i, const csp_constraint_ptr &constraint)
    {
        return i + !constraint->is_valuated();
    });
}

void csp::csp_variable::unvaluate()
{
    valuated = false;
}
void csp::csp_variable::add_constraint(csp_constraint_ptr ptr)
{
    constraints.push_back(ptr);
}
