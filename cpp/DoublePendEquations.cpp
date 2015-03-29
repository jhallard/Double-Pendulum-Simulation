#include "DoublePendEquations.h"


// @func - upperThetaPrime
// @info - This is the differential equation for the upper theta variable : theta1' = omega1
double DoublePendEquations::upperThetaPrime(double time) {

    return _omega1;
}

// @func - upperThetaPrime
// @info - This is the differential equation for the lower theta variable : theta2' = omega2
double DoublePendEquations::lowerThetaPrime(double time) {
    return _omega2;
}

// @func - upperThetaPrime
// @info - This is the differential equation for the upper omega (angular velocity) variable : omega1' = 2sin(theta_1-theta_2)...
double DoublePendEquations::upperOmegaPrime(double time) {
    double numerator = -1.0*_gravity*(2*_mass1+_mass2)*sin(_theta1) - _grav*_mass2*sin(_theta1-2*_theta2);
    numerator = numerator - 2*_mass2*sin(_theta1-_theta2)*(_length2*pow(_omega2, 2)+_length1*pow(_omega1, 2)*cos(_theta1-_theta2));

    double denominator =_length1*(2*_mass1+_mass2*(1-cos(2(_theta1-_theta2))));

    if(denominator == 0)
        throw std::logic_error("Error : Denominator 0 in upperOmegaPrime at t = " + time);

    return (double) numerator/denominator;
}

// @func - upperThetaPrime
// @info - This is the differential equation for the upper omega (angular velocity) variable : omega2' = L1cos(theta_1-theta_2)...
double DoublePendEquations::lowerOmegaPrime(double time) {

    double numerator = 2*sin(_theta1-_theta2);
    numerator *= (_length1*pow(_omega_1,2)*(_mass1+_mass2)*_gravity*cos(_theta1)*(_mass1+_mass2)+_length2*_mass2*pow(_omega2,2)*cos(_theta1-_theta2));

    double denominator = _length2*(2*_mass1+_mass2*(1-cos(2*(_theta1-_theta2))));

    if(denominator == 0)
        throw std::logic_error("Error : Denominator 0 in lowerOmegaPrime at t = " + time);

    return (double) numerator/denominator;
}

// @func - Constructor
// @args - #1 vector of values for the constants above
DoublePendEquations::DoublePendEquations(std::vector<double> constants) : FunctionWrapperRK4(4) {
    
    if(ic.size != 5) {
        throw std::logic_error("Error : Initial condition vector has wrong amount of information.
                                 Needs 5 double values (grav, ulen, umass, llen, lmass).");
    }

    for(auto x : & constants) {
        if(x <= 0) {
            throw std::logic_error("Error : All system-constant values must be positive.");
        }
    }

    _grav = constants[0];
    _length1 = constants[1];
    _mass1 = constants[2];
    _length2 = constants[3];
    _mass2 = constants[4];

}

// @func - Constructor #2
// @args - explicit values for constants above
DoublePendEquations::DoublePendEquations(double gravity, double ulength, double umass, double llength, double lmass) : FunctionWrapperRK4(4) {
    
    std::vector<double> constants = {gravity, ulength, umass, llength, lmass};

    if(ic.size != 5) {
        throw std::logic_error("Error : Initial condition vector has wrong amount of information.
                                 Needs 5 double values (grav, ulen, umass, llen, lmass).");
    }

    for(auto x : & constants) {
        if(x <= 0) {
            throw std::logic_error("Error : All system-constant values must be positive.");
        }
    }

    _grav = constants[0];
    _length1 = constants[1];
    _mass1 = constants[2];
    _length2 = constants[3];
    _mass2 = constants[4];
}

// @func - getValues
// @args - #1 current time value to be used in the calculations, #2 vector of values for the 4 changing state variables (uangle,
//         uangvel, langle, langvel)
// #info - This function is simply going to call the 4 private utility functions to get the values, it exists to fufill the interface defined
//         by the base class in the hierarchy.
std::vector<double> DoublePendEquations::getValues(double curr_time, const std::vector<double> & state) {

    if(state.size != 4) {
        throw std::logic_error("Error : state-vector must contain 4 double values (theta1, theta2, omega1, omega2.");
    }

    std::vector<double> diffeq_values;

    diffeq_values.push_back(upperThetaPrime(curr_time));
    diffeq_values.push_back(lowerThetaPrime(curr_time));
    diffeq_values.push_back(upperOmegaPrime(curr_time));
    diffeq_values.push_back(lowerOmegaPrime(curr_time));

    return diffeq_values;

}