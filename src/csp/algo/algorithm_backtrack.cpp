//
// Created by Pierre-Antoine on 20/05/2018.
//


#include <memory>
#include <algorithm>
#include "../../ostream.h"
#include "algorithm_backtrack.h"

csp::solution csp::algorithm_backtrack::run(variable_vector &variables,
                                            const constraint_vector &constraints,
                                            heuristic heuristic) const
{
    for (auto &i:variables)
    {
        i->release_all();
    }

    auto it_variable = variables.begin();

    csp::solution tracker = solution(variables.size(), *this, heuristic);
    tracker.start_chrono();
    while (true)
    {
        tracker.inc_node_count();
        auto it = get_lowest_variable(it_variable, variables.end(), heuristic);
        if (it_variable != it)
        {
            std::iter_swap(it_variable, it);
        }

        if (it_variable == variables.end())
        {
            break;
        }

        //si variable courante a domaine vide
        if ((*it_variable)->has_empty_domain())
        {
            //si variable est la première on arrete BT
            if (it_variable == variables.begin())
            {
                break;
            }
            //sinon, on libère le domaine et on retourne à la variable précédente, puis on repart du début de la boucle
            (*it_variable)->release_all();
            it_variable = std::prev(it_variable, 1);
            (*it_variable)->restrict_first();
            continue;
        }
        //on assigne une valeur à la variable
        (*it_variable)->assign_first_element_as_value();


        //on vérifie toutes les contraintes
        bool met_error = false;
        for (const auto &constraint : constraints)
        {
            tracker.inc_constraint_count();
            if (constraint->is_valuated() && !constraint->is_satisfied())
            {
                met_error = true;
                break;
            }
        }

        //si il y a eu une erreur, on exclue la valeur courante, et on repart du début de la boucle
        if (met_error)
        {
            (*it_variable)->restrict_first();
            continue;
        }

        it_variable = std::next(it_variable, 1);
        if (it_variable == variables.end())
        {
            tracker.add_record(variables);
            if (stop_at_first_result)
            {
                break;
            }
            it_variable = std::prev(it_variable, 1);
            (*it_variable)->restrict_first();
        }
    }
    tracker.stop_chrono();
    return std::move(tracker);
}

csp::algorithm_backtrack::algorithm_backtrack(bool stop_at_first_result) : algorithm(std::string("Backtrack"),
                                                                                     stop_at_first_result)
{

}
