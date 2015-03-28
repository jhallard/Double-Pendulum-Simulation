// So we should implement a simple runge-kutta class that takes in a pointer to a series of functions, with each function corresponding
// to a single differential equation that needs to be solved. The user can then input the tolerances and other options, then request to solve
// the given system. The system trajectory will be stored internally and can be queried over a discretization of points (most likely input as
// a vector). So we need a RK4 class.

class RK4 {

private:

    int num_equations;

    double disc;

    double k1, k2, k3, k4;

    double t0, tf;


public:

    RK4(uint num_equations, double disc, tf);
}