//
// Created by Pierre-Antoine on 21/05/2018.
//

#ifndef KAKURO_FORWARD_H
#define KAKURO_FORWARD_H

#include <memory>
#include <vector>
#include <stack>
#include <functional>

namespace csp
{
    class csp_variable;
    class csp_constraint;
    class csp_constraint_solution;
    class record;
}

typedef std::shared_ptr<csp::csp_variable> csp_variable_ptr;
csp_variable_ptr make_yield_variable(std::size_t);

typedef std::vector<csp_variable_ptr> variable_vector;

typedef std::shared_ptr<csp::csp_constraint> csp_constraint_ptr;
csp_constraint_ptr make_yield_c_sum(std::size_t);
csp_constraint_ptr make_yield_c_diff();
std::shared_ptr<csp::csp_constraint_solution> make_yield_c_solution();

typedef std::stack<std::pair<csp_constraint_ptr, csp::record>> record_vector;

template<typename iter_t, class T, class type>
T reduce(iter_t begin, iter_t end, T init, std::function<T (T,type)> f)
{
    for (; begin != end; std::advance(begin, 1))
    {
        init = f(init, *begin);
    }
    return init;
}

typedef std::vector<csp_constraint_ptr> constraint_vector;
typedef variable_vector::iterator iter_v;
typedef variable_vector::const_iterator const_iter_v;

#endif //KAKURO_FORWARD_H
