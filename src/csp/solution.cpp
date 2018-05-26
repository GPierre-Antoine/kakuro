//
// Created by Pierre-Antoine on 26/05/2018.
//


#include "solution.h"
#include "csp_variable.h"
#include "../ostream.h"

csp::solution::solution(std::size_t variable_count, const csp::algorithm &algo, const csp::heuristic &heuristic)
    : variable_count(variable_count),
      algorithm_info(edit(algo)),
      heuristic_name(edit(heuristic)),
      constraint_count(0),
      node_count(0)
{
}
csp::solution::solution(csp::solution &&previous) noexcept
    : variable_count(previous.variable_count),
      algorithm_info(previous.algorithm_info),
      heuristic_name(previous.heuristic_name)
{
    swap(*this, previous);
}
void csp::solution::start_chrono()
{
    this->start_time = clock();
}

void csp::solution::stop_chrono()
{
    this->end_time = clock();
}

void csp::solution::add_record(const variable_vector &variables)
{
    std::vector<std::size_t> affectation(variables.size());
    for (const auto &v : variables)
    {
        affectation[v->get_id()] = v->get_value();
    }
    records.push_back(affectation);
}

std::clock_t csp::solution::get_execution_time() const
{
    return (end_time - start_time);
}
size_t csp::solution::get_constraint_count() const
{
    return constraint_count;
}
void csp::solution::inc_constraint_count()
{
    constraint_count += 1;
}

void csp::solution::inc_node_count()
{
    node_count += 1;
}

size_t csp::solution::get_node_count() const
{
    return node_count;
}
const std::vector<std::vector<std::size_t>> &csp::solution::get_records() const
{
    return records;
}
