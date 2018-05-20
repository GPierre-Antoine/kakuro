//
// Created by Pierre-Antoine on 20/05/2018.
//


#include "compare_variables.h"

bool operator==(const csp::csp_variable &v1, const csp::csp_variable &v2)
{
    return v1.get_id() == v2.get_id();
}

bool operator!=(const csp::csp_variable &v1, const csp::csp_variable &v2)
{
    return (!(v1 == v2));
}

bool operator<(const csp::csp_variable &v1, const csp::csp_variable &v2)
{
    return v1.get_id() < v2.get_id();
}