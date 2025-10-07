/****************************
 *  Author : Sinan Demir
 *  Date   : 09/23/2025
 *  File   : main.h
 *  Purpose: Main header file for the project
 ***************************/


#ifndef MAIN_H
#define MAIN_H 


#include "integrators.h"
#include "differentiators.h"
#include "errors.h"
#include "star_physics.h"
#include "finance.h"
#include "util.h"


#include <fstream>
#include <string>
#include <sstream>

double simpson_result = 0.0;
double trapezoid_result = 0.0;
double exact;

#endif // MAIN_H