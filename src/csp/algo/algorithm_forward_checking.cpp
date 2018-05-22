//
// Created by Pierre-Antoine on 20/05/2018.
//


#include <algorithm>
#include <cstddef>

#include "../../ostream.h"
#include "algorithm_forward_checking.h"


void csp::algorithm_forward_checking::rollback_assignations(const csp_variable_ptr &variable,
                                                            std::vector<csp::record> &history) const
{
    release_automatic_assignations(history);
    rollback_assignations((*variable), history);
}

std::vector<std::vector<std::size_t>> csp::algorithm_forward_checking::run(std::vector<csp_variable_ptr> &variables,
                                                                           const std::vector<std::unique_ptr<csp::csp_constraint>> &constraints,
                                                                           heuristic heuristic) const
{


    for (auto &i:variables)
    {
        i->release_all();
    }

    auto history = std::vector<record>();
    history.reserve(1000);

    auto iterator = variables.begin();
    std::vector<std::vector<size_t>> solutions;

    std::size_t counter = 0;

    while (true)
    {
        cout << "Iteration : " << ++counter << ", current : " << *iterator << endl;
        bool met_error = false;


        //si la variable courante à un domaine vide
        //on rollback les assignations et on revient à la précédente
        //et on verrouille le resultat courant
        //on recommence
        cout << variables << endl;
        if ((*iterator)->has_empty_domain())
        {
            if (iterator == variables.begin())
            {
                break;
            }
            cout << variables << endl;
            rollback_assignations(*iterator, history);
            cout << variables << endl;
            if ((*iterator)->has_empty_domain())
            {
                std::advance(iterator, -1);
            }
            restrict(*iterator, history);
            continue;
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
                //si une
                auto variable_ptr = constraint->get_last_unvaluated_variable();
                auto domain_size_before_filter = variable_ptr->get_available_size();
                if (domain_size_before_filter > 1)
                {
                    constraint->run_fc();
                    for (auto it = variables.begin(); it != iterator && !met_error; std::advance(it, 1))
                    {
                        if (!(*it)->is_valuated())
                        {
                            cout << "met error : " << *it << endl;
                            iterator = it;
                            met_error = true;
                        }
                    }
                    for (auto it = std::next(iterator); it != variables.cend() && !met_error; std::advance(it, 1))
                    {
                        if ((*it)->has_empty_domain())
                        {
                            cout << "met error : " << *it << endl;
                            met_error = true;
                        }
                    }

                }
            }
            if (met_error)
            {
                rollback_assignations(*iterator,history);
                restrict(*iterator,history);
                break;
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

void csp::algorithm_forward_checking::restrict(csp_variable_ptr variable, std::vector<csp::record> &history) const
{
    if (!variable->get_available_size())
    {
        return;
    }
    variable->restrict_first();
    history.emplace_back(record(record_type::manual, variable));
}

void csp::algorithm_forward_checking::release_automatic_assignations(std::vector<csp::record> &vector) const
{
    while (!vector.empty() && !vector.back().is_manual())
    {
        vector.pop_back();
    }
}

void csp::algorithm_forward_checking::rollback_assignations(const csp::csp_variable &variable,
                                                            std::vector<csp::record> &history) const
{
    while (!history.empty() && history.back().is_manual() && !history.back().is_same_variable(variable))
    {
        history.pop_back();
    }
}

csp::algorithm_forward_checking::algorithm_forward_checking(bool stop_at_first_result) : algorithm(std::string(
    "Forward Checking"), stop_at_first_result)
{

}