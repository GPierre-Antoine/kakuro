//
// Created by Pierre-Antoine on 20/05/2018.
//


#pragma once


#include "csp_variable.h"

bool operator==(const csp::csp_variable & v1, const csp::csp_variable& v2);
bool operator!=(const csp::csp_variable & v1, const csp::csp_variable& v2);
bool operator<(const csp::csp_variable & v1, const csp::csp_variable& v2);
