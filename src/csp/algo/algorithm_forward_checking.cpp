//
// Created by Pierre-Antoine on 20/05/2018.
//


#include <algorithm>
#include <cstddef>

#include "../../ostream.h"
#include "algorithm_forward_checking.h"

std::vector<std::vector<std::size_t>> csp::algorithm_forward_checking::run(std::vector<std::shared_ptr<csp::csp_variable>> &variables,
                                                                           const std::vector<std::unique_ptr<csp::csp_constraint>> &constraints,
                                                                           const std::function<bool(const csp_variable_ptr&,const csp_variable_ptr&)> & heuristic) const
{
    for (auto &i:variables)
    {
        i->release_all();
    }

    auto history = std::vector<record>();
    history.reserve(1000);

    std::size_t index = 0;
    std::vector<std::vector<size_t>> solutions;


    while (true)
    {
        cout << __LINE__ << endl;
        //on met la variable la plus interessante devant
        std::sort(std::next(variables.begin(), index), variables.end(), heuristic);

        //si la variable courante à un domaine vide
        //on rollback les assignations et on revient à la précédente
        //et on verrouille le resultat courant
        //on recommence
        cout << variables << endl;
        if (variables[index]->has_empty_domain())
        {
            if (index == 0)
            {
                break;
            }
            rollback_assignations(*variables[index], history);
            restrict(variables[--index], history);
            continue;
        }

        //la variable considérée prend pour valeur la première valeur possible
        variables[index]->assign_first_element_as_value();

        cout << variables << endl;

        //on verifie toutes les constantes
        for (const auto &constraint:constraints)
        {
            if (constraint->has_only_one_variable_unvaluated_left())
            {
                //si une
                auto var = constraint->get_last_unvaluated_variable();
                if (var->get_available_size() > 1)
                {
                    constraint->run_fc(history);
                    if (var->has_empty_domain())
                    {
                        break;
                    }
                }
            }
        }

        bool met_error = false;
        for (auto left_variables = index; left_variables < variables.size(); left_variables += 1)
        {
            if (variables[left_variables]->has_empty_domain())
            {
                met_error = true;
                break;
            }
        }
        if (met_error)
        {
            release_automatic_assignations(history);
            rollback_assignations(*variables[index], history);
            if (!variables[index]->has_empty_domain())
            {
                restrict(variables[index], history);
            }
            continue;
        }


        if (++index == variables.size())
        {
            record_solution(solutions, variables);
            if (stop_at_first_result)
            {
                break;
            }
            restrict(variables[--index], history);
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
    history.emplace_back(record(record_type::manual, *variable));
}
void csp::algorithm_forward_checking::release_automatic_assignations(std::vector<csp::record> &vector) const
{
    cout << vector.size();
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
csp::algorithm_forward_checking::algorithm_forward_checking(bool stop_at_first_result) : algorithm(std::string(
    "Forward Checking"), stop_at_first_result)
{

}

