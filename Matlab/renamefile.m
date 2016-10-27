%%%%%%%%%%%%%%批量修改文件夹名称
% close all;clear all;clc;
% path='G:\100万采样\敦南CIS第四套\value-5\version-4\direction-0\'; %修改一级文件夹名称
% fileDIR=dir(path);  %获取路径信息    %第0层文件夹direction
% filenum=length(fileDIR);   %该文件夹下的子文件夹个数，从3开始  
% for p=3:filenum
%     filename=fileDIR(p).name;  %第p个子文件夹的文件夹名    
%     path1=strcat(path,filename,'\');
%     fileDIR1=dir(strcat(path1,'*')); %第一层文件夹1-50
%     filenum1=length(fileDIR1); 
%     for q=3:filenum1
%         filename1=fileDIR1(q).name;
%         path2=strcat(path1,filename1,'\');
%     DIR=dir(strcat(path2,'*.bmp')); %获取该子文件夹中所有bmp格式的图像
%     len=length(DIR);
%    
%   cd(path2);
%     if len>0
%         for i=0:2:len-1
%             name1=DIR(i+1).name;
%             name2=DIR(i+2).name;
%            movefile(name1,strcat(num2str(i/2),'_down.bmp'));
%            movefile(name2,strcat(num2str(i/2),'_up.bmp'));
%         end
%     end
%     end
% end

% clear all
% clc
% %folder_name=uigetdir;
% folder_name='G:\100万采样\敦南CIS第四套\value-5\version-4\direction-0\';
% % 手动打开要修改名称的文件夹的上一层文件夹
% folder=dir(folder_name);
% oldname=cell(length(folder)-2,1);
% for ii=3:length(folder)
%    oldname{ii-2}=folder(ii).name;
% end
% 
% % 提取出要修改文件夹的名称
% newname=cell(length(oldname),1);
% for ii=1:length(oldname)
%    a=oldname{ii};
%    %newname{ii}=a(2:end);
%    % 新的文件夹名称 
%    movefile([folder_name '\' oldname{ii}],[folder_name '\' num2str(ii)])
%    % 利用movefile函数进行修改
% end


%重命名文件夹名称
clear all
clc
close all;
folder_name='G:\100万采样\5元采样20000张\';
fileDir=dir(folder_name); 
folderNum=length(fileDir); %第一级目录 direction
for p=3:folderNum
    fileName=fileDir(p).name;
    path1=strcat(folder_name,fileName,'\');
    fileDIR1=dir(strcat(path1,'*'));
    
    for ii=3:length(fileDIR1)
        movefile([path1 '\' fileDIR1(ii).name],[path1 '\' num2str(ii-2)])
    end
end

