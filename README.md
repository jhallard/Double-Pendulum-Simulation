Double-Pendulum-Simulation
==========================

All of the code used to make the simulations and graphics in these posts [(1, ](https://jhallard.com/blog/double_pendulum.html)[2, ](https://jhallard.com/blog/double_pendulum_2.html)[3)](#) on my blog. Included are implementations of a double-pendulum simulator in the Matlab, Python, and C++ programming languages, along with some 3rd party libraries for graphing help.

```
git clone https://github.com/jhallard/Double-Pend-Simulation.git
cd Double-Pend-Simulation
```

### Matlab

Open up Matlab and navigate to the ``Double-Pendulum-Simulation/matlab/`` directory.
You will be calling one of the ``DoublePendSimulation()`` functions, and passing in 3 arguments, one of them being a vector arugments itself. The 4 arguments are :
1. IC - Initial conditions vector.  `ic = [theta1; angvel1; theta2; angvel2; grav; mass1; mass2; len1; len2;]`
2. time - The ending time of the simulation.
3. simspeed - A factor by which to slow-down the simulation, i.e. 2.0 means twice as slow (2x fps).

##### Examples
```matlab
DoublePendSimulation3([.849;-.2;-1.35;0;9.81;0.9;.7;.6;.4],55,1.0, 2);
DoublePendSimulation4([.75;-.2;-.1.15;0;9.81;0.9;.7;.6;.4],35,1.0, 2);
```

### C++
Currently in progress, almost finished with the Runge-Kutta solver, then I can move onto the simulation code. 

### Python 
Have not started yet, check back soon for updates.


