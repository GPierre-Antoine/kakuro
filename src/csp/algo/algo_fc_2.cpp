//
// Created by pierreantoine on 24/05/18.
//

#include "algo_fc_2.h"
#include "../../ostream.h"


#define lf __FILE__ << ":" << std::setw(3) << __LINE__ << " # "

/**
 *
 * @param f
 * @param history
 * @param timestamp
 * @param type
 */
void restrict_automatic(csp_variable_ptr &f, record_vector &history, std::size_t timestamp)
{
    history.emplace_back(csp::record(record_type::automatic, f, timestamp));
}

void restrict_manual(csp_variable_ptr &f, record_vector &history, std::size_t timestamp)
{
    f->restrict_first();
    history.emplace_back(csp::record(record_type::manual, f, timestamp));
}

/**
 * rollback state until f's last manual change (excluded)
 * @param f
 * @param history
 */
void rollback_different(csp_variable_ptr &f, record_vector &history)
{
    if (!history.empty())
        cout << lf << "next timestamp : " << history.back().timestamp << endl;

    while (!history.empty() && history.back().timestamp != f->get_id())
    {
        cout << lf << "timestamp de reference : " << f->get_id() << " timestamp a enlever : " << history.back().timestamp << endl;
        history.pop_back();
    }
}

void rollback_different_variable(csp_variable_ptr &f, record_vector &history)
{

    while (!history.empty() && !history.back().is_same_variable(*f))
    {
        cout << lf
             << "id comparée: " << history.back().get_variable()->get_id() << endl
             << lf
             << "timestamp (non-comparé ): " << history.back().timestamp << endl
                ;
        history.pop_back();
    }
}


void release_auto(record_vector &history)
{
    while (!history.empty() && !history.back().is_manual())
    {
        history.pop_back();
    }
}


bool resolve_error(const variable_vector &variables, variable_vector::iterator &it_variable, record_vector &history)
{
    //there is an error
    //it_variable has just been valuated
    //history -> timestamp maps to the IDs of the assignated variables
    //it_variable belongs to variables
    //it_variable is not in error state
    //error is after it_variable
    //but error is caused by it_variable assignation.

    while (true)
    {
        cout << lf << "error treatment rolling back all that is not : " << **it_variable << endl;

        rollback_different_variable(*it_variable, history);

        restrict_manual(*it_variable, history, (*it_variable)->get_id());
        cout << lf << "error treatment after restriction :  " << edit_domain(**it_variable) << endl;
        if (!(*it_variable)->has_empty_domain())
        {
            cout <<endl<< lf << "domains after treatment" << edit_fn(it_variable, variables.end(), edit_domain) << endl;
            return true;
        }
        if (it_variable == variables.begin())
        {
            return false;
        }
        std::advance(it_variable, -1);
    }
    //outputs :
    //either error resolved -> true
    //or
    //variables.begin() is empty -> false

}

csp::algo_fc_2::algo_fc_2(bool stop_at_first_result) : algorithm(std::string("FC2"), stop_at_first_result)
{

}

std::vector<std::vector<size_t>> csp::algo_fc_2::run(variable_vector &variables,
                                                     const constraint_vector &constraints,
                                                     heuristic heuristic) const
{
    std::vector<std::vector<size_t>> solutions;
    record_vector                    history;
    history.reserve(1000);

    auto it_variable = variables.begin();

    while (true)
    {
        //state is clear at the begining

        for (auto i = variables.begin(); i!=it_variable;std::advance(i,1)){
            if (!(*i)->is_valuated())
            {
                cout << lf << edit_fn(variables.begin(),it_variable,edit_value_v) << endl;
                throw std::runtime_error("Error in previous data");
            }
        }


        //check error
        bool met_error = false;


        cout << endl << lf << edit_fn(variables.begin(), it_variable, edit_value_v) << endl;

        if (it_variable == variables.end())
        {

            cout << lf << "found solution" << endl;
            //found solution
            record_solution(solutions, variables);


            if (stop_at_first_result)
            {
                break;
            }
            //it variable now re-points toward a csp::csp_variable
            it_variable = std::prev(it_variable);
            met_error   = true;
            //treat current affectation as error, it will be rolled-back the same

        }
        else
        {
            cout << lf << "edit domain pre-sort" << edit_fn(it_variable, variables.end(), edit_domain) << endl;
            //sort with heuristic
            std::sort(it_variable, variables.end(), heuristic);
            cout << lf << "edit domain post-sort" << edit_fn(it_variable, variables.end(), edit_domain) << endl;

            //assign new value
            (*it_variable)->assign_first_element_as_value();

            cout << lf << edit_value_v(**it_variable) << endl;

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
                        //record all new mecanisme under current variable id
                        restrict_automatic(variable, history, (*it_variable)->get_id());
                    }
                }
            }
        }

        for (const auto &i:variables)
        {
            if (i->has_empty_domain())
            {
                cout << lf << "met error : " << *i << endl;
                met_error = true;
            }
        }

        //clear error and return to start
        if (met_error)
        {
            if (!resolve_error(variables, it_variable, history))
            {
                //if could not resolve error, exit
                // <=> backtracked until first variable has empty domain
                break;
            }
            cout << lf << "edit domain post-error" << edit_fn(it_variable, variables.end(), edit_domain) << endl;
            continue;
        }


        //now clear from error, go to next variable
        it_variable = std::next(it_variable);
    }
    return solutions;
}

#undef PR