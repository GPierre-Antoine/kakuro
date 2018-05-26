//
// Created by Pierre-Antoine on 26/05/2018.
//


#pragma once


#include <cstddef>
#include <utility>
#include <stack>
#include "../forward.h"

namespace csp
{

    class record;

    typedef std::pair<csp_constraint_ptr, record> couple;

    class history
    {
        std::stack<couple> record_track{};
    public:
        history() = default;
        history(const history &) = delete;
        void track(const csp_constraint_ptr &constraint, csp::record &&r);
        bool empty();
        void pop();
        couple &top();
        csp_constraint_ptr &get_constraint();
        record &get_record();
        const csp_variable_ptr get_variable();
        bool has_constraint();
    };

}
