#ifndef RK4_JHALLARD
#define RK4_JHALLARD

#include "FunctionWrapperRK4.h"
#include <stdexcept>
#include <iostream>
#include <chrono>

// @class - RK4
// @info  - The purpose of this class is to take in a given set of equations (an Rk4_Equations class), and solve them using the RK4 method over
//          a user-specified discretization. The goal is to allow it to work with an arbitrary number of equations by letting the RK4_Equations 
//          class be derived from whenever a new set of equations that need to be solved comes up.
class RK4 {

private:

    int _num_equations;                  // number of equations to be solved simultaneously
    long double _disc;                        // discretization step
    std::vector<double> _k1, _k2, _k3, _k4; // 4 K vectors
    double _tf;

    // pointer to base object that serves as our interface to the diff. equations defined by the user
    FunctionWrapperRK4 * _equations;

    // vector of vectors, this holds an array of state-values for each of the variables that need to be solved.
    std::vector<std::vector<double> > _solutions;

    // @func - stateAdjust
    // @args - #1 vector to be adjusted, #2 vector to add to the first, #3 constant factor to adjust 2nd vector by
    std::vector<double> stateAdjust(const std::vector<double> &, const std::vector<double> &, double);

    // @func - vectorAdd
    // @info - takes a vector of vectors of the same length and adds all the components together
    std::vector<double> vectorAdd(const std::vector<std::vector<double> *> & vecs);


public:

    // @func - Constructor
    // @args - #1 ptr to base class, should hold your derived class that contains the
    //         equations of motion to be solved.
    RK4(FunctionWrapperRK4 * fn);

    // @func - solve
    // @args - #1 discretization, #2 final time for simulation (from 0s), #3 vector of initial condition values
    bool solve(long double disc, double tf, std::vector<double> ic);

    // @func - query
    // @args - #1 the starting time for the query, #2 the end time for the query, #3 the time step you wish to jump between those points
    std::vector<std::vector<double> > query(double t0, double tf, double step);

    // @func - setEquations
    // @info - enter a new set of equations to be solved
    bool setEquations(FunctionWrapperRK4 * fn);

    // @func - getEquations
    // @info - get the equations object being used currently.
    FunctionWrapperRK4 * getEquations();
};


#endif