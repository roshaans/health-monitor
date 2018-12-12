clear all
close all
load('pulseData.mat', 'data1')
load('pulseData.mat', 'data2')
ID = data1;
BPM = data2;
%% Structure
s = struct('ID',{},'BPM',{});
% s{1}.ID = BPM;

for i = 1:length(ID)
    s{1}.BPM{i} = BPM(ID==i);
end


figure;
plot(1:length(s{1}.BPM{2}),s{1}.BPM{2})
title("ID VS BPM")
xlabel("Day");
ylabel("BPM");
title('Data for ID#2')

