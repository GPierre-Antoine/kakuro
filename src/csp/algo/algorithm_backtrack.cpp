//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "algorithm_backtrack.h"

std::vector<std::vector<size_t>> csp::algorithm_backtrack::run(std::vector<csp::csp_variable> & variables, const std::vector<csp::csp_constraint>&constraints) const
{
    for (auto&i:variables)
        i.release_all();

    auto it_variable = variables.begin();
    std::vector<std::vector<size_t>> solutions;

    while (true)
    {
        for (const auto&variable:variables){
            if (!variable.is_valuated())
                break;
        }

        if (it_variable == variables.end())
            break;

        //si variable courante a domaine vide
        if (!it_variable->get_available_domain_size())
        {
            //si variable est la première on arrete BT
            if (it_variable == variables.begin())
            {
                break;
            }
            //sinon, on libère le domaine et on retourne à la variable précédente, puis on repart du début de la boucle
            it_variable->release_all();
            it_variable = std::prev(it_variable,1);
            it_variable->restrict_first();
            continue;
        }
        //on assigne une valeur à la variable
        it_variable->get_first_as_value();

        //on vérifie toutes les contraintes
        bool met_error = false;
        for (const auto &constraint : constraints)
        {
            if (constraint.associated_variable_are_valuated() && !constraint.run_constraint())
            {
                met_error = true;
                break;
            }
        }
        //si il y a eu une erreur, on exclue la valeur courante, et on repart du début de la boucle
        if (met_error)
        {
            it_variable->restrict_first();
            continue;
        }
        it_variable = std::next(it_variable,1);
        if (it_variable == variables.end()){
            record_solution(solutions, variables);
            it_variable = std::prev(it_variable,1);
            it_variable->restrict_first();
        }
    }

    return solutions;
}
