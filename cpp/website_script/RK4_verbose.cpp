#include "../RK4.h"


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

    _k1.resize(_num_equations, 0.0);
    _k2.resize(_num_equations, 0.0);
    _k3.resize(_num_equations, 0.0);
    _k4.resize(_num_equations, 0.0);


}

void printKValues(std::vector<std::vector<double> > vals) {
    int it = 1;
    for(auto x : vals) {
       printf("%d : ", it++);
        for(auto y : x) {
            printf("%f ", y);
        }
        printf("\n");
    }
}


// @func - solve
// @args - #1 discretization, #2 final time for simulation (from 0s), #3 vector of initial condition values
bool RK4::solve(long double disc, double tf, std::vector<double> ic) {
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
    int num_steps = tf/disc;

    _solutions.clear();
    _solutions.resize(_num_equations);

    for(auto & x: _solutions) {
        x.resize(num_steps);
    }

    // long double average_add_solutions = 0.0;
    // long double average_k1 = 0.0, average_k2 = 0.0, average_k3 = 0.0, average_k4 = 0.0;
    // long long int count = 0; 

    // auto start = std::chrono::high_resolution_clock::now(); // #remove
    // auto elapsed = std::chrono::high_resolution_clock::now() - start;   
    // long double m = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    // main RK4 loop
    for(int i = 0; i < num_steps; i++) {
        double t = i*_disc;


            for(int j = 0; j < states.size(); j++) {
                _solutions[j][i] = states[j];
            }


        _equations->getValues(t, states, &_k1);
        _equations->getValues(t+0.5*disc, stateAdjust(states, _k1, 0.5), &_k2);
        _equations->getValues(t+0.5*disc, stateAdjust(states, _k2, 0.5), &_k3);
        _equations->getValues(t+1.0*disc, stateAdjust(states, _k3, 1.0), &_k4);


        std::vector<std::vector<double> *> vals = {&_k1, &_k2, &_k2, &_k3, &_k3, &_k4};
        // printKValues(vals);

        std::vector<double> sum = vectorAdd(vals);

        states = stateAdjust(states, sum, 0.16666);
    }



    return true;
}

// @func - query
// @args - #1 the starting time for the query, #2 the end time for the query, #3 the time step you wish to jump between those points
std::vector<std::vector<double> > RK4::query(double t0, double tf, double step) {

    if(t0 < 0 || tf > _tf || step > tf-t0) {
        throw std::logic_error("Error : Invalid bounds in query");
    }
    int start_index = t0/_disc;
    if(start_index < 0) {
        start_index = 0;
    }
    int end_index = tf/_disc;
    int jump = step/_disc;

    std::vector<std::vector<double> > ret(_num_equations);

    for(int i = start_index; i < end_index && i < _solutions[0].size(); i += jump) {
        for(int j = 0; j < _num_equations; j++) {
            ret[j].push_back(_solutions[j][i]);
        }
    }
    return ret;
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

    std::vector<double> ret(base.size());

    for(int i = 0; i < base.size(); i++) {
        ret[i] = base[i]+adj[i]*factor*_disc;
    }

    return ret;
}

// @func - vectorAdd
// @info - takes a vector of vectors of the same length and adds all the components together
std::vector<double> RK4::vectorAdd(const std::vector<std::vector<double> * > & vecs) {

    if(vecs.size() <= 0) {
        return std::vector<double>();
    }

    int size = vecs[0]->size();

    std::vector<double> ret(_num_equations, 0.0);

    // this is a good error-checking method but it is costly, makes the solve function 10-15% less efficient.
    // for(auto vec : vecs) {
    //     if(vec.size() != size) {
    //         throw std::logic_error("Error : Vector addition requires same size vectors");
    //     }
    // }

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < vecs.size(); j++) {
            ret[i] += vecs[j]->at(i);
        }
    }

    return ret;
}
