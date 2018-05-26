//
// Created by pierreantoine on 24/05/18.
//

#ifndef KAKURO_ALGO_FC_2_H
#define KAKURO_ALGO_FC_2_H


#include "../algorithm.h"

namespace csp
{
    class algo_forward_checking : public algorithm
    {
    public:
        explicit algo_forward_checking(bool stop_at_first_result);
        std::vector<std::vector<size_t>> run(variable_vector &variables, const constraint_vector &constraints, heuristic heuristic) const override ;
    };
}


#endif //KAKURO_ALGO_FC_2_H
