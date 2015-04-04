#ifndef FUNC_WRAP_RK4
#define FUNC_WRAP_RK4

#include <vector>
#include <cmath>

// @class - FunctionWrapperRK4
// @info  - This is to serve as the base class for this hierarchy. All of these classes are meant to be wrappers around sets of equations
//          that are passed into the RK4 class to be solved.
class FunctionWrapperRK4 {
private:
    // number of equations to wrap with this object
    int _num_equations;

public:
    // @func - Constructor
    // @args - #1 number of equations to be wrapped
    FunctionWrapperRK4(int);

    // @func - getValues
    // @args - #1 current time value to be used #2 current state values to be used, #3 vector to return values in
    // @info - Overwritte this with child classes to return the true function values.
    virtual void getValues(double, const std::vector<double> &, std::vector<double> *) = 0;

    // @self-documenting
    int getNumEquations() const; 
};

#endif