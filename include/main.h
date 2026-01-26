/****************************
 *  Author : Sinan Demir
 *  Date   : 09/23/2025
 *  File   : main.h
 *  Purpose: Main header file for the project
 ***************************/

#ifndef MAIN_H
#define MAIN_H

#include "num_analysis/differentiation.h"
#include "num_analysis/errors.h"
#include "num_analysis/integration.h"
#include "physics/constants.h"
#include "physics/star_physics.h"
#include "util.h"
#include <fstream>
#include <sstream>
#include <string>

double simpson_result = 0.0;
double trapezoid_result = 0.0;
double exact;

#endif // MAIN_H