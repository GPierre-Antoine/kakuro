//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once


#include "record_type.h"
#include "../csp_variable.h"

namespace csp
{
    class record
    {
        record_type type;
        csp_variable* variable;
    public:
        record(record_type type, csp_variable&variable);
        record&operator=(const record& r) = default;
        bool is_manual () const;
        csp_variable* get_record() const;
        void forget();
        ~record();
    };
}

