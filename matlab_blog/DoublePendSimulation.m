% This solves and animates the motion, angle, or angular velocity of a double 
% pendulum system as it progresses through time
%
%   @author John Allard
%   ---------------------------------------------------------------------
%   
%   @params ic
%   ic = [theta1; angvel1; theta2; angvel2; grav; mass1; mass2; len1; len2;]
%   ic - Initial Conditions, is a 9 length row vector that represents the
%   initial conditions of the pendulm system.
%   a 1 after the parameter name means upper pendulum, 2 means lower pendulum.
%
%   @param time
%   The length in seconds of the simulation. It must always start at zero,
%   and it's value will be the length of the simulation at 100% of normal
%   running speed
%
%   @param simspeed
%   This number is a double that represents a percentage in a decimal
%   format. This percentage is the simulation speed as a percentage of the
%   normal speed. So 50% speed would have simspeed = 0.5.
%
%   @param angorangvel
%   This is either a 1 or a 2, do not pass in a value besides these. If it
%   is a 1, then the graph on the right will show the angles of the two
%   pendulums as they move throughout time. If this value is a 2, then the
%   graph on the right will be the angular velocities of the two pendulums
%   as they move throughout time.

%%   ---------------------------------------------------------------------

function DoublePendSimulation(ic, time, simspeed, angorangvel)
clear All;

opengl software;

%define the normal frames per second of the animation and the adjusted
%frames per second based on the simspeed variable.
fpsnormal = 30;
fps = fpsnormal*simspeed; 
numframes=time*fps;

%define the tolerances for the Runge-Kutta method of the differential
%equation
options = odeset('Refine',6,'RelTol',1e-5,'AbsTol',1e-7); 

%solve the differential equations defined in the file @DoublePEndEquations,
%over the interval t = 0 to t = time, with the initial conditions specified
%in the vector ic, according to the options defined directly above.
solutionsstruct=ode45(@DoublePendEquations,[0 time], ic, options);
%define a discrete vector of points that we want to obtain the solutions on
t = linspace(0,time,numframes);
%obtain the values of the differential equations defined on the linespace
%above
solutionsvector=deval(solutionsstruct,t);

% get the individual components of the solution vector
theta1=solutionsvector(1,:)'; angvel1=solutionsvector(2,:)';
theta2=solutionsvector(3,:)'; angvel2=solutionsvector(4,:)';
%get the individual initial conditions and constants passed in by the user
len1=ic(8); len2=ic(9);
m1 = ic(6); m2 = ic(7);
moment1 = 0.5.*m1.*len1.^2;
moment2 = 0.5*m2.*len2.^2;
grav = ic(5);

%initialize vectors to hold the x and y coordinated of the lines we are
%going to be plotting
linex1 = zeros(0, numframes-1);
linex2 = zeros(0,numframes-1); % x/y coordinates of trailing line for position 
liney2 = zeros(0,numframes-1);
liney1 = zeros(0, numframes-1);
omega1 = zeros(0, numframes-1); 
omega2 = zeros(0, numframes-1);
ang1 = zeros(0,numframes-1);
ang2 = zeros(0,numframes-1);
timearr = zeros(0,numframes-1);

%you can ignore these next 4 lines, they were used for an energy analysis
%of the system
maxval= max(omega1(:));
maxval2 = max(omega2(:));
maxv = [moment1.*maxval.^2 moment2.*maxval2.^2];
[maxe junk] = max(maxv);


%create the figure window, set it to outer edges of screen
figure('units','normalized','outerposition',[0 0 1 1]);
% this subplot defnes the coordinates and size of the pendulum pos. plot
subplot('Position',[.03 .1 .52 .8]);hold on;

% this plots the line that shows where the bottom pendulum has been
pendline = plot([0 0], [0 0], 'Color', [1 153/255 0]);
%h is the handle to the actual plot of the 2 pendulums x and y coordinates
rods = plot(0,0,'k', 'LineWidth',2);
%this plot places the objects on the ends up the pendulums 
ColorSet = [0 0 0; 1 0 1; 1 0 0];
pendobjects = scatter([0 0 0], [0 0 0], [50, 100, 100], ColorSet, 'filled');
axis equal;grid on;
title('Double Pendulum Motion', 'fontweight', 'bold', 'fontsize',10); hold off;

range=1.1*(len1+len2); axis([-range range -range range]); %pos plot axis limits

%dfine the subplot and plot for the second plot (theta plot or angvel plot)
subplot('Position', [.56 .1 .38 .8]);
%this is for the upper pendulum
plot2l1 = plot(0, 0,'r', 'LineWidth', 1.2);grid minor; hold on;
%this is for the lower pendulum
plot2l2 = plot(0, 0, 'b', 'LineWidth', 1.2, 'MarkerSize', 50);
if(angorangvel == 1)
    title('Upper and Lower Angle vs Time','fontweight','bold','fontsize',10);grid on;
end;
if(angorangvel == 2)
    title('Upper and Lower Anglular Velocity vs Time','fontweight','bold','fontsize',10);
end;
grid on;
hold off;

%put the data from the ODE solution into vector to be plotted
linex1 = len1*sin(theta1);
liney1 = -len1*cos(theta1);
linex2 = linex1+len2*sin(theta2);
liney2 = liney1-len2*cos(theta2);

%IGNORE all of these next commented lines, they were used for an energy
%analysis of the system
%height = len1+len2;
%en = .5.*(m1+m2).*(len1.^2).*angvel1.^2 + .5.*m2.*(len2.^2).*(angvel2.^2)...
%    + m2.*len1.*len2.*(angvel1).*angvel2.*cos(theta2-theta1)+(m1+m2).*grav.*len1.*(1-cos(theta1))+m2.*grav.*len2.*(1-cos(theta2));
%en1 = zeros(0, numframes-1);
%pot1 = m1.*grav.*(range+liney1);
%pot2 = m2.*grav.*(range+liney2);
%kin1 = .5*m1.*(angvel1.^2.*len1.^2);
%kin2 = en-pot1-pot2-kin1;
%enmax = max(en);
%ploten = bar([0 0], .5); ylim([0 enmax]); grid on;



%simulation loop
    for i=1:numframes
            timearr(i) = i/fps;
            Xcoord=[0,linex1(i),linex2(i)];
            Ycoord=[0,liney1(i),liney2(i)];
            
            %moment2 = 0.5*m2.*(linex2(i).^2 + liney2(i).^2);
            
            ang1(i) = theta1(i);
            ang2(i) = theta2(i);
            omega1(i) = angvel1(i);
            omega2(i) = angvel2(i);
            
            %ignore these next lines, they were used for an energy analysis
            k1 = .5.*moment1*(angvel1(i).^2);
            k2 = .5.*moment2*(angvel2(i).^2)+ .5*m2*angvel1(i).^2/len1.^2;
            u1 = (Ycoord(2)).*grav.*m1;
            u2 = (Ycoord(3)).*grav.*m2;
            
            %pendulum position simulation
            set(pendline,'XData',linex2(1:i),'YData',liney2(1:i));
            %uncomment the following if-statements if you want the line to
            %only last for the last 200 frames
            %if(i > 200)
            %    set(pendline,'XData',linex2(i-200:i),'YData',liney2(i-200:i));
            %end
            %if(i < 200)
            %    set(pendline,'XData',linex2(1:i),'YData',liney2(1:i));
            %end
            set(rods,'XData',Xcoord,'YData',Ycoord);
            set(pendobjects,'Xdata', Xcoord, 'YData', Ycoord);
            
            ax1 = get(plot2l1,'Parent');
            ax2 = get(plot2l2,'Parent');
            %these next two plot the two angles or angular velocities vs
            %time on the same graph, depending on the value of angorangvel
            if(angorangvel == 1)
                set(plot2l1,'XData',timearr,'YData',ang1);
                set(ax1,'XLIM',[timearr(i)-4 timearr(i)+1.5])
                set(plot2l2,'XData',timearr,'YData', ang2);
                set(ax2,'XLIM',[timearr(i)-4 timearr(i)+1.5]);
            end
            if(angorangvel==2)
                set(plot2l1,'XData',timearr,'YData',omega1);
                set(ax1,'XLIM',[timearr(i)-4 timearr(i)+1.5])
                set(plot2l2,'XData',timearr,'YData', omega2);
                set(ax2,'XLIM',[timearr(i)-4 timearr(i)+1.5]);
            end
            
            %ENERGY
            %en1(i) = en(i);
            %enarr = [kin1(i); kin2(i); pot1(i); pot2(i)];
            %set(ploten,'YData', enarr);
            
            %3D plot of position and angvel
            %set(plot2l2, 'XData',linex1(1:i),'YData',liney1(1:i),'ZData', angvel1(1:i));
            %set(plot2l3, 'XData',linex2(1:i),'YData',liney2(1:i),'ZData', angvel2(1:i));

            %set(plot2l2, 'XData',linex1(1:i),'YData',liney1(1:i),'ZData',zeros(1,i));
            %set(plot2l3, 'XData',linex1(1:i)+linex2(1:i),'YData',linex1(1:i),'ZData', liney2(1:i)-liney1(1:i));
      
      
            drawnow;
            %F(i) = getframe;
    end