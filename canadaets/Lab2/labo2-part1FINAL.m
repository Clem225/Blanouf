%% Labo2
%
clear all
close all
clc

%% Question 1
%
H = [0:1000:20000];
[T, a, P, rho] = atmosisa(H);

figure(1);

subplot(2,2,1);
plot(H,T);
title('Temperature en fonction de l''altitude');
xlabel('Altitude (m)');
ylabel('Température (K)');

subplot(2,2,2);
plot(H,a);
title('Vitesse du son en fonction de l''altitude');
xlabel('Altitude (m)');
ylabel('Vitesse du son (m/s2)');

subplot(2,2,3);
plot(H,P);
title('Pression en fonction de l''altitude');
xlabel('Altitude (m)');
ylabel('Pression (pascal)');

subplot(2,2,4);
plot(H,rho);
title('Densité de l''air en fonction de l''altitude');
xlabel('Altitude (m)');
ylabel('Densité de l''air (kg/m3)');


%En utilisant les equations
R=287;
L=6.5*10^-3;
g0 = 9.80665;

H = [0:1000:11000];
[T, a, P, rho] = atmosisa(H);

T_equa1 = T(1)*(1-((L)*H)/T(1));
a_equa1 = a(1)*sqrt(1-((L)*H)/T(1));
P_equa1 = P(1)*(1-((L)*H)/T(1)).^((g0)/(L*R));
rho_equa1 = rho(1)*(1-((L)*H)/T(1)).^(((g0)/(L*R))-1);

H = [12000:1000:20000];
[T, a, P, rho] = atmosisa(H);

T_equa2 = T;
a_equa2 = a;
P_equa2 = P(1)*exp((-g0./(R*T)).*(H-H(1)));
rho_equa2 = rho(1)*exp((-g0./(R*T)).*(H-H(1)));

H = [0:1000:20000];

figure();
subplot(2,2,1);
plot(H,[T_equa1 T_equa2]);
title('Temperature en fonction de l''altitude');
xlabel('Altitude (m)');
ylabel('Température (K)');

subplot(2,2,2);
plot(H,[a_equa1 a_equa2]);
title('Vitesse du son en fonction de l''altitude');
xlabel('Altitude (m)');
ylabel('Vitesse du son (m/s2)');

subplot(2,2,3);
plot(H,[P_equa1 P_equa2]);
title('Pression en fonction de l''altitude');
xlabel('Altitude (m)');
ylabel('Pression (pascal)');

subplot(2,2,4);
plot(H,[rho_equa1 rho_equa2]);
title('Densité de l''air en fonction de l''altitude');
xlabel('Altitude (m)');
ylabel('Densité de l''air (kg/m3)');



%% Question 2
%

Psmes = [10789 20145 28996 41358 50658 59789 70138 79864 90124 92654 93945 100123 100954 101325];
Ptmes = [29854 37416 45879 52678 64598 76458 86223 92600 97420 98500 99956 101000 101800 101325];
[T0, a0, P0, rho0] = atmosisa(0);

%Calcul de M
PtPsMes = Ptmes./Psmes;

M1 = [0:0.2:1];
M2 = [1.2:0.2:2];
M = [0:0.2:2];

PtPsM1 = (1 + 0.2.*M1.^2).^(3.5)
PtPsM2 = (166.92.*M2.^7)./((7.*M2.^2 - 1).^(2.5))
PtPsM = cat(2, PtPsM1, PtPsM2)

xq = PtPsMes;
vq1 = interp1(PtPsM,M,xq);
figure();
plot(PtPsM,M,'-',xq,vq1,'o');
title('Courbe du nombre de Mach en fonction du rapport Pt/Ps');
xlabel('Pt/Ps');
ylabel('M');
legend('Formule', 'Interpolation'); grid on ; box on;


%Calcul de Vc
Vc = [0:10:600];
Qc = zeros(1,size(Vc,2));
for i=1:length(Vc)
    if (Vc(i)/a0)<1
        Qc(i) = P0*(((1+0.2*(Vc(i)/a0)^2)^3.5)-1);
    else
        Qc(i) = P0*(((166.92*(Vc(i)/a0)^7)/(((7*(Vc(i)/a0)^2)-1)^2.5))-1);
    end
end

figure();
plot(Qc,Vc);
title('Qc vs Vc');
xlabel('Qc (Pa)');
ylabel('Vc (m/s)');

xq = Ptmes-Psmes;
vq1 = interp1(Qc,Vc,xq);
plot(Qc,Vc,'-',xq,vq1,'o');
title('Courbe de Vc en fonction de Pt-Ps');
xlabel('Pt-Ps');
ylabel('Vc');
legend('Formule', 'Interpolation'); grid on ; box on;


%Calcul de H en fct de Psmes
H = [0:1000:20000];
[T, a, P, rho] = atmosisa(H);
plot(H,P);

xq = Psmes;
vq1 = interp1(P,H,xq);
figure();
plot(H,P,'-',vq1,xq,'o');
title('Courbe de pression en fonction de l''altitude');
xlabel('H (m)');
ylabel('P (Pa)');
legend('Atm. standard', 'Interpolation'); grid on ; box on;
