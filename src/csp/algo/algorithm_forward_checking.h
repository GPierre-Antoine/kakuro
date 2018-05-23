//
// Created by pierreantoine on 22/05/18.
//

#ifndef KAKURO_ALGORITHM_FORWARD_CHECKING_2_H
#define KAKURO_ALGORITHM_FORWARD_CHECKING_2_H


#include "../algorithm.h"

namespace csp
{
    class algorithm_forward_checking : public algorithm
    {
        void release_automatic_assignations(std::vector<record> &vector) const;
        void restrict(csp_variable_ptr variable, std::vector<csp::record> &history, std::size_t value, std::size_t counter) const;
        csp_variable_ptr record_auto(const csp_constraint & constraint, std::vector<csp::record> &history, std::size_t counter) const;

    public:
        std::vector<std::vector<std::size_t>> run(variable_vector &variables, const constraint_vector &constraints,
                                                                                     heuristic heuristic) const override;

        explicit algorithm_forward_checking(bool continue_after_first);
        void rollback_assignations(const csp_variable_ptr &variable, std::vector<csp::record> &history) const;
        void rollback_assignations(const csp::csp_variable &variable, std::vector<record> &history) const;
    };
}


#endif //KAKURO_ALGORITHM_FORWARD_CHECKING_2_H
