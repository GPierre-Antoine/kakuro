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
void restrict_automatic(csp_variable_ptr &f, std::vector<csp::record> &history, std::size_t timestamp)
{
    history.emplace_back(csp::record(record_type::automatic, f, timestamp));
}

void restrict_manual(csp_variable_ptr &f, std::vector<csp::record> &history, std::size_t timestamp)
{
    f->restrict_first();
    history.emplace_back(csp::record(record_type::manual, f, timestamp));
}

/**
 * rollback state until f's last manual change (excluded)
 * @param f
 * @param history
 */
void rollback(csp_variable_ptr &f, std::vector<csp::record> &history)
{
    while (!history.empty() && (!history.back().is_same_variable(*f) && history.back().timestamp == f->get_id()))
    {
        history.pop_back();
    }
}

void release_auto(std::vector<csp::record> &history)
{
    while (!history.empty() && !history.back().is_manual())
    {
        history.pop_back();
    }
}

csp::algo_fc_2::algo_fc_2(bool stop_at_first_result) : algorithm(std::string("FC2"), stop_at_first_result)
{

}

std::vector<std::vector<size_t>> csp::algo_fc_2::run(variable_vector &variables,
                                                     const constraint_vector &constraints,
                                                     heuristic heuristic) const
{
    std::vector<std::vector<size_t>> solutions;
    std::vector<csp::record> history;
    history.reserve(1000);
    auto it_variable = variables.begin();

    auto counter = 0ul;

    while (true)
    {
        //state is clear at the begining

        //make a timestamp
        std::size_t change_index;


        if (it_variable == variables.end())
        {
            //found solution
            record_solution(solutions, variables);

            constexpr const std::size_t explore = 10;

            if (stop_at_first_result)
            {
                break;
            }
            //it variable now re-points toward a csp::csp_variable
            it_variable = std::prev(it_variable);

            change_index = (*it_variable)->get_id();
            release_auto(history);

            while (!history.empty() && !history.back().is_same_variable(**it_variable))
            {
                //rollback to previous
                (*it_variable)->unvaluate();
                it_variable = std::prev(it_variable);
            }
            change_index = (*it_variable)->get_id();
            restrict_manual(*it_variable, history, change_index);

            if (!(*it_variable)->has_empty_domain())
            {
                (*it_variable)->assign_first_element_as_value();
            }
            break;
        }
        else
        {
            //sort with heuristic
            std::sort(it_variable, variables.end(), heuristic);

            //assign new value
            (*it_variable)->assign_first_element_as_value();

            //timestamp = current variable id
            change_index = (*it_variable)->get_id();

            //reverbate changes
            for (const auto &i:constraints)
            {
                if (i->has_only_one_variable_unvaluated_left())
                {
                    auto variable = i->get_last_unvaluated_variable();
                    auto domain_size_before_constraint = variable->get_available_size();
                    i->run_fc();
                    auto domain_size_after_constraint = variable->get_available_size();
                    auto stack = domain_size_before_constraint - domain_size_after_constraint;
                    while (stack > 0)
                    {
                        stack -= 1;
                        //record all new mecanisme under current variable id
                        restrict_automatic(variable, history, change_index);
                    }
                }
            }
        }

        //check error
        bool met_error = false;
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
            while (!history.empty() && history.back().timestamp == change_index)
            {
                history.pop_back();
            }
            restrict_manual(*it_variable, history, change_index);

            while ((*it_variable)->has_empty_domain() && it_variable != variables.begin())
            {
                it_variable = std::prev(it_variable);
                rollback(*it_variable, history);
                change_index = (*it_variable)->get_id();
                restrict_manual(*it_variable, history, change_index);
            }

            //if first variable is empty, then exit
            // - variables are sorted only when free
            // - and break if first is sorted
            // therefore variable.begin has empty domain means itvariable=begin

            if ((**variables.begin()).has_empty_domain())
            {
                break;
            }

            continue;
        }
        //now clear from error, go to next variable
        it_variable = std::next(it_variable);

    }

    return solutions;
}

#undef PR