clear all
close all
clc

%PROFIL RAF15
%%% CONTOUR DU PROFIL
BA = [0;1.25;2.5;5;7.5;10;15;20;30;40;50;60;70;80;90;95;100];
ext = [1.5;3.14;3.94;5;5.37;6.09;6.67;6.96;6.94;6.63;6.13;5.52;4.79;3.91;2.81;2.17;0.94];
int = -[1.50;0.76;0.5;0.18;0.02;0.02;0.18;0.53;1.02;1.02;0.71;0.33;0.06;0.04;0.21;0.32;0.94];
figure('Name', 'Profil - RAF15');
plot(BA,[ext,int]);
xlabel('Pourcentage de corde');
ylabel('y_{int}, y_{ext}');
legend('Extrados', 'Intrados'); grid on ; box on; axis equal;

%%% COURBES CONCERNANT Alpha et Cz, Cz, et Cz/Cx
alpha = [-4:2:14,15,16,18,20]';
Cz =  [-0.14 ; 0.02; 0.14; 0.32; 0.46; 0.60; 0.76; 0.90; 1.04; 1.16; 1.22; 1.16; 1.02; 0.94];     
Cx =   [0.014; 0.008; 0.008; 0.012; 0.020; 0.030; 0.044; 0.060; 0.070; 0.096; 0.110; 0.140; 0.210; 0.260];
 
figure('Name', 'Courbe de coefficient de portance VS angle d''attaque, RAF15');
plot(alpha,Cz);
title('Courbe de coefficient de portance VS angle d''attaque, RAF15');
xlabel('Angle d''attaque');
ylabel('Coefficient de portance Cz');

figure('Name', 'Courbe de coefficient de trainee VS angle d''attaque, RAF15');
plot(alpha,Cx);
title('Courbe de coefficient de trainee VS angle d''attaque, RAF15');
xlabel('Angle d''attaque');
ylabel('Coefficient de trainee Cx');

figure('Name', 'Courbe de finesse VS angle d''attaque, RAF15');
plot(alpha,Cz./Cx);
title('Courbe de finesse VS angle d''attaque, RAF15');
xlabel('Angle d''attaque');
ylabel('Finesse Cz/Cx');

%Valeurs Czmax, Cxmin et Fmax
sprintf('Valeurs pour RAF15 : ')
Czmax = max(Cz)
Cxmin = min(Cx)
Fmax = Czmax/Cxmin

%Polaire du profil
figure('Name', 'Polaire du profil - RAF15');
plot(Cx,Cz);
title('Polaire du profil - RAF15');
xlabel('Coefficient de trainee Cx');
ylabel('Coefficient de portance Cz');

%Rapport lie a la puissance requise pour propulser l'avion
figure('Name', 'Rapport lie a la puissance requise pour propulser l''avion - RAF15');
plot(alpha,Cz.^(3/2)./Cx);
title('Rapport lie a la puissance requise pour propulser l''avion - RAF15');
xlabel('Coefficient de trainee Cx');
ylabel('Coefficient de portance Cz');




%PROFIL CLARK YH
%%% CONTOUR DU PROFIL
BA = [0;1.25;2.5;5;7.5;10;15;20;30;40;50;60;70;80;90;95;100];
ext = [3.5;5.45;6.5;7.9;8.85;9.6;10.68;11.36;11.7;11.4;10.51;9.15;7.42;5.62;3.84;2.93;2.05];
int = -[3.5;1.93;1.47;0.93;0.63;0.42;0.15;0.03;0;0;0;0;0.06;0.38;1.02;1.4;1.85];
figure('Name', 'Profil - CLARK YH');
plot(BA,[ext,int]);
xlabel('Pourcentage de corde');
ylabel('y_{int}, y_{ext}');
legend('Extrados', 'Intrados'); grid on ; box on; axis equal;

%%% COURBES CONCERNANT Alpha et Cz, Cz, et Cz/Cx
alpha = [-4:2:18,19,20,25,30]';
Cz =  [-0.09;0.05;0.2;0.36;0.51;0.66;0.8;0.94;1.06;1.21;1.33;1.43;1.36;1.26;0.97;0.81];
Cx =   [0.01;0.009;0.01;0.015;0.022;0.033;0.045;0.062;0.083;.103;.125;.146;.170;.211;.324;.430];
 
figure('Name', 'Courbe de coefficient de portance VS angle d''attaque, CLARK YH');
plot(alpha,Cz);
title('Courbe de coefficient de portance VS angle d''attaque, CLARK YH');
xlabel('Angle d''attaque');
ylabel('Coefficient de portance Cz');

figure('Name', 'Courbe de coefficient de trainee VS angle d''attaque, CLARK YH');
plot(alpha,Cx);
title('Courbe de coefficient de trainee VS angle d''attaque, CLARK YH');
xlabel('Angle d''attaque');
ylabel('Coefficient de trainee Cx');

figure('Name', 'Courbe de finesse VS angle d''attaque, CLARK YH');
plot(alpha,Cz./Cx);
title('Courbe de finesse VS angle d''attaque, CLARK YH');
xlabel('Angle d''attaque');
ylabel('Finesse Cz/Cx');

%Valeurs Czmax, Cxmin et Fmax
sprintf('Valeurs pour CLARK YH : ')
Czmax = max(Cz)
Cxmin = min(Cx)
Fmax = Czmax/Cxmin

%Polaire du profil
figure('Name', 'Polaire du profil - CLARK YH');
plot(Cx,Cz);
title('Polaire du profil - CLARK YH');
xlabel('Coefficient de trainee Cx');
ylabel('Coefficient de portance Cz');

%Rapport lie a la puissance requise pour propulser l'avion
figure('Name', 'Rapport lie a la puissance requise pour propulser l''avion - CLARK YH');
plot(alpha,Cz.^(3/2)./Cx);
title('Rapport lie a la puissance requise pour propulser l''avion - CLARK YH');
xlabel('Coefficient de trainee Cx');
ylabel('Coefficient de portance Cz');


