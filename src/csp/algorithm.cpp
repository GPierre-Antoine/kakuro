//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "algorithm.h"
#include <utility>
#include "../ostream.h"

void csp::algorithm::record_solution(std::vector<std::vector<std::size_t>> &affectations,
                                     const variable_vector &variables) const
{
    std::vector<std::size_t> affectation(variables.size());
    for (const auto &v : variables)
    {
        affectation[v->get_id()] = v->get_value();
    }
    affectations.push_back(affectation);
}
csp::algorithm::algorithm(std::string name, bool stop_at_first_result) : name(std::move(name)), stop_at_first_result(stop_at_first_result)
{

}
iter_v csp::algorithm::get_lowest_variable(iter_v begin, iter_v end, heuristic h) const
{
    auto ref=begin;
    while (begin!=end){
        if (h(*ref)>h(*begin)){
            ref=begin;
        }
        std::advance(begin,1);
    }
    return ref;
}
