
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% our first program
% --- awesome!
% by: Takis Zourntos
% date: 09-10-2019
%
%%
clear;  % clear memory
clc;    % clear console
format SHORTENG;
disp('program complete!');

%% 
%  read audio files 
%
ffile = 'human_voice_shh_female_001.mp3';
%mfile = 'human_voice_shh_male_001.mp3';
mfile='zapsplat_human_voice_male_in_peril_says_no_please_13185.mp3';
[yf, FSf]=audioread(ffile);
[ym, FSm]=audioread(mfile);
ym = decimate(ym, 4);
ym = ym';

%% 
%  manipulate data
%
% yf2 = rand(max(size(yf)))*yf;
% ym2 = rand(max(size(ym)))*ym;
Arf = eye(max(size(yf)));
Mrf = flip(Arf);
yf2 = Mrf*yf;

Arm = eye(max(size(ym)));
Mrm = flip(Arm);
ym2 = Mrm*ym;
ym2 = interp(ym2, 4);
ym2 = ym2';

%%
%  write audio files
%
ffile2 = 'human_voice_female_changed.ogg';
mfile2 = 'human_voice_male_changed.ogg';
!rm human_voice_female_changed.ogg
!rm human_voice_male_changed.ogg
audiowrite(ffile2,yf2,FSf);
audiowrite(mfile2,ym2,FSm);

