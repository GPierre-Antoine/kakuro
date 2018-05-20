//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "algorithm_forward_checking.h"

std::vector<std::vector<size_t>> csp::algorithm_forward_checking::run(std::vector<csp::csp_variable> &variables,
                                                                      const std::vector<std::unique_ptr<csp::csp_constraint>> &constraints) const
{
    for (auto &i:variables)
    {
        i.release_all();
    }

    auto history = std::vector<record>();
    history.reserve(1000);

    auto it_variable = variables.begin();
    std::vector<std::vector<size_t>> solutions;

    while (true)
    {
        if (it_variable == variables.end())
        {
            break;
        }

        //si variable courante a domaine vide
        if (!it_variable->get_available_domain_size())
        {
            //si variable est la première on arrete BT
            if (it_variable == variables.begin())
            {
                break;
            }
            //sinon, on libère le domaine et on retourne à la variable précédente, puis on repart du début de la boucle
            release_automatic_assignations(it_variable, history);
            it_variable = std::prev(it_variable, 1);
            it_variable->restrict_first();
            continue;
        }
        //on assigne une valeur à la variable
        restrict(*it_variable, history, record_type::manual);

        //on vérifie toutes les contraintes
        bool met_error = false;
        for (const auto &constraint : constraints)
        {
            if (constraint->associated_variable_are_valuated() && !constraint->run_constraint())
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
        it_variable = std::next(it_variable, 1);
        if (it_variable == variables.end())
        {
            record_solution(solutions, variables);
            it_variable = std::prev(it_variable, 1);
            it_variable->restrict_first();
        }
    }

    return solutions;
}

void csp::algorithm_forward_checking::restrict(csp::csp_variable &variable,
                                               std::vector<csp::record> &history,
                                               record_type type) const
{
    variable.restrict_first();
    history.push_back(record(type, variable));
}
void csp::algorithm_forward_checking::release_automatic_assignations(typename std::vector<csp::csp_variable>::iterator &it_variable,
                                                                     std::vector<csp::record> &vector) const
{
    while (!vector.back().is_manual())
    {
        vector.pop_back();
    }
    while (!vector.back().compare_record(*it_variable))
    {
        std::advance(it_variable, -1);
    }
}

