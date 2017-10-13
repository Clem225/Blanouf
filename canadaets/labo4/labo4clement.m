%% TP4

%% Choix avion : US Navy (premier) ==» Condition de vol 2

%% Caracteristiques

h = 15000;
M = 0.4;
V = 423;
g = 9.80665;
theta0 = 0;
u0 = V;

%%  Question 1


% Longitudinal

Xu = -0.0148;
Xalpha = -12.46;
Xw = Xalpha / V;

Zu = -0.160;
Zalpha = -219.6;
Zw = Zalpha / V;

Mu = 0.0005;
Malpha = -5.639;
Mw = Malpha / V;
Malpha_pt = -0.204;
Mw_pt = Malpha_pt / V;
Mq = -0.670;

Xgamaelevator = 2.55;
Zgamaelevator = -22.94;
Mgamaelevator = -7.40;


Alon = [Xu              Xw              0               -g*cos(theta0);
        Zu              Zw              u0              0;
        Mu+Mw_pt*Zu     Mw+Mw_pt*Zw     Mq+Mw_pt*u0     0;
        0               0               1               0]

Blon = [Xgamaelevator                       ;
        Zgamaelevator                       ;
        Mgamaelevator+Mw_pt*Zgamaelevator   ;
        0                                   ];
    
Clon = eye(4,4);
Dlon = [0; 0; 0; 0];   
    
coeffsAlon = poly(Alon)
polesAlon = eig(Alon)


% Lateral

Ybeta = -62.42;
Yp = 0;
Yr = 0;
Lbeta = -14.01;
Lp = -0.988;
Lr = 0.607;
Nbeta = 8.223;
Np = 0;
Nr = -0.401;

Ygamaileron = -0.795;
Ygamrudder = 10.83;
Lgamaileron = 8.757;
Lgamrudder = 2.802;
Ngamaileron = -0.246;
Ngamrudder = -3.651;

Alat = [Ybeta/u0 Yp/u0 -(1-Yr/u0) (g/u0)*cos(theta0);
        Lbeta    Lp    Lr         0                 ;
        Nbeta    Np    Nr         0                 ;
        0        1     0          0                 ]
 
Blat = [Ygamaileron/u0 Ygamrudder/u0;
        Lgamaileron    Lgamrudder   ;
        Ngamaileron    Ngamrudder   ;
        0              0            ];
    
Clat = eye(4,4);
Dlat = [0 0; 0 0; 0 0; 0 0];    
    
coeffsAlat = poly(Alat)
polesAlat = eig(Alat)

%%  Question 2

%  Période d’oscillation
wlat = abs(imag(polesAlat(1)));
Tlat = (2*pi)/wlat

wlon1 = abs(imag(polesAlon(1)));
Tlon1 = (2*pi)/wlon1

wlon2 = abs(imag(polesAlon(3)));
Tlon2 = (2*pi)/wlon2

%  Temps requis pour obtenir la moitié ou le double de l’amplitude
tlat = log(2)/abs(real(polesAlat(1)))

tlon1 = log(2)/abs(real(polesAlon(1)))
tlon2 = log(2)/abs(real(polesAlon(3)))

%  Nombre de cycles pour obtenir la moitié ou le double de l’amplitude
Nlat = tlat/Tlat

Nlon1 = tlon1/Tlon1
Nlon2 = tlon2/Tlon2

%  Constante de temps ?
tau1 = -1/real(polesAlat(3))
tau2 = -1/real(polesAlat(4))

tau = tau1 + tau2; % a voir

%%  Question 3
pulslon = zeros(1,4);
for i=1:4
    pulslon(i)=sqrt(real(real(polesAlon(i)))^2+imag(polesAlon(i))^2);
end

pulslat = zeros(1,4);
for i=1:4
    pulslat(i)=sqrt(real(real(polesAlat(i)))^2+imag(polesAlat(i))^2);
end

amorlon = zeros(1,4);
for i=1:4
    amorlon(i)=-(real(polesAlon(i)))/pulslon(i);
end

amorlat = zeros(1,4);
for i=1:4
    amorlat(i)=-(real(polesAlat(i)))/pulslon(i);
end


