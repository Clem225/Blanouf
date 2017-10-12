g = 9.81;
Ybeta = -62.42;
u0 = 423;
Yp = 0;
Yr = 0;
theta0 = 0;
Lbeta = -14.01;
Lp = -0.988;
Lr = 0.607;
Nbeta = 8.223;
Np = 0;
Nr = -0.401;

Alat = [Ybeta/u0 Yp/u0 -(1-Yr/u0) (g/u0)*cos(theta0);
        Lbeta    Lp    Lr         0                 ;
        Nbeta    Np    Nr         0                 ;
        0        1     0          0                 ];

coeffsAlat = poly(Alat)
polesAlat = eig(Alat)
 
Ygamaileron = -0.795;
Ygamrudder = 10.83;
Lgamaileron = 8.757;
Lgamrudder = 2.802;
Ngamaileron = -0.246;
Ngamrudder = -3.651;
 
Blat = [Ygamaileron/u0 Ygamrudder/u0;
        Lgamaileron    Lgamrudder   ;
        Ngamaileron    Ngamrudder   ;
        0              0            ];
    
Clat = eye(4,4);
Dlat = [0 0; 0 0; 0 0; 0 0];

