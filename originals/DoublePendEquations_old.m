%
%   @author John Allard
%   This file holds the differential equations that represent the motion
%   of a double pendulum.
%
%   @param ic
%   ic= [theta1, dtheta1, theta2, dtheta2, grav, m1, m2, len1, len2]
%   ic is a vector of initial conditions needed to properly set up the
%   equations of the double pendulum
%
%   ---------------------------------------------------------------------

function xdot = DoublePendEquations(t, ic)

%extract the initial conditions from the ic vector
grav=ic(5); m1=ic(6); m2=ic(7); len1=ic(8); len2=ic(9);
theta1 = ic(1); theta2 = ic(3);
dtheta1 = ic(2); dtheta2 = ic(4);


xdot=zeros(9,1);

%theta1 prime = angular velocity1
xdot(1)=dtheta1;

% angularvelocity1 prime = this equation 
xdot(2)= -(grav.*(2*m1+m2)*sin(theta1) + m2*grav*sin(theta1-2*theta2)...
         + 2*sin(theta1-theta2)*m2*((dtheta2.^2)*len2 + (dtheta1.^2).*len1*cos(theta1-theta2)))/...
         (len1*(2*m1+m2-m2*cos(2*theta1-2*theta2)));

%theta2 prime = angular velocity2
xdot(3)=dtheta2;

%angularvelocity2 prime = this equation
xdot(4)= (2*sin(theta1-theta2)*((dtheta1.^2)*len1*(m1+m2)+grav*(m1+m2)*cos(theta1)...
         +(dtheta2.^2)*len2*m2*cos(theta1-theta2)))/...
         (len2*(2*m1+m2-m2*cos(2*theta1-2*theta2)));
     
     
end