//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once

#include "../algorithm.h"
#include "record.h"
namespace csp
{
    class algorithm_forward_checking
        : public algorithm
    {
    void restrict(csp_variable &variable, std::vector<csp::record> &history, record_type type) const;
    public:
        virtual std::vector<std::vector<size_t>> run(std::vector<csp::csp_variable> &variables,
                                                     const std::vector<std::unique_ptr<csp::csp_constraint>> &constraints) const override;

        void release_automatic_assignations(typename std::vector<csp::csp_variable>::iterator & it_variable, std::vector<record> &vector) const;
    };
}

