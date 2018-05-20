//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once

#include "../algorithm.h"
namespace csp
{
    class algorithm_forward_checking
        : public algorithm
    {
    public:
        virtual std::vector<std::vector<size_t>> run(std::vector<csp::csp_variable> &variables,
                                                     const std::vector<csp::csp_constraint> &constraints) const override;

    };
}

