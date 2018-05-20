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

#include "algo/record.h"

csp::csp_variable::csp_variable(const std::size_t &s) : id(s), domain_start(domain.begin())
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
        std::cerr << (get_id()) << std::endl;
        std::string error("Empty Domain for variable " + get_id());
        throw std::runtime_error(error);
    }
    return *value;
}
bool csp::csp_variable::is_valuated() const
{
    return domain.begin() <= domain_start && domain_start <= value && value < domain.end();
}

bool csp::csp_variable::restrict(const std::size_t &index)
{
    auto it = get_free_iterator(index);
    if (it == domain.end())
    {
        //value is locked
        return false;
    }
    if (it != domain_start)
    {
        std::iter_swap(it, domain_start);
    }
    restrict_first();
    return true;
}

void csp::csp_variable::restrict_first()
{
    std::advance(domain_start, 1);
}

void csp::csp_variable::release_last()
{
    std::advance(domain_start, -1);
}

typename domain_t::iterator csp::csp_variable::get_free_iterator(const std::size_t &index)
{
    return std::find(domain_start, domain.end(), index);
}
typename domain_t::iterator csp::csp_variable::get_locked_iterator(const std::size_t &index)
{
    return std::find(domain.begin(), domain_start, index);
}
std::size_t csp::csp_variable::get_available_domain_size() const
{
    return domain.end() - domain_start - 1;
}
void csp::csp_variable::set_value(const std::size_t &index)
{
    auto it = get_free_iterator(index);
    if (it == domain.end())
    {
        throw std::runtime_error("Out of bound value");
    }
    if (it != domain_start)
    {
        std::iter_swap(it, domain.end());
    }
    value = domain.end();
}

void csp::csp_variable::get_first_as_value()
{
    if (get_available_domain_size() == 0)
    {
        throw std::runtime_error("Empty domain for variable " + std::to_string(get_id()));
    }
    value = domain_start;
}
void csp::csp_variable::release_all()
{
    domain_start = domain.begin();
    value = domain.cend();
}
csp::csp_variable::csp_variable(const csp::csp_variable &other) : id(other.get_id())
{

}

bool csp::csp_variable::restrict_not(const std::size_t &index, std::vector<csp::record> &vector)
{
    auto it = std::find(domain_start, domain.end(), index);
    auto correction = 0;
    if (it != domain.end())
    {
        std::iter_swap(it, std::prev(domain.end(), 1));
        correction = 1;
    }

    while (get_available_domain_size() - correction > 0)
    {
        restrict_first();
        vector.emplace_back(record(record_type::automatic, *this));
    }
    return get_available_domain_size() == 1;
}



