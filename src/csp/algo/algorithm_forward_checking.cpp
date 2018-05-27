//
// Created by pierreantoine on 24/05/18.
//

#include "algorithm_forward_checking.h"
#include "../../ostream.h"
#include "../history.h"

#define lf std::string(__FILE__) + ":" + std::to_string(__LINE__) + " # "

//void assert_variables_in_range_noempty(const_iter_v begin, const_iter_v end)
//{
//    for (; begin != end; std::advance(begin, 1))
//    {
//        if ((*begin)->has_empty_domain())
//        {
//            std::stringstream os;
//            os << std::setfill('0') << lf << "variable " << edit(**begin) << " has empty domain";
//            throw std::runtime_error(os.str());
//        }
//    }
//}

//void assert_variables_in_range_assignated(const_iter_v begin, const_iter_v end)
//{
//    for (; begin != end; std::advance(begin, 1))
//    {
//        if (!(*begin)->is_valuated())
//        {
//            throw std::runtime_error(edit(**begin) + " isn't valuated");
//        }
//    }
//}

/**
 *
 * @param var
 * @param history
 * @param timestamp
 * @param type
 */
void restrict_automatic(csp_variable_ptr &var, csp_constraint_ptr c, csp::history &history, std::size_t count)
{
    history.track(c, std::move(csp::record(record_type::automatic, var, var->get_id(), count)));
}

bool apply_constraint(const csp_constraint_ptr &constraint, csp::history &history)
{
    if (!constraint->has_only_one_variable_unvaluated_left())
    {
        return true;
    }
    auto variable = constraint->get_last_unvaluated_variable();
    auto domain_size_before_constraint = variable->get_available_size();
    constraint->run_fc();
    auto domain_size_after_constraint = variable->get_available_size();
    std::size_t stack = domain_size_before_constraint - domain_size_after_constraint;
    restrict_automatic(variable, constraint, history, stack);
    return domain_size_after_constraint != 0;
}

void restrict_manual(csp_variable_ptr &f, csp::history &history, std::size_t timestamp)
{
    f->restrict_first();
    history.track(nullptr, std::move(csp::record(record_type::manual, f, timestamp, 1)));
}

inline bool range_has_value(std::vector<std::size_t>::const_iterator begin,
                            std::vector<std::size_t>::const_iterator end,
                            std::size_t value)
{
    return std::find(begin, end, value) != end;
}

void rollback_unfixed_variables(const std::vector<std::size_t> &delete_values, csp::history &history)
{
    while (!history.empty()
        && range_has_value(delete_values.begin(), delete_values.end(), history.get_variable()->get_id()))
    {
        history.pop();
    }
}

bool resolve_error_unfixed(const variable_vector &variables,
                           variable_vector::iterator &it_variable,
                           csp::history &history)
{
    auto begin = variables.begin();
    auto end = variables.end();
    std::vector<std::size_t> unfixed;
    unfixed.reserve(static_cast<std::size_t>(std::distance(begin, end)));
    for (auto it = std::next(it_variable); it != end; std::advance(it, 1))
    {
        unfixed.emplace_back((*it)->get_id());
    }
    for (;;)
    {
        rollback_unfixed_variables(unfixed, history);
        restrict_manual(*it_variable, history, (*it_variable)->get_id());
        if (!(*it_variable)->has_empty_domain())
        {
            //            assert_variables_in_range_noempty(begin, end);
            return true;
        }
        if (it_variable == begin)
        {
            return false;
        }
        unfixed.emplace_back((*it_variable)->get_id());
        std::advance(it_variable, -1);
    }
}

bool resolve_error_with_constraint(variable_vector &variables,
                                   variable_vector::iterator &it_variable,
                                   csp::history &history)
{
    auto begin = variables.begin();
    auto end = variables.end();
    //    std::cout << "\n" << lf << edit_fn(begin, end, edit_domain) << "\n";
    std::vector<std::size_t> ids;
    ids.reserve(variables.size());
    ids.resize(static_cast<std::size_t>(std::distance(it_variable, end)));
    std::transform(it_variable, end, ids.begin(), [](const csp_variable_ptr &var)
    {
        return var->get_id();
    });

    for (;; std::advance(it_variable, -1))
    {
        while (history
            && ((history.has_constraint() && history.get_constraint()->has_a_empty_variable())
                || (!history.has_constraint()
                    && range_has_value(ids.begin(), ids.end(), history.get_variable()->get_id()))))
        {
            history.pop();
        }

        restrict_manual(*it_variable, history, (*it_variable)->get_id());
        if (!(*it_variable)->has_empty_domain())
        {
            break;
        }
        if (it_variable == begin)
        {
            return false;
        }
        ids.push_back((*it_variable)->get_id());
    }
    //    std::cout << lf << edit_fn(begin, end, edit_domain) << "\n";
    return true;
}

csp::algorithm_forward_checking::algorithm_forward_checking(bool find_all_results) : algorithm(std::string(
    "Forward Checking"), find_all_results)
{

}

csp::solution csp::algorithm_forward_checking::run(variable_vector &variables, constraint_vector &constraints,
                                                   heuristic heuristic) const
{
    std::vector<std::vector<size_t>> solutions;
    csp::history history{};
    auto it_variable = variables.begin();

    csp::solution tracker = solution(variables.size(), *this, heuristic);

    tracker.start_chrono();
    while (true)
    {
        tracker.inc_node_count();
        //state is clear at the begining

        //check error
        bool met_error = false;

        if (it_variable == variables.end())
        {
            //found solution
            tracker.add_record(variables);

            if (stop_at_first_result)
            {
                break;
            }
            //it variable now re-points toward a csp::csp_variable
            it_variable = std::prev(it_variable);
            met_error = true;
            //treat current affectation as error, it will be rolled-back the same
        }
        else
        {
            //sort with heuristic
            auto it = find_lower_value_variable(it_variable, variables.end(), heuristic);
            if (it_variable != it)
            {
                std::iter_swap(it_variable, it);
            }

            //assign new value
            (*it_variable)->assign_first_element_as_value();

            //reverbate changes
            for (const auto &constraint:constraints)
            {
                tracker.inc_constraint_count();
                if (!apply_constraint(constraint, history))
                {
                    met_error = true;
                    break;
                }
            }
        }

        //clear error and return to start
        if (met_error)
        {
            if (!resolve_error_unfixed(variables, it_variable, history))
            {
                //if could not resolve error, exit
                // <=> backtracked until first variable has empty domain
                break;
            }
            continue;
        }

        //now clear from error, go to next variable
        it_variable = std::next(it_variable);
    }
    tracker.stop_chrono();
    return std::move(tracker);
}

