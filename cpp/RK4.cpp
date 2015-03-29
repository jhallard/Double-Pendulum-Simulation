#include "RK4.h"


// @func - Constructor
// @args - #1 ptr to base class, should hold your derived class that contains the
//         equations of motion to be solved.
RK4::RK4(FunctionWrapperRK4 * fn) {
    
    if(fn == nullptr) {
        throw std::logic_error("Error : FunctionWrapper object must not be null.");
    }
    _equations = fn;

    if(_equations->getNumEquations() <= 0) {
        throw std::logic_error("Error : Cannot solve system of <1 equations.");
    }
    _num_equations = _equations->getNumEquations();

    _solutions.resize(_num_equations);
}


// @func - solve
// @args - #1 discretization, #2 final time for simulation (from 0s), #3 vector of initial condition values
bool RK4::solve(double disc, double tf, std::vector<double> ic) {
    if(disc <= 0) {
        throw std::logic_error("Error : Time step must be > 0.");
    }
    _disc = disc;

    if(tf <= 0) {
        throw std::logic_error("Error : Ending time must be > 0");
    }
    _tf = tf;

    if(ic.size() != _num_equations) {
        throw std::logic_error("Error : Not enough initial conditions Submitted");
    }

    std::vector<double> states = ic;
    int num_steps = (int)tf/disc;

    // main RK4 loop
    for(int i = 0; i < num_steps; i++) {
        double t = i*_disc;
        _k1 = _equations->getValues(t, states);
        _k2 = _equations->getValues(t+0.5*disc, stateAdjust(states, _k1, 0.5));
        _k3 = _equations->getValues(t+0.5*disc, stateAdjust(states, _k2, 0.5));
        _k4 = _equations->getValues(t+disc, stateAdjust(states, _k2, 1.0));

        std::vector<std::vector<double> > vals = {_k1, _k2, _k2, _k3, _k3, _k4};
        int it = 1;
        for(auto x : vals) {
           printf("%d : ", it++);
            for(auto y : x) {
                printf("%f ", y);
            }
            printf("\n\n");
        }
        std::vector<double> sum = vectorAdd(vals);

        states = stateAdjust(states, sum, 0.16666);

        // for(auto x : sum) {
        //     printf("%f ", x);
        // }
        // printf("\n\n");

    }


}


// @func - query
// @args - the time step you wish to extract values from (ex. 0.03333 for 30 fps)
std::vector<std::vector<double> > RK4::query(double step) {

    return _solutions;
}


// @func - setEquations
// @info - enter a new set of equations to be solved
bool RK4::setEquations(FunctionWrapperRK4 * fn) {
    if(fn == nullptr) {
        throw std::logic_error("Error : FunctionWrapper object must not be null.");
    }
    _equations = fn;

    if(_equations->getNumEquations() <= 0) {
        throw std::logic_error("Error : Cannot solve system of <1 equations.");
    }
    _num_equations = _equations->getNumEquations();

    _solutions.clear();
    _solutions.resize(_num_equations);
}

// @func - getEquations
// @info - get the equations object being used currently.
FunctionWrapperRK4 * RK4::getEquations() {
    return _equations;
}

// @func - stateAdjust
// @args - #1 vector to be adjusted, #2 vector to add to the first, #3 constant factor to adjust 2nd vector by
std::vector<double> RK4::stateAdjust(const std::vector<double> & base, const std::vector<double> & adj, double factor) {

    if(base.size() != adj.size()) {
        throw std::logic_error("Error : Vector addition requires same size vectors");
    }

    std::vector<double> ret;

    for(int i = 0; i < base.size(); i++) {
        ret.push_back(base[i]+adj[i]*factor*_disc);
    }

    return ret;
}


std::vector<double> RK4::vectorAdd(std::vector<std::vector<double> > vecs) {

    if(vecs.size() <= 0)
        return std::vector<double>();

    int size = vecs[0].size();

    std::vector<double> ret;

    for(auto vec : vecs) {
        if(vec.size() != size) {
            throw std::logic_error("Error : Vector addition requires same size vectors");
        }
    }

    for(int i = 0; i < size; i++) {
        ret.push_back(0.0);
    }

    for(int i = 0; i < vecs.size(); i++) {
        for(int j = 0; j < vecs[i].size(); j++) {
            ret[j] += vecs[i][j];
        }
    }

    return ret;
}