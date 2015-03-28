#ifndef DOUBLE_PEND_EQUATIONS_JHA
#define DOUBLE_PEND_EQUATIONS_JHA

#include "FunctionWrapperRK4"

// @class - DoublePendEquations
// @info  - This class is a child class of the FunctionWrapperRK4 base class, and is used to represent the differential-equations of motions
//          for a double-pendulum in a manner that allows them to be solved by our implementation of the Runge-Kutta-4 method (@file RK4.h). 
//          The RK4 method will simply query this object by calling the .getValues function which will return the values for the 4 first-order
//          differential equations at a given time and state value. For more info, see https://jhallard.com/double_pendulum_2.html
class DoublePendEquations : public FunctionWrapperRK4 {

private:
    // system constants (u-prefix is upper l-prefix is lower)
    double gravity, ulength, umass, llength, lmass;

public:

    // @func - Constructor
    // @args - #1 vector of values for the constants above
    DoublePendEquations(std::vector<double>);
    
    // @func - Constructor #2
    // @args - explicit values for constants above
    DoublePendEquations(double gravity, double ulength, double umass, double llength, double lmass);
    
    // @func - getValues
    // @args - #1 current time value to be used in the calculations, #2 vector of values for the 4 changing state variables (uangle,
    //         uangvel, langle, langvel)
    std::vector<t> getValues(double time, const std::vector<t> & state);


};

#endif