//
// Created by pierreantoine on 22/05/18.
//

#ifndef KAKURO_ALGORITHM_FORWARD_CHECKING_2_H
#define KAKURO_ALGORITHM_FORWARD_CHECKING_2_H


#include "algorithm_forward_checking.h"

namespace csp
{
    class algorithm_forward_checking_2 : public algorithm_forward_checking
    {
    public:
        std::vector<std::vector<std::size_t>> run(std::vector<csp_variable_ptr> &variables,
                                                                                     const std::vector<std::unique_ptr<csp::csp_constraint>> &constraints,
                                                                                     heuristic heuristic) const override;

        explicit algorithm_forward_checking_2(bool continue_after_first);
    };
}


#endif //KAKURO_ALGORITHM_FORWARD_CHECKING_2_H
