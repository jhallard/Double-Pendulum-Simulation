#ifndef RK4_JHALLARD
#define RK4_JHALLARD

#include "FunctionWrapperRK4.h"

// @class - RK4
// @info  - The purpose of this class is to take in a given set of equations (an Rk4_Equations class), and solve them using the RK4 method over
//          a user-specified discretization. The goal is to allow it to work with an arbitrary number of equations by letting the RK4_Equations 
//          class be derived from whenever a new set of equations that need to be solved comes up.
class RK4 {

private:

    int num_equations;     // number of equations to be solved simultaneously
    double disc;           // discretization step
    double k1, k2, k3, k4; // 4 K values (should be vectors probably)
    double t0, tf;

    // pointer to base object that serves as our interface to the diff. equations defined by the user
    FunctionWrapperRK4 * function_handler;


public:

    RK4(uint num_equations, double disc, tf);
};


#endif