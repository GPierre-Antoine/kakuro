//
// Created by Pierre-Antoine on 26/05/2018.
//


#include "history.h"

#include "csp_constraint.h"

void csp::history::track(const csp_constraint_ptr &constraint, csp::record &&r)
{
    record_track.emplace(couple(constraint, std::move(r)));
}

bool csp::history::empty() const
{
    return record_track.empty();
}
void csp::history::pop()
{
    record_track.pop();
}
csp::couple &csp::history::top()
{
    return record_track.top();
}

csp_constraint_ptr &csp::history::get_constraint()
{
    if (!has_constraint())
    {
        throw std::runtime_error(std::string("History : No constraints") + (empty() ? "(empty)" : ""));
    }
    return record_track.top().first;
}

csp::record &csp::history::get_record()
{
    if (empty())
    {
        throw std::runtime_error(std::string("History : empty"));
    }
    return record_track.top().second;
}

bool csp::history::has_constraint()
{
    return !empty() && (record_track.top().first != nullptr);
}
const csp_variable_ptr csp::history::get_variable()
{
    return get_record().get_variable();
}
csp::history::operator bool() const
{
    return !empty();
}
