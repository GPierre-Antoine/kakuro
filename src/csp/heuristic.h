//
// Created by Pierre-Antoine on 26/05/2018.
//


#pragma once


#include <string>
#include "../typedefs.h"
namespace csp
{
    class heuristic
    {
    public:
        const std::string name;
        const heuristic_f function;
        heuristic(std::string name, heuristic_f function);
        long operator()(const csp_variable_ptr &) const;
    };
}