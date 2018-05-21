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
        record_type type;
        csp_variable *variable;
    public:
        friend void swap(record&f,record&s){
            std::swap(f.type,s.type);
            std::swap(f.variable,s.variable);
        }
        record(record_type type, csp_variable & variable);
        record(record && r) noexcept ;
        record&operator=(const record& r) = default;
        bool is_manual () const;
        const csp::csp_variable & get_record() const;
        bool is_same_variable(const csp_variable &variable) const;
        void forget();
        ~record();

    };

}

