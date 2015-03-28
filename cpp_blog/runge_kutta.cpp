// So we should implement a simple runge-kutta class that takes in a pointer to a series of functions, with each function corresponding
// to a single differential equation that needs to be solved. The user can then input the tolerances and other options, then request to solve
// the given system. The system trajectory will be stored internally and can be queried over a discretization of points (most likely input as
// a vector). So we need a RK4 class.

class RK4_Equations;

// @class - RK4
// @info  - The purpose of this class is to take in a given set of equations (an Rk4_Equations class), and solve them using the RK4 method over
//          a user-specified discretization. The goal is to allow it to work with an arbitrary number of equations by letting the RK4_Equations 
//          class be derived from whenever a new set of equations that need to be solved comes up.
class RK4 {

private:

    int num_equations;

    double disc;

    double k1, k2, k3, k4;

    double t0, tf;

    RK4_Equations * function_handler;


public:

    RK4(uint num_equations, double disc, tf);
};


// @class - RK4_Equations
// @info  - This is to serve as the base class for this hierarchy. All of these classes are meant to be wrappers around sets of equations
//          that are passed into the RK4 class to be solved.
class RK4_Equations {

private:

public:

};