
% %%%%%%%%%%%%%%批量修改文件名一级文件夹   \路径下直接为文件
% close all;clear all;clc;
% path='G:\100万采样\YC_AK采样\value-100\version-15\direction-1\新建文件夹\';
% fileDIR=dir(strcat(path,'*.txt'));  %获取路径信息    %第0层文件夹direction
% filenum=length(fileDIR);   %该文件夹下的子文件夹个数，从3开始
% cd(path);
% for i=0:2:filenum-1
%     name1=fileDIR(i+1).name;
%     name2=fileDIR(i+2).name;
%     movefile(name1,strcat(num2str(i/2),'_down.bmp'));
%     movefile(name2,strcat(num2str(i/2),'_up.bmp'));
% end

%%%%%%%%%%%%%%批量修改文件名二级文件夹   \路径下文件夹\文件
close all;clear all;clc;
path='G:\48_7_20161023\2015版\AK47DL\value-100\';
fileDIR1=dir(strcat(path,'*')); %第一层文件夹direction-
filenum1=length(fileDIR1);
for q=3:filenum1
    filename1=fileDIR1(q).name;
    path2=strcat(path,filename1,'\');
    DIR=dir(strcat(path2,'*.bmp')); %获取该子文件夹中所有bmp格式的图像,从0开始
    len=length(DIR);
    
    cd(path2);
    if len>0
        for i=0:2:len-1
            if ((i+2)<=len & (i+1)<=len)
                name1=DIR(i+1).name;
                name2=DIR(i+2).name;
                movefile(name1,strcat(num2str(i/2),'_down.bmp'));
                movefile(name2,strcat(num2str(i/2),'_up.bmp'));
            end
        end
    end
    %  end
end

% close all;clear all;clc;
% path='G:\100万采样\YC_AK采样\value-10\direction-0\1\';
% fileDIR=dir(strcat(path,'*.bmp'));  %获取路径信息    %第0层文件夹direction
% len=length(fileDIR);   %该文件夹下的子文件夹个数，从3开始
% cd(path);
% if len>0
%     for i=1:len/2
%         oldname=strcat('Image_Y_all',num2str(i-1),'.bmp');
%         newname=strcat(num2str(i-1),'_up.bmp');
%         movefile(oldname,newname);
%         oldname=strcat('Image_U_all',num2str(i-1),'.bmp');
%         newname=strcat(num2str(i-1),'_down.bmp');
%         movefile(oldname,newname);
%     end
% end



% %%%%%%%%%%%%%%批量修改文件名三级文件夹   \路径下文件夹\文件夹\文件
% close all;clear all;clc;
% path='G:\100万采样\5元采样20000张\';
% fileDIR=dir(path);  %获取路径信息    %第0层文件夹direction
% filenum=length(fileDIR);   %该文件夹下的子文件夹个数，从3开始
% for p=5:filenum  %
%     filename=fileDIR(p).name;  %第p个子文件夹的文件夹名
%     path1=strcat(path,filename,'\');
%     fileDIR1=dir(strcat(path1,'*')); %第一层文件夹1-50
%     filenum1=length(fileDIR1);
%     for q=3:filenum1
%         filename1=fileDIR1(q).name;
%         path2=strcat(path1,filename1,'\');
%         DIR=dir(strcat(path2,'*.bmp')); %获取该子文件夹中所有bmp格式的图像,从0开始
%         len=length(DIR);
%         
%         cd(path2);
%         if len>0
%             for i=0:2:len-1
%                 if ((i+2)<=len & (i+1)<=len)
%                     name1=DIR(i+1).name;
%                     name2=DIR(i+2).name;
%                     movefile(name1,strcat(num2str(i/2),'_down.bmp'));
%                     movefile(name2,strcat(num2str(i/2),'_up.bmp'));
%                 end
%             end
%         end
%     end
% end