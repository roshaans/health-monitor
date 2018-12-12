clear all
close all
load('newData.mat', 'data1')
load('newData.mat', 'data2')
ID = data1;
BPM = data2;
%% Structure
s = struct('ID',{},'BPM',{});
% s{1}.ID = BPM;

for i = 1:length(ID)
    s{1}.BPM{i} = BPM(ID==i);
end


figure;
plot(1:length(ID),s{i}.BPM{2})
title("ID VS BPM")
xlabel("ID");
ylabel("BPM");

