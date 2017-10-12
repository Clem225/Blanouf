%%GPA745 LABO3

clear all
close all
clc

%% QUESTION 1
% Donnees groupe 2
% Modele : ville = [lat_degre lat_minute long_degre long_minute]
brun = [31 03.03 81 26.76]; %N W
sava = [32 09.63 81 06.75]; %N W

lat1 = brun(1) + brun(2)/60;
lon1 = - (brun(3) + brun(4)/60);

lat2 = sava(1) + sava(2)/60;
lon2 = - (sava(3) + sava(4)/60);

dlat = abs(lat2-lat1); %degres
dlon = abs(lon2-lon1); %degres

mlat = (lat1+lat2)/2; %degre
A = 60*cos(deg2rad(mlat));

D = sqrt((60*dlat)^2+(A*dlon)^2); %nm

w = rad2deg(asin(dlat*60/D)); %degres

% Calcul du True Course
if (dlat>=0 && dlon>=0)
	TC=90-w;
else
    if (dlat<0 && dlon >=0)
        TC=90+w;
    else
        if (dlat<0 && dlon <0)
            TC=270-w;
        else
           TC=270+w;
        end
    end
end

% %Valeurs trouvees sur geomag
% VAR_brun = 6;
% VAR_sava = 7;
% VAR = mean([VAR_brun VAR_sava]);

VAR = 4;
MC =  TC + VAR;

%% QUESTION 2
%

WD = [0:10:360];
WV = [5:5:50];
TAS = [50, 100, 160, 450];

GS_sans_vent = zeros(length(TAS),length(WV));
GS_vent_dos = zeros(length(TAS),length(WV));
GS_vent_face = zeros(length(TAS),length(WV));

for j = 1:length(WV)
    for i = 1: length(TAS)
        GS_sans_vent(i,j)=TAS(i);
        GS_vent_dos(i,j)=TAS(i)+WV(j);
        GS_vent_face(i,j)=TAS(i)-WV(j);
    end
    plot(TAS,GS_vent_dos(:,j),'red'); hold on
    plot(TAS,GS_sans_vent(:,j),'green');     
    plot(TAS,GS_vent_face(:,j), 'blue'); 
end
title('Graphique de la vitesse de l''avion par rapport au sol');
xlabel('TAS (noeuds)');
ylabel('GS (noeuds)');
legend ('Vent dans le dos', 'Sans vent', 'Vent de face');
hold off

WA = TC - WD;

WCA = zeros(length(TAS),length(WV), length(WD));
GS = zeros(length(TAS),length(WV), length(WD));
MH = zeros(length(TAS),length(WV), length(WD));
for k=1:length(TAS)
	for j=1:length(WV)
        M{j} = ['WV = ' num2str(WV(j))];
        for i=1:length(WA)
            WCA(i,j,k) = rad2deg(asin(sin(deg2rad(WA(i)))*WV(j)/TAS(k)));
            MH(i,j,k) = TC + VAR - WCA(i,j,k);
            GS(i,j,k) = TAS(k)*sin(deg2rad(WA(i)-WCA(i,j,k)))/sin(deg2rad(WA(i)));
        end
	end
    figure();
    plot(WD, WCA(:,:,k))
    titre = ['Graphique de l''angle de la dérive pour une vitesse TAS = ' num2str(TAS(k))];
    xlabel('WD (deg)');
    ylabel('WCA (deg)');
    title(titre);
    legend(M)
    
    figure();
    plot(WD, MH(:,:,k))
    titre = ['Graphique du cap magnétique pour une vitesse TAS = ' num2str(TAS(k))];
    xlabel('WD (deg)');
    ylabel('MH (deg)');
    title(titre);
    legend(M)
    
	figure();
    plot(WD, GS(:,:,k))
    titre = ['Graphique de la vitesse par rapport au sol (GS) pour une vitesse TAS = ' num2str(TAS(k))];
    xlabel('WD (deg)');
    ylabel('GS (noeuds)');
    title(titre);
    legend(M)
end 