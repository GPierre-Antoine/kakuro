//
// Created by Pierre-Antoine on 26/05/2018.
//


#include "history.h"

#include "csp_constraint.h"

void csp::history::track(const csp_constraint_ptr &constraint, csp::record &&r)
{
    record_track.push(std::make_pair(constraint->id, std::move(r)));
}
void csp::history::track(const constraint_vector::const_iterator &constraint, csp::record &&r)
{
    track(*constraint, std::move(r));
}
