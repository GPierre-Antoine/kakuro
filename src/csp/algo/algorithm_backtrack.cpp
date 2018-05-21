//
// Created by Pierre-Antoine on 20/05/2018.
//


#include <memory>
#include <algorithm>
#include "../../ostream.h"
#include "algorithm_backtrack.h"

std::vector<std::vector<size_t>> csp::algorithm_backtrack::run(std::vector<csp_variable_ptr> &variables,
                                                               const std::vector<std::unique_ptr<csp::csp_constraint>> &constraints,
                                                               heuristic heuristic) const
{
    for (auto &i:variables)
    {
        i->release_all();
    }

    auto it_variable = variables.begin();
    std::vector<std::vector<size_t>> solutions;

    while (true)
    {
        std::sort(it_variable,variables.end(),heuristic);

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
            record_solution(solutions, variables);
            if (stop_at_first_result)
                break;
            it_variable = std::prev(it_variable, 1);
            (*it_variable)->restrict_first();
        }
    }

    return solutions;
}

csp::algorithm_backtrack::algorithm_backtrack(bool stop_at_first_result) : algorithm(std::string("Backtrack"),stop_at_first_result)
{

}
