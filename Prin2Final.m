%% datalogRetrieveDataOffCardDirectly
% Author: Daniel Moller
% Program: datalogRetrieveDataOffCardDirectly.m              Version:    1.0
% Original Date: 9/2018
%
% Function calls:
%   none
%
% Function called by:
%   none
%
% Revision History (include version, programmer, date and description)
% =========================================================================
%
% Notes
% ********************
%  This program acquires data from the uSD card when connected directly to
%  the USB port using a reader.
% *************************************************************************

%% clear the workspace
clear all
close all

%% get the data
[filename,pathname]=uigetfile('.txt','Choose the data to import');
data=dlmread([pathname filename])';

%% put the data in individual variables
[nrows ncols] = size(data);
if nrows==1
    data1 = data(1,:);
elseif nrows==2
    data1 = data(1,:);
    data2 = data(2,:);
elseif nrows==3
    data1 = data(1,:);
    data2 = data(2,:);
    data3 = data(3,:);
else
    error('incorrect file input');
end
    
%% Save variables for later
str = input(['<ENTER> to abort save\n' '   OR\n' ...
    'Enter preferred filename (with no spaces)\n:'],'s');
if ~isempty(str)
    if nrows==1
        save(str,'data1')
    elseif nrows==2
        save(str,'data1','data2')
    elseif nrows==3
        save(str,'data1','data2','data3')
    end
end
   
    
    

