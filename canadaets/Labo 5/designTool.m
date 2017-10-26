function designTool(syslineaire)

A = syslineaire.a;
B = syslineaire.b;
C = [0 0 1 0];

[figure_axes, slider_control, text_box] = initialiseInterface();

while ishandle(figure_axes.q)
    
    kq = slider_control.kq.Value;
    kp = slider_control.kp.Value;
    ki = slider_control.ki.Value;
%     kq = get(slider_control.kq,'Value');
%     kp = get(slider_control.kp,'Value');
%     ki = get(slider_control.ki,'Value');
    
    % Calcul de retour :
    kx    = [0, 0, kq, 0];
    sysCl = ss([A-B*kx, -B*ki; -C, 0], [B*kp; 1], eye(5), zeros(5,1));
    t     = 0:0.1:10;
    u     = ones(size(t))*pi/180;
    y     = lsim(sysCl, u, t);
    de    = - kq*y(:,3) + kp*(u' - y(:,3)) - ki*y(:,5);
    
    % Performances :
    [wn,zeta] = damp(sysCl);
    
    plot(figure_axes.q, t, y(:,3)*180/pi);
    xlabel(figure_axes.q, 'temps [s]');
    ylabel(figure_axes.q, 'q [deg/s]');
    title(figure_axes.q, 'R?ponse de la vitesse de tangage (q)');
    grid(figure_axes.q, 'on');
    
    plot(figure_axes.de, t, de*180/pi);
    xlabel(figure_axes.de, 'temps [s]');
    ylabel(figure_axes.de, '\delta_e [deg]');
    title(figure_axes.de, 'Commande envoy?e aux ?l?vateurs (\delta_e)');
    grid(figure_axes.de, 'on');
    
    string{01,:} = ' ***************************** ';
    string{02,:} = ' *   R?sultats du contr?le   * ';
    string{03,:} = ' ***************************** ';
    string{04,:} = ' ';
    string{05,:} = ' ** Gains :';
    string{06,:} = sprintf('  -? kq = %+08.4f\n', kq);
    string{07,:} = sprintf('  -? kp = %+08.4f\n', kp);
    string{08,:} = sprintf('  -? ki = %+08.4f\n', ki);
    string{09,:} = ' ';
    string{10,:} = ' ** Performances :';
    string{11,:} = '  # Short Period :';
    string{12,:} = sprintf('  -? wn/zeta = %+06.2f / %+06.2f\n', wn(4), zeta(4));
    string{13,:} = ' ';
    string{14,:} = '  # Phugo?de :';
    string{15,:} = sprintf('  -? wn/zeta = %+06.2f / %+06.2f\n', wn(2), zeta(2));
    
    set(text_box, 'string', string);
    
    drawnow
    pause(0.1);
end

end

function [figure_axes, slider_control, text_box] = initialiseInterface()

screenSize = get(0,'ScreenSize');
width      = 800;
height     = 600;
pos        = [screenSize(3)/2-width/2 screenSize(4)/2-height/2 width height];

figure('units','pixels','position',pos,...
    'color',[.94 .94 .94],'numbertitle','off','MenuBar','none',...
    'name','Stabilit? & Contr?le d''un avion civil','ToolBar','none',...
    'resize','off');

logo_larcase = axes('Units','normalized', 'position',[0 0.77 1 0.3],...
    'box','off');                                              %#ok<*NASGU>

imshow('logoLarcase.jpg');

figure_axes.q = axes('Units','normalized',...
    'position',[0.1 0.5 0.5 0.3],'box','on');

figure_axes.de = axes('Units','normalized',...
    'position',[0.1 0.1 0.5 0.3],'box','on');

panel = uipanel('Title','Gains du compensateur',...
    'FontSize',10,'FontWeight','bold','BackgroundColor',[.94 .94 .94],...
    'ForeGround','black','Position',[.65 .51 .30 .30]);

uicontrol('parent', panel, 'Style', 'text', 'string', 'Kq', ...
    'Position', [65 135 100 20], 'fontsize', 10);

slider_control.kq = uicontrol('parent', panel, 'Style', 'slider',...
    'Min',-15,'Max',15,'Value',0,...
    'Position', [17 120 200 10],...
    'Callback', '');

uicontrol('parent', panel, 'Style', 'text', 'string', 'Ki', ...
    'Position', [65 80 100 20], 'fontsize', 10);

slider_control.ki = uicontrol('parent', panel, 'Style', 'slider',...
    'Min',0,'Max',30,'Value',0,...
    'Position', [17 70 200 10],...
    'Callback', '');

uicontrol('parent', panel, 'Style', 'text', 'string', 'Kp', ...
    'Position', [65 30 100 20], 'fontsize', 10);

slider_control.kp = uicontrol('parent', panel, 'Style', 'slider',...
    'Min',-10,'Max',10,'Value',0,...
    'Position', [17 15 200 10],...
    'Callback', '');

text_box = uicontrol('Style', 'listbox',...
    'Position', [521 60 240 200], 'BackGroundColor',[1 1 1],...
    'FontName','FixedWidth','FontSize', 8, 'FontUnits','normalized',...
    'SelectionHighlight','off','selected','off', 'string',...
    'Demarrage...');

uicontrol('style','text','units','normalized',...
    'position',[0 -0.03 1 0.1],'BackgroundColor',[.94 .94 .94],...
    'ForegroundColor',[0 0 0],'FontSize',8,'FontWeight','normal',...
    'HorizontalAlignment','center',...
    'string',['__________________________________________________________',...
    '____________________________________________________________________',...
    '_______']);

 uicontrol('style','text','units','normalized',...
    'position',[0 -0.035 1 0.07],'BackgroundColor',[.94 .94 .94],...
    'ForegroundColor',[0 0 0],'FontSize',12,'FontWeight','normal',...
    'HorizontalAlignment','center',...
    'string','?2014 G. GHAZI / LARCASE TOUS DROITS R?SERV?S');

end