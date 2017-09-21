Psmes = [10789 20145 28996 41358 50658 59789 70138 79864 90124 92654 93945 100123 100954 101325];
Ptmes = [29854 37416 45879 52678 64598 76458 86223 92600 97420 98500 99956 101000 101800 101325];

PtPsMes = Ptmes./Psmes;

%Calcul de M à partir de PT / PS

M1 = [0:0.2:1];
M2 = [1.2:0.2:2];
M = [0:0.2:2];

PtPsM1 = (1 + 0.2.*M1.^2).^(3.5)
PtPsM2 = (166.92.*M2.^7)./((7.*M2.^2 - 1).^(2.5))
PtPsM = cat(2, PtPsM1, PtPsM2)

xq = PtPsMes;
vq1 = interp1(PtPsM,M,xq);
plot(PtPsM,M,'-',xq,vq1,'o');
title('Courbe du rapport Pt/Ps en fonction du nombre de Mach');
xlabel('Pt/Ps');
ylabel('M');
legend('Formule', 'Interpolation'); grid on ; box on;

