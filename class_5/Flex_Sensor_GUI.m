function varargout = Class_5_FSR_GUI(varargin)
% CLASS_5_FSR_GUI MATLAB code for Class_5_FSR_GUI.fig
%      CLASS_5_FSR_GUI, by itself, creates a new CLASS_5_FSR_GUI or raises the existing
%      singleton*.
%
%      H = CLASS_5_FSR_GUI returns the handle to a new CLASS_5_FSR_GUI or the handle to
%      the existing singleton*.
%
%      CLASS_5_FSR_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in CLASS_5_FSR_GUI.M with the given input arguments.
%
%      CLASS_5_FSR_GUI('Property','Value',...) creates a new CLASS_5_FSR_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Class_5_FSR_GUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Class_5_FSR_GUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Class_5_FSR_GUI

% Last Modified by GUIDE v2.5 15-Sep-2013 17:57:30

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Class_5_FSR_GUI_OpeningFcn, ...
                   'gui_OutputFcn',  @Class_5_FSR_GUI_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before Class_5_FSR_GUI is made visible.
function Class_5_FSR_GUI_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Class_5_FSR_GUI (see VARARGIN)

% Choose default command line output for Class_5_FSR_GUI
handles.output = hObject;

% Clear all previously created objects
delete(instrfindall);

% Create initial plot
plot(handles.axesHandle,0,0,'MarkerFaceColor','auto','MarkerEdgeColor',[0 1 0],'Marker','.','LineWidth',1,'Color',[0 1 0]);

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Class_5_FSR_GUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Class_5_FSR_GUI_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in startButton.
function startButton_Callback(hObject, eventdata, handles)
% hObject    handle to startButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

button_state = get(hObject,'Value');
if button_state == get(hObject,'Max')
	% Toggle button is pressed
    
    % Change the string on the button
    set(hObject,'String','Stop');
    
    % Check if the object is already created
    if ~exist('arduinoObject','var')
        % Create an object to connect to Arduino board
        serialPortString = get(handles.serialPortEdit,'string');
        arduinoObject = arduino(serialPortString);
        
        % Reset data array
        clear data;
        % Reset initial plot
        plot(handles.axesHandle,0,0,'MarkerFaceColor','auto','MarkerEdgeColor',[0 1 0],'Marker','.','LineWidth',1,'Color',[0 1 0]);

    end
    
elseif button_state == get(hObject,'Min')
	% Toggle button is not pressed
    
    % Change the string on the button
    set(hObject,'String','Start');
    
    % Clear the object created
    clear a;
end

tic;
iLoop = 1;
while isequal(get(hObject,'Value'),get(hObject,'Max'))
    data(iLoop) = analogRead(arduinoObject,0);  %#ok<*AGROW>
    timeStamp(iLoop) = toc; 
    plot(handles.axesHandle,timeStamp,data,'MarkerFaceColor','auto','MarkerEdgeColor',[0 1 0],'Marker','.','LineWidth',1,'Color',[0 1 0]);
    iLoop = iLoop+1;
    drawnow;
end



function serialPortEdit_Callback(hObject, eventdata, handles)
% hObject    handle to serialPortEdit (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of serialPortEdit as text
%        str2double(get(hObject,'String')) returns contents of serialPortEdit as a double


% --- Executes during object creation, after setting all properties.
function serialPortEdit_CreateFcn(hObject, eventdata, handles)
% hObject    handle to serialPortEdit (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
