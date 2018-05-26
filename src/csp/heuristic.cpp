//
// Created by Pierre-Antoine on 26/05/2018.
//


#include "heuristic.h"
csp::heuristic::heuristic(std::string name, heuristic_f function) : name(name), function(function)
{

}
long csp::heuristic::operator()(const csp_variable_ptr &v) const
{
    return function(v);
}
