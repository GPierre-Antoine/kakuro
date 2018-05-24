//
// Created by pierreantoine on 24/05/18.
//

#include "algo_fc_2.h"
#include "../../ostream.h"

/**
 *
 * @param f
 * @param history
 * @param timestamp
 * @param type
 */
void restrict(csp_variable_ptr &f, std::vector<csp::record> &history, std::size_t timestamp, record_type type)
{
    history.emplace_back(csp::record(type, f, timestamp));
}

/**
 * rollback state until f's last manual change (excluded)
 * @param f
 * @param history
 */
void rollback(csp_variable_ptr &f, std::vector<csp::record> &history)
{
    while (!history.empty() && (!history.back().is_same_variable(*f) || !history.back().is_manual()))
    {
        history.pop_back();
    }
}

csp::algo_fc_2::algo_fc_2(bool stop_at_first_result) : algorithm(std::string("FC2"), stop_at_first_result)
{

}

std::vector<std::vector<size_t>>
csp::algo_fc_2::run(variable_vector &variables, const constraint_vector &constraints, heuristic heuristic) const
{
    std::vector<std::vector<size_t>> solutions;
    std::vector<csp::record>         history;
    history.reserve(1000);
    auto it_variable = variables.begin();

    std::cout << edit(variables) << std::endl;

    while (true)
    {
        //state is clear at the begining

        //sort with heuristic
        std::sort(variables.begin(), variables.end(), heuristic);

        //assign new value
        (*it_variable)->assign_first_element_as_value();

        std::size_t change_index = history.size();

        //reverbate changes
        for (const auto &i:constraints)
        {
            if (i->has_only_one_variable_unvaluated_left())
            {
                auto variable                      = i->get_last_unvaluated_variable();
                auto domain_size_before_constraint = variable->get_available_size();
                i->run_fc();
                auto domain_size_after_constraint = variable->get_available_size();
                auto stack                        = domain_size_before_constraint - domain_size_after_constraint;
                while (stack > 0)
                {
                    stack -= 1;
                    restrict(variable, history, change_index, record_type::automatic);
                }
            }
        }

        //todo prove valid to place it here
        if (it_variable == variables.end())
        {
            //found solution
            record_solution(solutions, variables);

            if (stop_at_first_result)
            {
                break;
            }

            //rollback to previous
            std::advance(it_variable, -1);
            auto compute_size = history.empty() ? 0 : history.back().timestamp;
            restrict(*it_variable, history, compute_size, record_type::manual);
        }

        //check error
        bool            met_error = false;
        for (const auto &i:variables)
        {
            if (i->has_empty_domain())
            {
                met_error = true;
                break;
            }
        }
        //clear error and return to start
        if (met_error)
        {
            while (!history.empty() && history.back().timestamp == change_index && !history.back().is_manual())
            {
                history.pop_back();
            }
            restrict(*it_variable, history, change_index, record_type::manual);

            while ((*it_variable)->has_empty_domain() && it_variable != variables.begin())
            {
                std::advance(it_variable, -1);
                rollback(*it_variable, history);
                restrict(*it_variable, history, change_index, record_type::manual);
            }

            //if first variable is empty, then exit
            // - variables are sorted only when free
            // - and break if first is sorted
            // therefore variable.begin has empty domain means itvariable=begin
            if ((**variables.begin()).has_empty_domain())
            {
                break;
            }

            //now clear from error, go to next variable
            std::advance(it_variable, 1);

        }

    }

    return solutions;
}