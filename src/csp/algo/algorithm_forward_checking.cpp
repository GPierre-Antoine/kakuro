//
// Created by pierreantoine on 22/05/18.
//

#include "algorithm_forward_checking.h"
#include "../../ostream.h"

std::vector<std::vector<std::size_t>> csp::algorithm_forward_checking::run(variable_vector &variables,
                                                                           const constraint_vector &constraints,
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

    bool met_error = false;

    while (true)
    {
        counter+=1;

        met_error = met_error || (*iterator)->has_empty_domain();

        if (met_error)
        {
            //resolve error


            if ((*iterator)->has_empty_domain())
            {
                if (iterator == variables.begin())
                {
                    break;
                }
                std::advance(iterator, -1);
            }
            rollback_assignations(*iterator, history);
            restrict(*iterator, history, (*iterator)->get_value(), counter);
            if (!(*iterator)->has_empty_domain())
            {
                met_error = false;
            }
        }
        if (met_error)
        {
            continue;
        }

        //on met la variable la plus interessante devant
        cout << variables << endl;
        std::sort(iterator, variables.end(), heuristic);
        cout << variables << endl;


        //la variable considérée prend pour valeur la première valeur possible
        (*iterator)->assign_first_element_as_value();
        cout << *iterator << endl << endl;
        //on verifie toutes les constantes

        for (const auto &constraint:constraints)
        {
            if (constraint->has_only_one_variable_unvaluated_left())
            {
                auto var = record_auto(*constraint, history, counter);
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
            restrict(*iterator, history, (*iterator)->get_value(), counter);
        }
    }

    return solutions;
}

csp::algorithm_forward_checking::algorithm_forward_checking(bool continue_after_first)
    : algorithm(std::string("FC"),continue_after_first)
{

}
void csp::algorithm_forward_checking::restrict(csp_variable_ptr variable,
                                               std::vector<csp::record> &history,
                                               std::size_t value,
                                               std::size_t counter) const
{
    if (!variable->get_available_size())
    {
        return;
    }
    variable->restrict(value);
    history.emplace_back(record(record_type::manual, variable, counter));
}

csp_variable_ptr csp::algorithm_forward_checking::record_auto(const csp_constraint &constraint,
                                                              std::vector<csp::record> &history,
                                                              std::size_t counter) const
{
    auto var = constraint.get_last_unvaluated_variable();
    auto size_before_constraint = var->get_available_size();
    constraint.run_fc();
    long difference = size_before_constraint - var->get_available_size();
    while (difference > 0)
    {
        history.emplace_back(record(record_type::automatic, var, counter));
        difference -= 1;
    }
    return var;
}
void csp::algorithm_forward_checking::release_automatic_assignations(std::vector<csp::record> &vector) const
{
    if (vector.empty())
    {
        return;
    }
    auto id = vector.back().timestamp;
    while (!vector.empty() && vector.back().timestamp == id && !vector.back().is_manual())
    {
        vector.pop_back();
    }
}
void csp::algorithm_forward_checking::rollback_assignations(const csp_variable_ptr &variable,
                                                            std::vector<csp::record> &history) const
{

    release_automatic_assignations(history);
    rollback_assignations((*variable), history);
}

void csp::algorithm_forward_checking::rollback_assignations(const csp::csp_variable &variable,
                                                            std::vector<csp::record> &history) const
{
    while (!history.empty() && history.back().is_manual() && !history.back().is_same_variable(variable))
    {
        history.pop_back();
    }
}
