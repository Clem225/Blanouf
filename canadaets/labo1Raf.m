%PROFIL NACA 23018

BA = [0; 1.25; 2.5; 5.0; 7.5; 10; 15; 20; 25; 30; 40; 50; 60; 70; 80; 90; 95; 100];
EXT = [0; 4.09; 5.29; 6.92; 8.01; 8.83; 9.86; 10.36; 10.56; 10.55; 10.04; 9.05; 7.75; 6.18; 4.40; 2.39; 1.32; 0];
INT = -[0; 1.83; 2.71; 3.80; 4.60; 5.22; 6.18; 6.86; 7.27; 7.47; 7.37; 6.81; 5.94; 4.82; 3.48; 1.94; 1.09; 0];

figure('Name', 'Profil - NACA 23018');
plot(BA, [EXT, INT]);
title('Profil - NACA 23018');
xlabel('Distance du bord d''attaque');
ylabel('y_{int}, y_{ext}');

alpha = [-8:2:16]';
Cz =  [-0.62 ; -0.47; -0.28; -0.09; 0.12; 0.33; 0.53; 0.72; 0.90; 1.01; 1.06; 0.75; 0.68];
Cx =  [0.016 ; 0.014; 0.012; 0.011; 0.010; 0.011; 0.012; 0.014; 0.016; 0.020; 0.028; 0.040; 0.060];

figure('Name', 'Courbe de coefficient de portance VS angle dattaque - NACA 23018');
plot(alpha,Cz);
title('Courbe du coefficient de portance par rapport a l''angle d''attaque');
xlabel('Angle d''attaque');
ylabel('Coefficient de portance Cz');


Czmax = max(Cz)

figure('Name', 'Courbe de coefficient de trainee VS angle dattaque - NACA 23018');
plot(alpha,Cx);

Cxmin = min(Cx)

figure('Name', 'Courbe de finesse VS angle dattaque - NACA 23018');
plot(alpha,Cz./Cx);

figure('Name', 'Polaire du profil - NACA 23018');
plot(Cx, Cz);

figure('Name', 'Rapport lié a la puissance requise pour propulser l''avion - NACA 23018');
plot(alpha, Cz.^(3/2)./Cx);

