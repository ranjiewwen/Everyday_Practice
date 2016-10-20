function rename_dir(path, option)  
%Author:shizhixin  
%Email:szhixin@gmail.com  
%Blog:http://blog.csdn.net/shizhixin  
%Date:2012-02-15  
  
%option = 'LAMOST','DR8','SPECIAL'  
%LAMOST:类似spec_release.php@path=%2Fdata1%2Fspectra_v2.3.3%2F20111024%  
% 2FF5902%2Fspec-55859-F5902_sp02-166.fits的文件名，只取后面部分  
% 重命名为spec-55859-F5902_sp02-166.fits  
%DR8: spec-pppp-mmmmm-ffff.fits  
%fits@plateid=278&mjd=51900&fiber=583的文件重命名为spec-0278-51900-0583.fit  
%数字位数不够补零  
%SPECIAL :Spec-2951-54592-433.fit  ---> spec-pppp-mmmmm-ffff.fits  
  
%EX:rename_dir('G:\DR8_data\', 'DR8')  
switch option  
    case 'LAMOST'  
        files = dir([path '*.fits']); %读入后缀为.fits的所有文件  
        n = length(files);           %文件总数  
        for i = 1:n  
            i  
            filename = [path files(i).name];    %文件名，包括路径  
            old_name = files(i).name;           %仅仅包括文件名  
            pos = strfind(old_name, 'spec-');   %找到spec-的位置  
            new_name = old_name(pos:end);       %从spec-开始直到最后所有的字符为新的文件名  
            old_path = strcat(path,old_name);   %获取原来文件名及路径  
            new_path = strcat(path,new_name);   %获取新文件名及路径  
            status = movefile(old_path,new_path); %通过移动文件，重命名文件  
        end  
    case 'DR8'  
        files = dir([path '*']); %读入所有文件  
        n = length(files);           %文件总数  
        for i = 1:n  
            i  
            filename = [path files(i).name];    %文件名，包括路径  
            old_name = files(i).name;           %仅仅包括文件名  
            pos_equal = strfind(old_name, '=');   %找到=的位置   
            pos_and = strfind(old_name, '&');   %找到&的位置  
            if length(pos_equal)~=3  
                continue;  
            end  
            pppp = old_name(pos_equal(1)+1:pos_and(1)-1);  
            pppp = alignbitzero(pppp ,4);  
            mmmmm = old_name(pos_equal(2)+1:pos_and(2)-1);  
            mmmmm = alignbitzero(mmmmm ,5);  
            ffff = old_name(pos_equal(3)+1:end);  
            ffff = alignbitzero(ffff ,4);  
  
            new_name = ['spec-' pppp '-' mmmmm '-' ffff '.fits'];  
            %从spec-开始直到最后所有的字符为新的文件名  
            old_path = strcat(path,old_name);   %获取原来文件名及路径  
            new_path = strcat(path,new_name);   %获取新文件名及路径  
            status = movefile(old_path,new_path); %通过移动文件，重命名文件  
        end  
    case 'SPECIAL'  
        %Spec-2951-54592-433.fit  ---> spec-pppp-mmmmm-ffff.fits  
        files = dir([path '*.fit']); %读入所有文件  
        n = length(files);           %文件总数  
        for i = 1:n  
            i  
            filename = [path files(i).name];    %文件名，包括路径  
            old_name = files(i).name;           %仅仅包括文件名  
            pos_equal = strfind(old_name, '-');   %找到=的位置   
            pos_point = strfind(old_name, '.');   %找到.的位置   
            if length(pos_equal)~=3  
                continue;  
            end  
            pppp = old_name(pos_equal(1)+1:pos_equal(2)-1);  
            pppp = alignbitzero(pppp ,4);  
            mmmmm = old_name(pos_equal(2)+1:pos_equal(3)-1);  
            mmmmm = alignbitzero(mmmmm ,5);  
            ffff = old_name(pos_equal(3)+1:pos_point-1);  
            ffff = alignbitzero(ffff ,4);  
  
            new_name = ['spec-' pppp '-' mmmmm '-' ffff '.fits'];  
            %从spec-开始直到最后所有的字符为新的文件名  
            old_path = strcat(path,old_name);   %获取原来文件名及路径  
            new_path = strcat(path,new_name);   %获取新文件名及路径  
            status = movefile(old_path,new_path); %通过移动文件，重命名文件  
        end  
  
    otherwise  
        disp 'option error!'  
end  
end  
  
%old_num这个数如果不足bit位，就补零,如alignbitzero(234,4)返回结果是0234  
function new_num = alignbitzero(old_num, bit)  
len = length(old_num);  
if len > bit  
    disp 'error';  
end  
for i=1:bit-len  
    old_num=strcat('0', old_num);  
end  
new_num = old_num;  
end  
