clear all
close all
clc

% Mouvement longitudinal
% x = [u, w, q, theta] || u = [elevateur, TLA]
A_lon = [ -0.0066, 0.1178, -12.5704, -9.7477; ...
 -0.0910, -0.7560, 111.1563, -1.1037; ...
 0.0055, -0.0477, -0.8536, 0; 0, 0, 1, 0];

B_lon = [0.4909; -6.0184; -2.5926; 0];

% Mouvement lat�ral
% x = [v, p, r, phi] || u = [ailerons, rudder]
A_lat = [-0.1094, 13.0137, -110.3137, 9.7483; ...
 -0.0615, -1.8025, 0.9608, 0; 0.0024, -0.2635, -0.1127, 0; ...
 0, 1, 0.1127, 0];

B_lat = [0, 1.2045; 2.3141, 0.3154; 0.2011, -0.3226; 0 0];

[Wn_lon,zeta_lon,P_lon] = damp(A_lon)
[Wn_lat,zeta_lat,P_lat] = damp(A_lat)

% Visualisation du PIO
sys_lon = ss(A_lon, B_lon(:,1), [0 0 0 1], 0);
figure(); 
bode(sys_lon); 
grid on;

freq = 0.117; % voir figure rapport
phase = 180;

% Conception du correcteur
designTool(sys_lon);

Kq = -11.6667;
Kp = 0.3268;
Ki = 30.0;
