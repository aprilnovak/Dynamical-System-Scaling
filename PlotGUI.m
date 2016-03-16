function simple_gui2

% Name of data folders of interest (for Plot 1 and Plot 2)

global Folder1;
%Folder1 = 'Iterating4/';
Folder1 = 'Iterating4_better_guesses/';
%Folder1 = 'Iterating_Area_Modified/';
%Folder1 = 'Iterating_Prototype/';
%Folder1 = 'Iterating_LongTerm/';

global Folder2;
%Folder2 = 'Iterating4/';
%Folder2 = 'Iterating4_better_guesses/';
Folder2 = 'Iterating_Area_Modified/';
%Folder2 = 'Iterating_Prototype/';
%Folder2 = 'Iterating_LongTerm/';


% Name of the test files (generic)
global Tests;
Tests = 'Test*';

% Path to location where the Folders are held. 
global Path;
Path ='/Users/aprilnovak/Documents/RELAP/Output/';
DirFolder = dir(strcat(Path,'It*'));

% How the GUI is centered on the screen
f = figure('Visible','off','Name','Welcome to One Stop Plot!','NumberTitle','off','Position',[140,100,1000,600]);
%set ( f, 'Color', [1 1 1] )
htitle = uicontrol('Style','text','Position',[10,575,120,20],'String','One Stop Plot','FontSize',...
    16,'FontWeight','bold','ForegroundColor',[0,0,1]);
hclear1 = uicontrol('Style','pushbutton','HorizontalAlignment','center','String','Clear Plot 1',...
    'Position',[140,570,70,30],...
    'Callback',@clearplot1);
hclear2 = uicontrol('Style','pushbutton','HorizontalAlignment','center','String','Clear Plot 2',...
    'Position',[210,570,70,30],...
    'Callback',@clearplot2);

% Save boxes
% hsave1 = uicontrol('Style','pushbutton','HorizontalAlignment','center','String','Save Plot 1','Position',[280,570,70,30],...
%     'Callback',@saveplot1);
% hsave2 = uicontrol('Style','pushbutton','HorizontalAlignment','center','String','Save Plot 2','Position',[350,570,70,30]);
hdataheader = uipanel('Title','Data Sets','FontSize',14,'Position',[0.01,0.01,0.98,0.3]);

hplot1header = uicontrol('Style','text','FontSize',12,'FontWeight','bold','String','Plot 1: ','Position',[15,150,50,20]);
hplot1x = uicontrol('Style','text','FontSize',12,'FontAngle','italic','String','X-axis: ','Position',[17, 120, 50, 20]);
hplot1y = uicontrol('Style','text','FontSize',12,'FontAngle','italic','String','Y-axis: ','Position',[17, 90, 50, 20]);
hplot1y2 = uicontrol('Style','text','FontSize',12,'FontAngle','italic','String','2nd axis: ','Position',[240, 90, 60, 20]);

hplot2header = uicontrol('Style','text','FontSize',12,'FontWeight','bold','String','Plot 2: ','Position',[490,150,50,20]);
hplot2x = uicontrol('Style','text','FontSize',12,'FontAngle','italic','String','X-axis: ','Position',[492, 120, 50, 20]);
hplot2y = uicontrol('Style','text','FontSize',12,'FontAngle','italic','String','Y-axis: ','Position',[492, 90, 50, 20]);
hplot2y2 = uicontrol('Style','text','FontSize',12,'FontAngle','italic','String','2nd axis: ','Position',[715, 90, 60, 20]);

% Pop up menu - data set
DirEntries1 = dir(strcat(Path,Folder1,Tests));
DirEntries2 = dir(strcat(Path,Folder2,Tests));
D1 = dir(strcat(Path,Folder1));
D2 = dir(strcat(Path,Folder2));
num_files1 = length(D1(not([D1.isdir])))-1;
num_files2 = length(D2(not([D2.isdir])))-1;

hpopup_1_x = uicontrol('Style','popupmenu','String',{' ','All',DirEntries1.name},'Position',[70,145,415,25],'Callback',@popupmenu1_Callback_x);
hpopup_2_x = uicontrol('Style','popupmenu','String',{' ','All',DirEntries2.name},'Position',[545,145,415,25],'Callback',@popupmenu2_Callback_x);

hpopup_1_x_sub = uicontrol('Style','popupmenu','String',{' ','Iteration number','Core flowrate [kg/s]',...
    'Bypass flowrate [kg/s]','DHX shell flowrate [kg/s]',...
    'DHX tube flowrate [kg/s]','Core inlet temp [K]','Core outlet temp [K]','DHX shell inlet temp [K]',...
    'DHX shell outlet temp [K]',...
    'DHX tube inlet temp [K]','DHX tube outlet temp [K]','TCHX inlet temp [K]','TCHX outlet temp [K]',...
    'Core loss coefficient','Bypass loss coefficient','DHX shell loss coefficient','DHX tube loss coefficient',...
    'TCHX heat transfer length'},'Position',[70,115,175,25],...
    'Callback',@popupmenu1_Callback_x_sub);
hpopup_1_y_sub = uicontrol('Style','popupmenu','String',{' ','Iteration number','Core flowrate [kg/s]','Bypass flowrate [kg/s]','DHX shell flowrate [kg/s]',...
    'DHX tube flowrate [kg/s]','Core inlet temp [K]','Core outlet temp [K]','DHX shell inlet temp [K]','DHX shell outlet temp [K]',...
    'DHX tube inlet temp [K]','DHX tube outlet temp [K]','TCHX inlet temp [K]','TCHX outlet temp [K]',...
    'Core loss coefficient','Bypass loss coefficient','DHX shell loss coefficient','DHX tube loss coefficient','TCHX heat transfer length'},'Position',[70,85,175,25],...
    'Callback',@popupmenu1_Callback_y_sub);
hpopup_1_y_sub_2nd = uicontrol('Style','popupmenu','String',{'None','Iteration number','Core flowrate [kg/s]','Bypass flowrate [kg/s]','DHX shell flowrate [kg/s]',...
    'DHX tube flowrate [kg/s]','Core inlet temp [K]','Core outlet temp [K]','DHX shell inlet temp [K]','DHX shell outlet temp [K]',...
    'DHX tube inlet temp [K]','DHX tube outlet temp [K]','TCHX inlet temp [K]','TCHX outlet temp [K]',...
    'Core loss coefficient','Bypass loss coefficient','DHX shell loss coefficient','DHX tube loss coefficient','TCHX heat transfer length'},'Position',[300,85,175,25],...
    'Callback',@popupmenu1_Callback_y_sub_2nd);

hpopup_2_x_sub = uicontrol('Style','popupmenu','String',{' ','Iteration number','Core flowrate [kg/s]','Bypass flowrate [kg/s]','DHX shell flowrate [kg/s]',...
    'DHX tube flowrate [kg/s]','Core inlet temp [K]','Core outlet temp [K]','DHX shell inlet temp [K]','DHX shell outlet temp [K]',...
    'DHX tube inlet temp [K]','DHX tube outlet temp [K]','TCHX inlet temp [K]','TCHX outlet temp [K]',...
    'Core loss coefficient','Bypass loss coefficient','DHX shell loss coefficient','DHX tube loss coefficient','TCHX heat transfer length'},'Position',[545,115,175,25],...
    'Callback',@popupmenu2_Callback_x_sub);
hpopup_2_y_sub = uicontrol('Style','popupmenu','String',{' ','Iteration number','Core flowrate [kg/s]','Bypass flowrate [kg/s]','DHX shell flowrate [kg/s]',...
    'DHX tube flowrate [kg/s]','Core inlet temp [K]','Core outlet temp [K]','DHX shell inlet temp [K]','DHX shell outlet temp [K]',...
    'DHX tube inlet temp [K]','DHX tube outlet temp [K]','TCHX inlet temp [K]','TCHX outlet temp [K]',...
    'Core loss coefficient','Bypass loss coefficient','DHX shell loss coefficient','DHX tube loss coefficient','TCHX heat transfer length'},'Position',[545,85,175,25],...
    'Callback',@popupmenu2_Callback_y_sub);
hpopup_2_y_sub_2nd = uicontrol('Style','popupmenu','String',{'None','Iteration number','Core flowrate [kg/s]','Bypass flowrate [kg/s]','DHX shell flowrate [kg/s]',...
    'DHX tube flowrate [kg/s]','Core inlet temp [K]','Core outlet temp [K]','DHX shell inlet temp [K]','DHX shell outlet temp [K]',...
    'DHX tube inlet temp [K]','DHX tube outlet temp [K]','TCHX inlet temp [K]','TCHX outlet temp [K]',...
    'Core loss coefficient','Bypass loss coefficient','DHX shell loss coefficient','DHX tube loss coefficient','TCHX heat transfer length'},'Position',[775,85,175,25],...
    'Callback',@popupmenu2_Callback_y_sub_2nd);


hPlot1 = axes('Units', 'normalized','HandleVisibility','callback','Position',[0.05 0.4 0.4 0.5]);
hPlot2 = axes('Units', 'normalized','HandleVisibility','callback','Position',[0.55 0.4 0.4 0.5]);



% Insert short descriptions about each Data folder. 
switch Folder1
    case 'Iterating4_better_guesses/'
        description1 = 'Iterations beginning with more educated guesses (random number generator) for the magnitudes of the loss coefficients. Core began with 30-50, Bypass with 30,000-35,000, DHX shell with 10,000-20,000, and DHX tube with 1-10. These choices were based on iterations with randomly generated coefficients from 1-100.';
    case 'Iterating4/'
        description1 = 'Loss coefficients arbitrarily all set as random numbers between 0 and 100.';
    case 'Iterating_Area/'
        description1 = 'Iteratins are run with more educated guesses (core from 30-50, bypass set at 40,000, DHX shell from 10,000-20,000, and DHX tube from 0-1). The heat transfer length of the TCHX is updated, but not inserted into new files. This investigation is looking to see if the calculated areas are too small (thermodynamic property errors).';
    case 'Iterating_Prototype/'
        description1 = 'Beginning from the same ranges for loss coefficients, do the inputs all converge to the same transient behavior (when non-dimensionalized)?';
    case 'Iterating_LongTerm/'
        description1 = 'Beginning with random coefficients in the updated ranges, the maximum number of iterations is set to 50 with tighter convergence criteria to see if the cases converge to one solution.';
    otherwise
        description1 = ' ';
end
hdescription1 = uicontrol('Style','text','Position',[30,10,425,55],'String',description1,'HorizontalAlignment','left');

switch Folder2
    case 'Iterating4_better_guesses/'
        description2 = 'Iterations beginning with more educated guesses (random number generator) for the magnitudes of the loss coefficients. Core began with 30-50, Bypass with 30,000-35,000, DHX shell with 10,000-20,000, and DHX tube with 1-10. These choices were based on iterations with randomly generated coefficients from 1-100.';    case 'Iterating4/'
    case 'Iterating4/'
        description2 = 'Loss coefficients arbitrarily all set as random numbers between 0 and 100.';
    case 'Iterating_Area_Modified/'
        description2 = 'First implementation of the extra TCHX heat transfer area iteration.';
    case 'Iterating_Prototype/'
        description1 = 'Beginning from the same ranges for loss coefficients, do the inputs all converge to the same transient behavior (when non-dimensionalized)?';
    case 'Iterating_LongTerm/'
        description2 = 'Beginning with random coefficients in the updated ranges, the maximum number of iterations is set to 50 with tighter convergence criteria to see if the cases converge to one solution.';
    
    otherwise
        description2 = ' ';
end
hdescription2 = uicontrol('Style','text','Position',[505,10,425,55],'String',description2,'HorizontalAlignment','left');

% hides legend
hlegendhide1 = uicontrol('Style','pushbutton','String','Hide/Show Legend 1',...
                  'Position',[280,570,120,30],...
                  'HandleVisibility','off','Callback',@bselection1);

hlegendhide2 = uicontrol('Style','pushbutton','String','Hide/Show Legend 2',...
                  'Position',[400,570,120,30],...
                  'HandleVisibility','off','Callback',@bselection2);


%align([hsurf,hmesh,hcontour,htext,hpopup],'Center','None');
f.Visible = 'on';

global plot1_data;

global plot1_x;
plot1_x = ' ';
global plot1_x_dataname;

global plot1_y;
plot1_y = ' ';
global plot1_y_dataname;

global plot1_y_2nd;
plot1_y_2nd = 1;
global plot1_y_dataname_2nd;
plot1_y_dataname_2nd = 'None';

global hleg1;
global hleg2;

%%%
global plot2_data;

global plot2_x;
plot2_x = ' ';
global plot2_x_dataname;

global plot2_y;
plot2_y = ' ';
global plot2_y_dataname;

global plot2_y_2nd;
plot2_y_2nd = 1;
global plot2_y_dataname_2nd;
plot2_y_dataname_2nd = 'None';

global legendflag1;
legendflag1 = 'hide';
global legendflag2;
legendflag2 = 'hide';

function bselection1(source,callbackdata)
    if legendflag1 == 'show'
        set(hleg1,'visible','on');
        legendflag1 = 'hide';
    else
        set(hleg1, 'visible','off');
        legendflag1 = 'show';
    end
end

function bselection2(source,callbackdata)
    if legendflag2 == 'show'
        set(hleg2,'visible','on');
        legendflag2 = 'hide';
    else
        set(hleg2, 'visible','off');
        legendflag2 = 'show';
    end
end

% clears plots
function clearplot1(hObject, eventdata, handles)
    plot1_data = ' ';
    plot1_x = ' ';
    plot1_y = ' ';
    plot1_x_dataname = ' ';
    plot1_y_dataname = ' ';
    plot1_y_2nd = 1;
    plot1_y_dataname_2nd = 'None';
    cla (hPlot1, 'reset')
    set(hpopup_1_x_sub,'Value',1)
    set(hpopup_1_y_sub,'Value',1)
    set(hpopup_1_y_sub_2nd,'Value',1)
    set(hpopup_1_x,'Value',1)
end

function clearplot2(hObject, eventdata, handles)
    plot2_data = ' ';
    plot2_x = ' ';
    plot2_y = ' ';
    plot2_x_dataname = ' ';
    plot2_y_dataname = ' ';
    plot2_y_2nd = 1;
    plot2_y_dataname_2nd = 'None';
    cla (hPlot2, 'reset')
    set(hpopup_2_x_sub,'Value',1)
    set(hpopup_2_y_sub,'Value',1)
    set(hpopup_2_y_sub_2nd,'Value',1)
    set(hpopup_2_x,'Value',1)
end

% saves plots
function saveplot1(hObject, eventdata, handles)
    %hgsave(hPlot1, '/Users/aprilnovak/Documents/RELAP/Output/fig.fig')
    %saveas(hPlot1, 'exportedfigure1.fig','tiff')
end


% RETURNS THE DATA SETS///////////////////////////////////////////////////
function [mx1] = popupmenu1_Callback_x(hObject, eventdata, handles)
    items = get(hObject,'String');
    index_selected_1x = get(hpopup_1_x,'Value');
    mx1 = items{index_selected_1x};
    plot1_data = mx1;
        if ((strcmp(plot1_x,' ') ~= 1) && (strcmp(plot1_y, ' ') ~= 1))
                Plot(plot1_data, plot1_x, plot1_y, plot1_y_2nd, plot1_x_dataname, plot1_y_dataname, plot1_y_dataname_2nd, hPlot1)
        else         
        end
end
function [mx2] = popupmenu2_Callback_x(hObject, eventdata, handles)
    items = get(hObject,'String');
    index_selected_2x = get(hpopup_2_x,'Value');
    mx2 = items{index_selected_2x};
    plot2_data = mx2;
    if ((strcmp(plot2_x,' ') ~= 1) && (strcmp(plot2_y, ' ') ~= 1))
                Plot(plot2_data, plot2_x, plot2_y, plot2_y_2nd, plot2_x_dataname, plot2_y_dataname, plot2_y_dataname_2nd, hPlot2)
    else         
    end
end


% RETURNS THE SUB-SPECIFICATIONS (1) //////////////////////////////////////
% x-axis
function [row1_x] = popupmenu1_Callback_x_sub(hObject, eventdata, handles)
    items = get(hObject,'String');
    row1_x = get(hpopup_1_x_sub,'Value');
    item_selected_1x = items{row1_x};
    plot1_x = row1_x;
    plot1_x_dataname = item_selected_1x;
    if ((strcmp(plot1_x,' ') ~= 1) && (strcmp(plot1_y, ' ') ~= 1))
                Plot(plot1_data, plot1_x, plot1_y, plot1_y_2nd, plot1_x_dataname, plot1_y_dataname, plot1_y_dataname_2nd, hPlot1)
        else         
        end
end

% primary y-axis
function [row1_y] = popupmenu1_Callback_y_sub(hObject, eventdata, handles)
    items = get(hObject,'String');
    row1_y = get(hpopup_1_y_sub,'Value');
    item_selected_1y = items{row1_y};
    plot1_y = row1_y;
    plot1_y_dataname = item_selected_1y;
    if ((strcmp(plot1_x,' ') ~= 1) && (strcmp(plot1_y, ' ') ~= 1))
                Plot(plot1_data, plot1_x, plot1_y, plot1_y_2nd, plot1_x_dataname, plot1_y_dataname, plot1_y_dataname_2nd, hPlot1)
    else         
    end
end

% secondary y-axis
function [row1_y_2nd] = popupmenu1_Callback_y_sub_2nd(hObject, eventdata, handles)
    items = get(hObject,'String');
    row1_y_2nd = get(hpopup_1_y_sub_2nd,'Value');
    item_selected_1y_2nd = items{row1_y_2nd};
    plot1_y_2nd = row1_y_2nd;
    plot1_y_dataname_2nd = item_selected_1y_2nd;
        if ((strcmp(plot1_x,' ') ~= 1) && (strcmp(plot1_y, ' ') ~= 1))
                Plot(plot1_data, plot1_x, plot1_y, plot1_y_2nd, plot1_x_dataname, plot1_y_dataname, plot1_y_dataname_2nd, hPlot1)
        else         
        end
end









% RETURNS THE SUB-SPECIFICATIONS (2)///////////////////////////////////////
function [row2_x] = popupmenu2_Callback_x_sub(hObject, eventdata, handles)
    items = get(hObject,'String');
    row2_x = get(hpopup_2_x_sub,'Value');
    item_selected_2x = items{row2_x};
    plot2_x = row2_x;
    plot2_x_dataname = item_selected_2x;
    if ((strcmp(plot2_x,' ') ~= 1) && (strcmp(plot2_y, ' ') ~= 1))
                Plot(plot2_data, plot2_x, plot2_y, plot2_y_2nd, plot2_x_dataname, plot2_y_dataname, plot2_y_dataname_2nd, hPlot2)
        else         
        end
end

% primary y-axis
function [row2_y] = popupmenu2_Callback_y_sub(hObject, eventdata, handles)
    items = get(hObject,'String');
    row2_y = get(hpopup_2_y_sub,'Value');
    item_selected_2y = items{row2_y};
    plot2_y = row2_y;
    plot2_y_dataname = item_selected_2y;
    if ((strcmp(plot2_x,' ') ~= 1) && (strcmp(plot2_y, ' ') ~= 1))
                Plot(plot2_data, plot2_x, plot2_y, plot2_y_2nd, plot2_x_dataname, plot2_y_dataname, plot2_y_dataname_2nd, hPlot2)
    else         
    end
end

% secondary y-axis
function [row2_y_2nd] = popupmenu2_Callback_y_sub_2nd(hObject, eventdata, handles)
    items = get(hObject,'String');
    row2_y_2nd = get(hpopup_2_y_sub_2nd,'Value');
    item_selected_2y_2nd = items{row2_y_2nd};
    plot2_y_2nd = row2_y_2nd;
    plot2_y_dataname_2nd = item_selected_2y_2nd;
        if ((strcmp(plot2_x,' ') ~= 1) && (strcmp(plot2_y, ' ') ~= 1))
                Plot(plot2_data, plot2_x, plot2_y, plot2_y_2nd, plot2_x_dataname, plot2_y_dataname, plot2_y_dataname_2nd, hPlot2)
        else         
        end
end
 
  




   
function Plot(filename, xdata1, ydata1, ydata2, xdataname1, ydataname1, ydataname2, whichplot)
    if (strcmp(filename,'All') == 1)
        if (whichplot == hPlot1)
            num_files = num_files1;
        else
            num_files = num_files2;
        end
        
    for index = 1:num_files        
        if (strcmp(ydataname2, 'None') ~= 1) % There is a secondary y-axis 
        else
            if (whichplot == hPlot1)
                filename = D1(index+3).name;
                fname = strcat(Path,Folder1,filename);
            else
                filename = D2(index+3).name;
                fname = strcat(Path,Folder2,filename);
            end
            
            M = csvread(fname);
            A = size(M);
            plot(whichplot, M(xdata1-1,1:(A(2)-1)),M(ydata1-1,1:(A(2)-1)),'*-','DisplayName',filename)
            hold (whichplot,'on')
            %hleg = legend(whichplot,'-DynamicLegend')
        if (whichplot == hPlot1)
            hleg1 = legend(whichplot,'-DynamicLegend')
        else
            hleg2 = legend(whichplot,'-DynamicLegend')
        end
            xlabel(whichplot, xdataname1,'FontSize',14), ylabel(whichplot, ydataname1,'FontSize',14)%, title(whichplot,'All Files')
            grid(whichplot,'on')
        end
    end
hold (whichplot,'off') 
else % user did not select "All"  
            if (whichplot == hPlot1)
                fname = strcat(Path,Folder1,filename);
            else
                fname = strcat(Path,Folder2,filename);
            end
    
    M = csvread(fname);
    A = size(M);

    if (strcmp(ydataname2, 'None') ~= 1) 
        [ax h1 h2] = plotyy(whichplot,M(xdata1-1,1:(A(2)-1)),M(ydata1-1,1:(A(2)-1)), M(xdata1-1,1:(A(2)-1)), M(ydata2-1,1:(A(2)-1)))
        %hleg = legend([h1;h2], ydataname1, ydataname2)
        if (whichplot == hPlot1)
            hleg1 = legend([h1;h2], ydataname1, ydataname2)
        else
            hleg2 = legend([h1;h2], ydataname1, ydataname2)
        end
        xlabel(whichplot, xdataname1,'FontSize',14), ylabel(ax(1), ydataname1), ylabel(ax(2), ydataname2,'FontSize',14)%, title(whichplot,filename)
        set([h1;h2],'Marker','*')
        grid(whichplot,'on')
    else
        plot(whichplot, M(xdata1-1,1:(A(2)-1)),M(ydata1-1,1:(A(2)-1)),'*-')
        if (whichplot == hPlot1)
            hleg1 = legend(whichplot, ydataname1)
        else
            hleg2 = legend(whichplot,ydataname1)
        end
        xlabel(whichplot, xdataname1,'FontSize',14), ylabel(whichplot, ydataname1,'FontSize',14)%, title(whichplot,filename)
        grid(whichplot,'on')
    end
    
end
end










































end

