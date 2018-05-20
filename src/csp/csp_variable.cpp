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

csp::csp_variable::csp_variable(const std::size_t &s) : id(s), domain_start(domain.begin())
{
}

std::size_t csp::csp_variable::get_id() const
{
    return id;
}

typename std::pair<domain_t::const_iterator, domain_t::const_iterator> csp::csp_variable::get_domain() const
{
    return make_pair(domain_start, domain.end());
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

void csp::csp_variable::restrict(const std::size_t &index)
{
    auto it = get_free_iterator(index);
    if (it == domain.end())
    {
        //value is locked
        return;
    }
    if (it != domain_start)
    {
        std::iter_swap(it, domain_start);
    }
    restrict_first();
}

void csp::csp_variable::restrict_first()
{
    domain_start += 1;
}

void csp::csp_variable::release(const std::size_t &index)
{
    auto it = get_locked_iterator(index);
    if (it == domain_start)
    {
        //value is free
        return;
    }
    std::iter_swap(it, domain_start);
    release_last();

}

void csp::csp_variable::release_last()
{
    domain_start -= 1;
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
        std::iter_swap(it, domain_start);
    }
    value = domain_start;
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

std::ostream &csp::operator<<(std::ostream &f, const csp::csp_variable &var)
{
    return f <<std::string("variable n°")
        + std::to_string(var.get_id())
        + " "
        + (var.is_valuated() ? "{" + std::to_string(var.get_value()) + "}" : " {}");
}

