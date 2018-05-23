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
        friend void swap(csp::record &first, csp::record &second)
        {
            using std::swap;
            swap(first.type, second.type);
            swap(first.variable,second.variable);
        }
        record(record_type type, csp_variable_ptr variable, std::size_t timestamp);
        record(record && r) noexcept ;
        record&operator=(const record& r) = default;
        bool is_manual () const;
        const csp_variable_ptr get_variable() const;
        bool is_same_variable(const csp_variable &variable) const;
        void forget();
        ~record();
    };

}

