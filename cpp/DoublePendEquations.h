#ifndef DOUBLE_PEND_EQUATIONS_JHA
#define DOUBLE_PEND_EQUATIONS_JHA

#include "FunctionWrapperRK4.h"

#include <stdexcept>
// @class - DoublePendEquations
// @info  - This class is a child class of the FunctionWrapperRK4 base class, and is used to represent the differential-equations of motions
//          for a double-pendulum in a manner that allows them to be solved by our implementation of the Runge-Kutta-4 method (@file RK4.h). 
//          The RK4 method will simply query this object by calling the .getValues function which will return the values for the 4 first-order
//          differential equations at a given time and state value. For more info, see https://jhallard.com/double_pendulum_2.html
class DoublePendEquations : public FunctionWrapperRK4 {

private:
    // system constants (u-prefix is upper l-prefix is lower)
    double _gravity, _length1, _mass1, _length2, _mass2;

    // specific state values that are extracted from the given state vector
    double _theta1, _theta2, _omega1, _omega2;

    // @func - upperThetaPrime
    // @info - This is the differential equation for the upper theta variable : theta1' = omega1
    double upperThetaPrime(double time);

    // @func - upperThetaPrime
    // @info - This is the differential equation for the lower theta variable : theta2' = omega2
    double lowerThetaPrime(double time);

    // @func - upperThetaPrime
    // @info - This is the differential equation for the upper omega (angular velocity) variable : omega1' = 2sin(theta_1-theta_2)...
    double upperOmegaPrime(double time);

    // @func - upperThetaPrime
    // @info - This is the differential equation for the upper omega (angular velocity) variable : omega2' = L1cos(theta_1-theta_2)...
    double lowerOmegaPrime(double time);

public:

    // @func - Constructor
    // @args - #1 vector of values for the constants above
    DoublePendEquations(std::vector<double>);
    
    // @func - Constructor #2
    // @args - explicit values for constants above
    DoublePendEquations(double gravity, double length1, double mass1, double length2, double mass2);
    
    // @func - getValues
    // @args - #1 current time value to be used in the calculations, #2 vector of values for the 4 changing state variables (uangle,
    //         uangvel, langle, langvel)
    // #info - This function is simply going to call the 4 private utility functions to get the values, it exists to fufill the interface defined
    //         by the base class in the hierarchy.
    virtual void getValues(double, const std::vector<double> &, std::vector<double> *);

};

#endif