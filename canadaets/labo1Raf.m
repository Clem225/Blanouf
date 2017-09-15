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
title('Profil - RAF15');
xlabel('Pourcentage de corde');
ylabel('y_{int}, y_{ext}');
legend('Extrados', 'Intrados'); grid on ; box on; axis equal;

%%% COURBES CONCERNANT Alpha et Cz, Cz, et Cz/Cx
alpha = [-4:2:14,15,16,18,20]';
alpharaf15 = alpha;
Cz =  [-0.14 ; 0.02; 0.14; 0.32; 0.46; 0.60; 0.76; 0.90; 1.04; 1.16; 1.22; 1.16; 1.02; 0.94];     
Cx =   [0.014; 0.008; 0.008; 0.012; 0.020; 0.030; 0.044; 0.060; 0.070; 0.096; 0.110; 0.140; 0.210; 0.260];
 
%Valeurs Czmax, Cxmin et Fmax
sprintf('Valeurs pour RAF15 : ')
epaisseur_max = max(ext-int)
[Czmax, idMax] = max(Cz)
[Cxmin, idMin] = min(Cx)
[finesseMax, idFMax] = max(Cz./Cx)
alphaMax = alpha(idFMax)
Fmax = Czmax/Cxmin

figure('Name', 'Courbe de coefficient de portance VS angle d''attaque, RAF15');
hold on;
plot(alpha,Cz);
plot(alpha(idMax), Cz(idMax), 'or');
title('Courbe de coefficient de portance VS angle d''attaque, RAF15');
xlabel('Angle d''attaque');
ylabel('Coefficient de portance Cz');

figure('Name', 'Courbe de coefficient de trainee VS angle d''attaque, RAF15');
hold on;
plot(alpha,Cx);
plot(alpha(idMin), Cx(idMin), 'or');
title('Courbe de coefficient de trainee VS angle d''attaque, RAF15');
xlabel('Angle d''attaque');
ylabel('Coefficient de trainee Cx');

figure('Name', 'Courbe de finesse VS angle d''attaque, RAF15');
plot(alpha,Cz./Cx);
title('Courbe de finesse VS angle d''attaque, RAF15');
xlabel('Angle d''attaque');
ylabel('Finesse Cz/Cx');

%Polaire du profil
figure('Name', 'Polaire du profil - RAF15');
plot(Cx,Cz);
CxRAF15 = Cx;
CzRAF15 = Cz;
title('Polaire du profil - RAF15');
xlabel('Coefficient de trainee Cx');
ylabel('Coefficient de portance Cz');

%Rapport lie a la puissance requise pour propulser l'avion
figure('Name', 'Rapport lie a la puissance requise pour propulser l''avion - RAF15');
raf15 = Cz.^(3/2)./Cx;
plot(alpha,raf15);
title('Rapport lie a la puissance requise pour propulser l''avion - RAF15');
xlabel('Angle d''attaque alpha');
ylabel('Cx^{3/2}/Cz');




%PROFIL CLARK YH
%%% CONTOUR DU PROFIL
BA = [0;1.25;2.5;5;7.5;10;15;20;30;40;50;60;70;80;90;95;100];
ext = [3.5;5.45;6.5;7.9;8.85;9.6;10.68;11.36;11.7;11.4;10.51;9.15;7.42;5.62;3.84;2.93;2.05];
int = -[3.5;1.93;1.47;0.93;0.63;0.42;0.15;0.03;0;0;0;0;0.06;0.38;1.02;1.4;1.85];
figure('Name', 'Profil - CLARK YH');
plot(BA,[ext,int]);
title('Profil - CLARK YH');
xlabel('Pourcentage de corde');
ylabel('y_{int}, y_{ext}');
legend('Extrados', 'Intrados'); grid on ; box on; axis equal;

%%% COURBES CONCERNANT Alpha et Cz, Cz, et Cz/Cx
alpha = [-4:2:18,19,20,25,30]';
alphaclark = alpha;
Cz =  [-0.09;0.05;0.2;0.36;0.51;0.66;0.8;0.94;1.06;1.21;1.33;1.43;1.36;1.26;0.97;0.81];
Cx =   [0.01;0.009;0.01;0.015;0.022;0.033;0.045;0.062;0.083;.103;.125;.146;.170;.211;.324;.430];
 
%Valeurs Czmax, Cxmin et Fmax
sprintf('Valeurs pour CLARK YH : ')
epaisseur_max = max(ext-int)
[Czmax, idMax] = max(Cz)
[Cxmin, idMin] = min(Cx)
[finesseMax, idFMax] = max(Cz./Cx)
alphaMax = alpha(idFMax)
Fmax = Czmax/Cxmin

figure('Name', 'Courbe de coefficient de portance VS angle d''attaque, CLARK YH');
hold on;
plot(alpha,Cz);
plot(alpha(idMax), Cz(idMax), 'or');
title('Courbe de coefficient de portance VS angle d''attaque, CLARK YH');
xlabel('Angle d''attaque');
ylabel('Coefficient de portance Cz');

figure('Name', 'Courbe de coefficient de trainee VS angle d''attaque, CLARK YH');
hold on;
plot(alpha,Cx);
plot(alpha(idMin), Cx(idMin), 'or');
title('Courbe de coefficient de trainee VS angle d''attaque, CLARK YH');
xlabel('Angle d''attaque');
ylabel('Coefficient de trainee Cx');

figure('Name', 'Courbe de finesse VS angle d''attaque, CLARK YH');
plot(alpha,Cz./Cx);
title('Courbe de finesse VS angle d''attaque, CLARK YH');
xlabel('Angle d''attaque');
ylabel('Finesse Cz/Cx');

%Polaire du profil
figure('Name', 'Polaire du profil - CLARK YH');
plot(Cx,Cz);
CxCLARK = Cx;
CzCLARK = Cz;
title('Polaire du profil - CLARK YH');
xlabel('Coefficient de trainee Cx');
ylabel('Coefficient de portance Cz');

%Rapport lie a la puissance requise pour propulser l'avion
figure('Name', 'Rapport lie a la puissance requise pour propulser l''avion - CLARK YH');
clark = Cz.^(3/2)./Cx;
plot(alpha,clark);
title('Rapport lie a la puissance requise pour propulser l''avion - CLARK YH');
xlabel('Angle d''attaque alpha');
ylabel('Cx^{3/2}/Cz');


%PROFIL NACA 23018

BA = [0; 1.25; 2.5; 5.0; 7.5; 10; 15; 20; 25; 30; 40; 50; 60; 70; 80; 90; 95; 100];
ext = [0; 4.09; 5.29; 6.92; 8.01; 8.83; 9.86; 10.36; 10.56; 10.55; 10.04; 9.05; 7.75; 6.18; 4.40; 2.39; 1.32; 0];
int = -[0; 1.83; 2.71; 3.80; 4.60; 5.22; 6.18; 6.86; 7.27; 7.47; 7.37; 6.81; 5.94; 4.82; 3.48; 1.94; 1.09; 0];

figure('Name', 'Profil - NACA 23018');
plot(BA, [ext, int]);
title('Profil - NACA 23018');
xlabel('Pourcentage de corde');
ylabel('y_{int}, y_{ext}');
legend('Extrados', 'Intrados'); grid on ; box on; axis equal;

alpha = [-8:2:16]';
alphanaca = alpha;
Cz =  [-0.62 ; -0.47; -0.28; -0.09; 0.12; 0.33; 0.53; 0.72; 0.90; 1.01; 1.06; 0.75; 0.68];
Cx =  [0.016 ; 0.014; 0.012; 0.011; 0.010; 0.011; 0.012; 0.014; 0.016; 0.020; 0.028; 0.040; 0.060];

%Valeurs Czmax, Cxmin et Fmax
sprintf('Valeurs pour NACA 23018 : ')
epaisseur_max = max(ext-int)
[Czmax, idMax] = max(Cz)
[Cxmin, idMin] = min(Cx)
[finesseMax, idFMax] = max(Cz./Cx)
alphaMax = alpha(idFMax)
Fmax = Czmax/Cxmin

figure('Name', 'Courbe de coefficient de portance VS angle d''attaque, NACA 23018');
hold on;
plot(alpha,Cz);
plot(alpha(idMax), Cz(idMax), 'or');
title('Courbe de coefficient de portance VS angle d''attaque, NACA 23018');
xlabel('Angle d''attaque');
ylabel('Coefficient de portance Cz');

figure('Name', 'Courbe de coefficient de trainee VS angle d''attaque, NACA 23018');
hold on;
plot(alpha,Cx);
plot(alpha(idMin), Cx(idMin), 'or');
title('Courbe de coefficient de trainee VS angle d''attaque, NACA 23018');
xlabel('Angle d''attaque');
ylabel('Coefficient de trainee Cx');

figure('Name', 'Courbe de finesse VS angle d''attaque, NACA 23018');
plot(alpha,Cz./Cx);
title('Courbe de finesse VS angle d''attaque, NACA 23018');
xlabel('Angle d''attaque');
ylabel('Finesse Cz/Cx');

%Polaire du profil
figure('Name', 'Polaire du profil - NACA 23018');
plot(Cx,Cz);
CxNACA = Cx;
CzNACA = Cz;
title('Polaire du profil - NACA 23018');
xlabel('Coefficient de trainee Cx');
ylabel('Coefficient de portance Cz');


%Rapport lie a la puissance requise pour propulser l'avion
figure('Name', 'Rapport lie a la puissance requise pour propulser l''avion - NACA 23018');
naca = Cz.^(3/2)./Cx;
plot(alpha,naca);
title('Rapport lie a la puissance requise pour propulser l''avion - NACA 23018');
xlabel('Angle d''attaque alpha');
ylabel('Cx^{3/2}/Cz');

figure('Name', 'Rapport lie a la puissance requise pour propulser l''avion - TOUT');
hold on;
plot(alpharaf15,raf15);
plot(alphaclark,clark);
plot(alphanaca,naca);
title('Rapport lie a la puissance requise pour propulser l''avion - TOUT');
xlabel('Angle d''attaque alpha');
ylabel('Cx^{3/2}/Cz');

figure('Name', 'Polaire du profil - TOUT');
hold on;
plot(CxRAF15,CzRAF15);
plot(CxCLARK,CzCLARK);
plot(CxNACA,CzNACA);
title('Polaire du profil - TOUT');
xlabel('Coefficient de trainee Cx');
ylabel('Coefficient de portance Cz');
