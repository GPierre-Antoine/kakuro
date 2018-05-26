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

    typedef std::pair<std::size_t, record> couple;

    class history
    {
        std::stack<couple> record_track;
    public:
        history(const history &) = delete;
        void track(const csp_constraint_ptr &constraint, csp::record &&r);
        void track(const constraint_vector::const_iterator &constraint, csp::record &&r);
    };

}
