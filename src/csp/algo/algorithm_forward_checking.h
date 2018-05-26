//
// Created by pierreantoine on 24/05/18.
//

#ifndef KAKURO_ALGO_FC_2_H
#define KAKURO_ALGO_FC_2_H


#include "../algorithm.h"
#include "../heuristic.h"

namespace csp
{
    class algorithm_forward_checking : public algorithm
    {
    public:
        explicit algorithm_forward_checking(bool find_all_results);
        solution run(variable_vector &variables, constraint_vector &constraints,
                     heuristic heuristic) const override;
    };
}


#endif //KAKURO_ALGO_FC_2_H
