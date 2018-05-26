//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once


#include "record_type.h"
#include "../csp_variable.h"
#include "../../typedefs.h"
#include <algorithm>

namespace csp
{

    class record
    {
    protected:
        record_type type;
        csp_variable_ptr variable;
    public:
        const std::size_t timestamp;
        const std::size_t count;
        friend void swap(csp::record &first, csp::record &second)
        {
            using std::swap;
            swap(first.type, second.type);
            swap(first.variable, second.variable);
        }
        record(record_type type, csp_variable_ptr variable, std::size_t timestamp, std::size_t count);
        record(const record &) = delete;
        record(record &&r) noexcept;

        bool is_manual() const;
        const csp_variable_ptr get_variable() const;
        void forget();
        ~record();
    };

}

