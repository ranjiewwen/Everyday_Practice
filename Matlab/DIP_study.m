% clear all
% clc;
% B=imread('C:\Users\ranji\Desktop\test.bmp');
% A=rgb2gray(B);
% A2=dct2(A);
% A3=fft2(A);
% subplot(2,2,1);imshow(B);
% subplot(2,2,2);imshow(A);
% subplot(2,2,3);imshow(A2);
% subplot(2,2,4);imshow(A3);
% %tab键智能提示

% function test=subim(f,m,n,rx,ry)
% test=zeros(m,n);
% rowhigh=rx+m-1;
% colhigh=ry+n-1;
% xcount=0;
% for r=rx:rowhigh
%     xcount=xcount+1;
%     ycount=0;
%     for c=ry:colhigh
%         ycount=ycount+1;
%         test(xcount,ycount)=f(r,c);
%     end
% end

%对数变换
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% g=imadjust(A,[0 1],[1 0]);
% gs=im2uint8(mat2gray(A));
% gg=im2uint8(mat2gray(log(1+double(A))));
% %imshow(A),figure,imshow(g),figure,imshow(gs)
% subplot(2,2,1);imshow(A)
% subplot(2,2,2);imshow(g)
% subplot(2,2,3);imshow(gs)
% subplot(2,2,4);imshow(gg);

%%函数intrans.m里面有各种空间变换效果

%直方图
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% h=imhist(B);
% h1=h(1:10:256);
% horz=1:10:256;
% %bar(horz,h1);
% %stem(horz,h1,'fill');
% plot(h);
% axis([0 255 0 1500]);
% set(gca,'xtick',0:50:255);
% set(gca,'ytick',0:200:1500);

%%直方图均衡化
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% imshow(B);
% figure , imhist(B);
% ylim('auto')
% g=histeq(B,256);
% figure,imshow(g)
% figure,imhist(g)
% ylim('auto')
% %imwrite(g,'save.bmp'); 
% 
% hnorm=imhist(B)./numel(B);
% cdf=cumsum(hnorm);
% x=linspace(0,1,256);
% plot(x,cdf);
% axis([0 1 0 1]);
% set(gca,'xtick',0:.2:1);
% set(gca,'ytick',0:.2:1);
% xlabel('Input intensity values','fontsize',9);
% ylabel('Output intensity values','fontsize',9);
% text(0.18,0.5,'Transformation function','fontsize',9);

%%直方图匹配,多峰高斯函数，manualhist.m文件

% %%线性空间滤波
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B1=A(:,:,1);
% imshow(B1);
% B=B1(10:180,50:220);
% B=double(B); %不转换就是空白的
% w=ones(17);
% gd=imfilter(B,w);
% figure, imshow(gd,[ ]);  %模糊效果明显
% 
% gr=imfilter(B,w,'replicate');  %用滤波器对图像进行卷积操作会产生模糊效果
% figure, imshow(gr,[]); 
% 
% gs=imfilter(B,w,'symmetric');
% figure, imshow(gs,[]);
% 
% gc=imfilter(B,w,'circular');
% figure,imshow(gc,[]);
% 
% C=im2double(B);
% gDr=imfilter(C,w,'replicate');
% figure, imshow(gDr,[]);

%非线性空间滤波 colfilt.m文件

% %%标准空间滤波器
% %%线性空间滤波
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% imshow(B);
% w=fspecial('laplacian',0);  %generate 滤波掩模
% w1=[1,1,1;1,-8,1;1,1,1];  %手工指定滤波器
% g1=imfilter(B,w,'replicate');
% figure, imshow(g1,[]);
% B1=im2double(B);
% g2=imfilter(B1,w,'replicate');
% g3=imfilter(B1,w1,'replicate');
% figure ,imshow(g2,[])  %默认是显示0~255,用了[]就显示min(A)~max(A),imshow(A,[])后会从最小到最大拉伸显示
% figure ,imshow(g3,[]);
% g=B1-g2;
% gg=B1-g3;
% figure,imshow(g); %有效果的,用laplas增强图像
% figure,imshow(gg);title('w1滤波器');%图像更清楚  

% %%非线性空间滤波
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% imshow(B);
% fn=imnoise(B,'salt & pepper',0.2);
% gm=medfilt2(fn);  %中值滤波去噪
% figure,imshow(gm);
% gms=medfilt2(fn,'symmetric'); %symmetric
% figure, imshow(gms);

% %%计算并可视化二维DFT
% A=imread(' C:\Users\ranji\Desktop\test.jpg');  %或者使用save.bmp实验
% B=A(:,:,1);
% B=B(50:700,150:950);
% imshow(B);
% F=fft2(B);
% S=abs(F);
% figure,imshow(S,[]);% 白点在左上角
% Fc=fftshift(F);
% figure, imshow(abs(Fc),[]); %白点在中心点
% S2=log(1+abs(Fc));
% figure,imshow(S2,[]);

% %%eg4.1不填充进行滤波
% close all;
% clear all;
% clc;
% A=imread(' C:\Users\ranji\Desktop\test.jpg');  %或者使用save.bmp实验
% B=A(:,:,1);
% B=B(50:700,150:950);
% imshow(B);
% [M,N]=size(B);
% F=fft2(B);
% sig=10;
% H=lpfilter('gaussian',M,N,sig);
% G=H.*F;
% g=real(ifft2(G));
% figure,imshow(g,[]);   %图像模糊
% 
% %%使用填充进行滤波 频域滤波的基本步骤：
% PQ=paddedsize(size(B));
% Fp=fft2(B,PQ(1),PQ(2)); %Compute the FFT with padding
% Hp=lpfilter('gaussian',PQ(1),PQ(2),2*sig);
% Gp=Hp.*Fp;  %频域数组相乘
% gp=real(ifft2(Gp));
% gpc=gp(1:size(B,1),1:size(B,2));
% figure, imshow(gpc,[]);
% %空间滤波效果
% h=fspecial('gaussian',15,7);
% gs=imfilter(B,h);
% figure,imshow(gs);


% %%4.4空间滤波器和频率滤波器的比较
% close all;
% clear all;
% clc;
% A=imread(' C:\Users\ranji\Desktop\test.jpg');  %或者使用save.bmp实验
% B=A(:,:,1);
% B=B(101:700,151:750);
% imshow(B);
% imwrite(B,'test1.bmp');
% F=fft2(B);
% ss=abs(F);%计算每一个元素的幅度
% S=fftshift(log(1+abs(F)));
% S=gscale(S);
% figure,imshow(S);
% h=fspecial('sobel')';
% figure,freqz2(h);
% PQ=paddedsize(size(B));
% figure,freqz2(h,PQ(1),PQ(2));
% H=freqz2(h,PQ(1),PQ(2));
% H1=ifftshift(H);
% figure,imshow(abs(H),[]);
% figure,imshow(abs(H1),[]);
% 
% %空间域和频率域
% gs=imfilter(double(B),h);
% gf=dftfilt(B,H1);
% figure,imshow(gs,[]); %有负值
% figure,imshow(gf,[]);
% figure,imshow(abs(gs),[]);
% figure,imshow(abs(gf),[]);
% %创建阈值二值图像
% figure,imshow(abs(gs)>0.2*abs(max(gs(:))));
% figure,imshow(abs(gf)>0.2*abs(max(gf(:))));

% %%4.5在频域中直接生成滤波器
% A=imread(' C:\Users\ranji\Desktop\test1.bmp');  
% imshow(A);
% PQ=paddedsize(size(A)); %执行时要打开相应放入目录文件
% [U,V]=dftuv(PQ(1),PQ(2));
% D0=0.05*PQ(2);
% F=fft2(A,PQ(1),PQ(2));
% H=exp(-(U.^2+V.^2)/(2*(D0^2)));  %高斯低通滤波器
% g=dftfilt(A,H);
% figure,imshow(fftshift(H),[]); %以图像的形式显示的高斯低通滤波器
% figure,imshow(log(1+abs(fftshift(F))),[]);
% figure,imshow(g,[]); %图像变模糊

% %线框图和表面图
% H=fftshift(lpfilter('gaussian',500,500,50));
% mesh(H(1:10:500,1:10:500));
% axis([0 50 0 50 0 1]);
% colormap([0 0 0]);
% axis off
% grid off
% view(-25,30)
% %view(-25,0)
% surf(H)
% colormap(gray)

%[Y,X]=meshgrid(-2:0.1:2,-2:0.1:2);
%Z=X.*exp(-X.^2+Y.^2);
%mesh(Z)
%surf(Z)
%meshgrid(Z);

%%高通滤波器增强
% close all
% clc;
% H=fftshift(hpfilter('ideal',500,500,50));
% mesh(H(1:10:500,1:10:500)); %线框图
% %surf(H); %表面图
% axis([0 50 0 50 0 1]);
% colormap([0 0 0]); 
% axis off 
% grid off
% figure,imshow(H,[]);
% A=imread(' C:\Users\ranji\Desktop\test1.bmp');
% PQ=paddedsize(size(A));
% D0=0.05*PQ(1);
% H=hpfilter('gaussian',PQ(1),PQ(2),D0);
% g=dftfilt(A,H);
% figure,imshow(g,[])

% %%高频强调滤波
% close all
% clear all
% clc;
% A=imread(' C:\Users\ranji\Desktop\test1.bmp');
% imshow(A);
% PQ=paddedsize(size(A));
% D0=0.05*PQ(1);
% HBW=hpfilter('btw',PQ(1),PQ(2),D0);
% H=0.5+2*HBW;
% gbw=dftfilt(A,HBW);
% figure,imshow(gbw);  %加[]有区别
% gbw=gscale(gbw);
% figure,imshow(gbw);
% ghf=dftfilt(A,H);
% figure,imshow(ghf,[])
% ghf=gscale(ghf);
% figure,imshow(ghf,[])
% ghe=histeq(ghf,256);
% figure,imshow(ghe,[]);

% %%估计噪声参数
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% imshow(B);
% fn=imnoise(B,'salt & pepper',0.2);
% C=fn+B;
% figure,imshow(C);
% [b,c,r]=roipoly(C); %%等待选定区域
% [p,npix]=histroi(C,c,r);
% figure,bar(p,1)
% 
% [v,unv]=statmoments(p,2)  %覆盖区域均值和方差 
% X=imnoise2('gaussian',npix,1,147,20);
% figure,hist(X,130);
% axis([0 300 ])


% %%函数spfilt的==使用仅有噪声的复原
% A=imread(' C:\Users\ranji\Desktop\SAVE.bmp');
% B=A(:,:,1);
% imshow(B);
% fn=imnoise(B,'salt & pepper',0.2);
% C=fn+B;
% figure,imshow(C);
% %胡椒噪声污染
% [M,N]=size(B);
% R=imnoise2('salt & pepper', M , N , 0.1 , 0);
% c=find(R==0);
% gp=B;
% gp(c)=0;
% figure,imshow(gp);
% %过滤胡椒噪声,采用Q为正值的反调和滤波器
% fp=spfilt(gp,'chmean',3,3,1.5);
% figure,imshow(fp);
% %max
% fpmax=spfilt(gp,'max',3,3);
% figure,imshow(fpmax)
% 
% %盐椒噪声污染
% R1=imnoise2('salt & pepper',M,N,0,0.1);
% c=find(R==1);
% gs=B;
% gs(c)=255;
% figure,imshow(gs);
% %盐椒噪声用Q为负值的反调和滤波器
% fs=spfilt(gs,'chmean',3,3,-1.5);
% figure,imshow(fs);
% %min
% fsmin=spfilt(gs,'min',3,3);
% figure,imshow(fsmin);

% %%自适应中值滤波
% close all
% clf;
% A=imread(' C:\Users\ranji\Desktop\test2.jpg');
% B=A(:,:,1);
% imshow(B);
% fn=imnoise(B,'salt & pepper',0.25);
% figure,imshow(fn);
% f1=medfilt2(fn,[7 7],'symmetric'); %没有噪声，但是变得模糊和失真,感觉效果不明显
% figure,imshow(f1);
% f2=adpmedian(fn,7); %自适应中值滤波
% figure,imshow(f2);

% %%%%%模糊噪声图像，即退化建模
% close all
% f=checkerboard(8); %生成测试图像
% imshow(pixeldup(f,8),[]);  
% title('原图放大')
% PSF=fspecial('motion',7,45);
% gb=imfilter(f,PSF,'circular');
% figure,imshow(pixeldup(gb,8),[]);
% title('原图加退化函数模型')
% noise=imnoise(zeros(size(f)),'gaussian',0,0.001);
% figure,imshow(pixeldup(noise,8),[]);
% title('噪声')
% g1=gb+noise;
% figure,imshow(pixeldup(g1,8),[]); 
% title('原图+退化模型+噪声');  %%后面复原此图
% 
% g=im2uint8(g);
% %%%%维纳滤波 %要利用前面的退化模型
% fr1=deconvwnr(g,PSF);
% figure,imshow(pixeldup(fr1,8),[]);
% title('方式一：直接逆滤波的结果');
% %计算比率R
% Sn=abs(fft2(noise)).^2; %noise power spectrum
% nA=sum(Sn(:))/prod(size(noise));  %prod.m  对于矩阵返回的是按列向量的所有元素的积，然后组成一行向量；
% Sf=abs(fft2(f)).^2;
% fA=sum(Sf(:))/prod(size(f));
% R=nA/fA;
% fr2=deconvwnr(g,PSF,R);
% figure,imshow(pixeldup(fr2,8),[]);
% title('方式二：噪信比已知');  %效果明显
% %使用自相关函数
% NCORR=fftshift(real(ifft2((Sn))));
% ICORR=fftshift(real(ifft2((Sf))));
% fr3=deconvwnr(g,PSF,NCORR,ICORR);
% figure,imshow(pixeldup(fr3,8),[]);
% title('方式三：利用自相关函数');

% %%空间变换
% close all;
% T1=[3 0 0;0 2 0;0 0 1];
% tform1=maketform('affine',T1);
% vistformfwd(tform1,[0 100],[0 100]);
% title('水平缩放因子3，垂直缩放因子2')
% 
% T2=[1 0 0;.2 1 0;0 0 1];
% tform2=maketform('affine',T2);
% figure,vistformfwd(tform2,[0 100],[0 100]);
% 
% Tscale=[1.5 0 0;0 2 0;0 0 1];
% Trotation=[cos(pi/4) sin(pi/4) 0
%     -sin(pi/4) cos(pi/4) 0
%     0 0 1];
% Tshear=[1 0 0;.2 1 0;0 0 1];
% T3=Tscale*Trotation*Tshear;
% tform3=maketform('affine',T3);
% figure,vistformfwd(tform3,[0 100],[0 100]);

% %%对图像应用空间变换--线性等角变换
% close all
% f=checkerboard(40);  %%参数为8时，后面的图像变模糊;貌似越大越清晰
% imshow(pixeldup(f,8),[]);  
% s=0.8;
% theta=pi/6;
% T=[s*cos(theta) ,s*sin(theta) ,0;
%     -s*sin(theta) ,s*cos(theta), 0;
%     0, 0 ,1];
% tform=maketform('affine',T);
% g=imtransform(f,tform);
% figure,imshow(pixeldup(g,8),[]);  
% 
% g2=imtransform(f,tform,'nearest');
% figure,imshow(pixeldup(g2,8),[]); 


% %%RGB图像
% close all
% test2=imread('C:\Users\ranji\Desktop\test2.jpg');
% fR=test2(:,:,1);
% fG=test2(:,:,2);
% fB=test2(:,:,3);
% r=fR(1:8:end,1:8:end);
% g=fG(1:8:end,1:8:end);
% b=fB(1:8:end,1:8:end);
% imshow(r);
% figure,imshow(g);
% figure,imshow(b);
% rgb_image=cat(3,r,g,b);
% figure,imshow(rgb_image);
% %imwrite(rgb_image,'C:\Users\ranji\Desktop\rgb_image.jpg');

% %%索引图像
% close all
% clear all
% clc;
% rgb_image=imread('C:\Users\ranji\Desktop\rgb_image.jpg');
% f=rgb2gray(rgb_image);
% [X,map]=gray2ind(f,100);
% imshow(X,map);
% % fd=mat2gray(f);
% %XX=grayslice(fd,0.89); %%全是黑色的？？
% [X1,map1]=rgb2ind(rgb_image,8,'nodither'); %RGB图像创建索引图像
% figure,imshow(X1,map1);
% [X2,map2]=rgb2ind(rgb_image,8,'dither');
% figure,imshow(X2,map2);
% g=dither(f);
% figure,imshow(g),   %抖动效果


%%%svd重构图像
% clear all;
% close all;
% clc;
% 
% a=imread('C:\Users\ranji\Desktop\rgb_image.jpg');
% 
% imshow(mat2gray(a))
% [m n]=size(a);
% a=double(a);
% %r=rank(a);
% [s v d]=svd(a(:,:,1));
% 
% %re=s*v*d';
% re=s(:,:)*v(:,1:1)*d(:,1:1)';
% figure;
% imshow(mat2gray(re));
% imwrite(mat2gray(re),'C:\Users\ranji\Desktop\1.jpg')
% 
% re1=s(:,:)*v(:,1:20)*d(:,1:20)';
% figure;
% imshow(mat2gray(re));
% imwrite(mat2gray(re),'C:\Users\ranji\Desktop\2.jpg')
% 
% re=s(:,:)*v(:,1:80)*d(:,1:80)';
% figure;
% imshow(mat2gray(re));
% imwrite(mat2gray(re),'C:\Users\ranji\Desktop\3.jpg')
% 
% re=s(:,:)*v(:,1:150)*d(:,1:150)';
% figure;
% imshow(mat2gray(re));
% imwrite(mat2gray(re),'C:\Users\ranji\Desktop\4.jpg')

% %% 测试figure上标题添加变量
% close all;
% for i=1:10
%     figure(i);
%     x = -pi:.1:pi;
%     y = sin(x); 
%     plot(x,y);
%     set(gca,'XTick',-pi:pi/2:pi);
%     set(gca,'XTickLabel',{'-pi','-pi/2','0','pi/2','pi'});
%     xlabel('-/pi /leq /Theta /leq /pi');    %图像下方-1.22处加入x坐标轴名称
%     ylabel('sin(/Theta)');                      %图像y坐标轴名称
%     a=[1,2,3,4,5,6,7,8,9,10];
%     % title('Plot of sin(/Theta)');      %图像上方加入字符串标题（string）
%     %title(['order=',num2str(i)]);    %图像上方加入变量标题（variable）
%     title({'x in this figure is equal to' i});
%     %title(['order=',num2str(a(i))],'position',[0 -1.28]);    %图像下方中间加入变量标题（variable）
%     % title(['order=',num2str(a(2))],'position',[0 -1.22]);    %图像下方中间与'xlabel'同位置加入变量标题（variable）
%     text(-pi/4,sin(-pi/4),'/leftarrow sin(-/pi/div4)',...
%         'HorizontalAlignment','left');                                      %图像注释（annotation）
%end

% %%彩色图像空间转换
% close all
% clear all
% clc;
% rgb_image=imread('C:\Users\ranji\Desktop\rgb_image.jpg');
% yiq_image=rgb2ntsc(rgb_image); %RGB转YIQ图像
% imshow(yiq_image);
% ycbcr_image=rgb2ycbcr(rgb_image);%RGB转YCBCR
% figure,imshow(ycbcr_image);
% hsv_image=rgb2hsv(rgb_image);% RGB转HSV
% figure,imshow(hsv_image);
% cmy_image=imcomplement(rgb_image); %RGB转HSI
% figure,imshow(cmy_image);
% hsi_imge=rgb2hsi(rgb_image); %RGB转HSI
% figure,imshow(hsi_imge);  %效果和hsv有点像
% % 不同分量的效果;
% hsi_h_image=hsi_imge(:,:,1);
% figure,imshow(hsi_h_image);
% hsi_s_image=hsi_imge(:,:,2);
% figure,imshow(hsi_s_image);
% hsi_i_image=hsi_imge(:,:,3);
% figure,imshow(hsi_i_image);


% %%彩色图像空间滤波
% close all
% clear all
% clc;
% rgb_image=imread('C:\Users\ranji\Desktop\rgb_image.jpg');
% imshow(rgb_image);
% %g=ice('image',rgb_image);
% lapmask=[1 1 1;1 -8 1; 1 1 1];
% fen=imsubtract(rgb_image,imfilter(rgb_image,lapmask,'replicate'));  %彩色图像锐化
% figure,imshow(fen);
% [VG,A,PPG]=colorgrad(rgb_image);%梯度的彩色边缘检测
% figure,imshow(A);
% figure,imshow(VG);

%%彩色图像图像分割
close all
clear all
clc;
rgb_image=imread('C:\Users\ranji\Desktop\rgb_image.jpg');
mask=roipoly(rgb_image);  %select region interactively
red=immultiply(mask,rgb_image(:,:,1));
green=immultiply(mask,rgb_image(:,:,2));
blue=immultiply(mask,rgb_image(:,:,3));
g=cat(3,red,green,blue);
figure,imshow(g)

[M,N,K]=size(g);
I=reshape(g,M*N,3);
idx=find(mask);
I=double(I(idx,1:3));
[C,m]=covmatrix(I);
d=diag(C);
sd=sqrt(d)';
E25=colorseg('euclidean',rgb_image,50,m);  %效果不太好；根据sd的值选择阈值
figure,imshow(E25);
