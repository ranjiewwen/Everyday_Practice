
% %%%%%%%%%%%%%%一级目录下删除raw文件   \文件
% close all;
% clear all;
% clc;
% path='G:\48_7_20161023\1999版\value-10\direction-0\';
% fileDIR=dir(strcat(path,'*.raw'));  %获取路径信息
% filenum=length(fileDIR);   %该文件夹下的子文件夹个数，从3开始
% cd(path);
% if filenum>0
%     for i=1:filenum
%         rawname=fileDIR(i).name;
%         rawname=strcat(path,rawname);
%         delete(rawname);
%     end
% end

%%%%%%%%%%%%%%二级目录下删除raw文件    \文件夹\文件
close all;
clear all;
clc;
path='G:\48_7_20161023\2015版\AK47DL\value-100\';
fileDIR=dir(path);  %获取路径信息
filenum=length(fileDIR);   %该文件夹下的子文件夹个数，从3开始
for p=3:filenum %
    filename=fileDIR(p).name;  %第p个子文件夹的文件夹名
    path1=strcat(path,filename,'\');
    fileDIR1=dir(strcat(path1,'*.raw'));
    filenum1=length(fileDIR1);
    
    cd(path1);
    if filenum1>0
        for i=1:filenum1
            rawname=fileDIR1(i).name;
            rawname=strcat(path1,rawname);
            delete(rawname);
        end
    end
end

% %%%%%%%%%%%%%%三级目录下删除raw文件    \文件夹\文件夹\文件
% close all;
% clear all;
% clc;
% path='E:\中钞信达采样\中钞信达采样\05-10\';
% fileDIR=dir(path);  %获取路径信息
% filenum=length(fileDIR);   %该文件夹下的子文件夹个数，从3开始
% for p=3:filenum %
%     filename=fileDIR(p).name;  %第p个子文件夹的文件夹名
%     path1=strcat(path,filename,'\');
%     fileDIR1=dir(strcat(path1,'*'));
%     filenum1=length(fileDIR1);
%     for q=3:filenum1
%         filename1=fileDIR1(q).name;
%         path2=strcat(path1,filename1,'\');
%     DIR=dir(strcat(path2,'*.raw')); %获取该子文件夹中所有raw格式的图像
%     len=length(DIR);
%
%   cd(path2);
%     if len>0
%         for i=1:len
%             rawname=DIR(i).name;
%             rawname=strcat(path2,rawname);
%             delete(rawname);
%         end
%     end
%     end
% end
