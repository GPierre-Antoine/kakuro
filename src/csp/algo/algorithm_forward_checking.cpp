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
        //si pile de variables est vide on sort
        if (it_variable == variables.end())
        {
            break;
        }

        if (it_variable->get_available_domain_size())
        {
            //si domaine non vide, on assigne la variable.
            heuristic(*it_variable);
        }
        else
        {
            //si domaine de variable est vide
            //si c'est la première variable on sort
            if (it_variable == variables.begin())
            {
                break;
            }
            //on defait toutes les valuations de cette variable
            rollback_assignations(*it_variable, history);
            release_automatic_assignations(history);
            //on retourne à la dernière variable assignée manuellement
            while (!history.back().is_same_variable(*it_variable))
            {
                it_variable = std::prev(it_variable, 1);
            }
            //on exclue sa première valeur et on retourne au début
            restrict(*it_variable, history);
            continue;
        }

        //on vérifie toutes les contraintes
        //on exclue les valeurs incompatibles
        //si on a fait une exclusion on recommence
        bool redo;
        do
        {
            redo = false;
            for (const auto &constraint : constraints)
            {
                if (constraint->one_variable_left_unvaluated())
                {
                    constraint->run_fc(history);
                    if (!redo && constraint->one_variable_left_unvaluated())
                    {
                        redo = true;
                    }
                }
            }
        }
        while (redo);

        for (auto &variable:variables)
        {
            if (!variable.get_available_domain_size())
            {
                release_automatic_assignations(history);
                restrict(variable, history);
                break;
            }
        }
    }

    return solutions;
}

void csp::algorithm_forward_checking::restrict(csp::csp_variable &variable, std::vector<csp::record> &history) const
{
    if (!variable.get_available_domain_size())
    {
        return;
    }
    variable.restrict_first();
    history.push_back(record(record_type::manual, variable));
}
void csp::algorithm_forward_checking::release_automatic_assignations(std::vector<csp::record> &vector) const
{
    while (!vector.back().is_manual())
    {
        vector.pop_back();
    }
}

void csp::algorithm_forward_checking::rollback_assignations(const csp::csp_variable &variable,
                                                            std::vector<csp::record> &vector) const
{
    while (vector.back().is_manual() && vector.back().is_same_variable(variable))
    {
        vector.pop_back();
    }
}
void csp::algorithm_forward_checking::heuristic(csp::csp_variable &variable) const
{
    variable.get_first_as_value();
}
csp::algorithm_forward_checking::algorithm_forward_checking() : algorithm(std::string("Forward Checking"))
{

}
