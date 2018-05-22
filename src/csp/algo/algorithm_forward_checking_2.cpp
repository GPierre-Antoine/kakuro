//
// Created by pierreantoine on 22/05/18.
//

#include "algorithm_forward_checking_2.h"
#include "../../ostream.h"

std::vector<std::vector<std::size_t>> csp::algorithm_forward_checking_2::run(std::vector<csp_variable_ptr> &variables,
                                                                             const std::vector<std::unique_ptr<csp::csp_constraint>> &constraints,
                                                                             heuristic heuristic) const
{


    for (auto &i:variables)
    {
        i->release_all();
    }

    auto history = std::vector<record>();
    history.reserve(1000);

    auto                             iterator = variables.begin();
    std::vector<std::vector<size_t>> solutions;

    std::size_t counter = 0;

    bool met_error = false;

    while (true)
    {
        cout << "Iteration : " << ++counter << ", current : " << *iterator << endl;

        met_error = met_error || (*iterator)->has_empty_domain();

        if (met_error)
        {
            //resolve error

            rollback_assignations(*iterator, history);

            if ((*iterator)->has_empty_domain())
            {
                if (iterator == variables.begin())
                {
                    break;
                }
                std::advance(iterator, -1);
            }
            restrict(*iterator, history);
            met_error = false;
        }

        //on met la variable la plus interessante devant
        std::sort(iterator, variables.end(), heuristic);

        //la variable considérée prend pour valeur la première valeur possible
        (*iterator)->assign_first_element_as_value();
        cout << variables << endl;

        //on verifie toutes les constantes

        for (const auto &constraint:constraints)
        {
            if (constraint->has_only_one_variable_unvaluated_left())
            {
                auto var = constraint->run_fc();
                if (var->has_empty_domain())
                {
                    cout << var << endl;
                    met_error = true;
                    break;
                }
            }
        }

        if (met_error)
        {
            continue;
        }

        std::advance(iterator, 1);

        if (iterator == variables.cend())
        {
            record_solution(solutions, variables);
            if (stop_at_first_result)
            {
                break;
            }
            std::advance(iterator, -1);
            restrict(*iterator, history);
        }
    }

    return solutions;
}

csp::algorithm_forward_checking_2::algorithm_forward_checking_2(bool continue_after_first) : algorithm_forward_checking(continue_after_first, "FC2")
{

}
