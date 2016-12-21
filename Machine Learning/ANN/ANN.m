% %产生指定类别的样本点，并在图中绘出
% X = [0 1; 0 1]; % 限制类中心的范围
% clusters = 5; % 指定类别数目
% points = 10; % 指定每一类的点的数目
% std_dev = 0.05; % 每一类的标准差
% P = nngenc(X,clusters,points,std_dev);
% plot(P(1,:),P(2,:),'+r');
% title('输入样本向量');
% xlabel('p(1)');
% ylabel('p(2)');
% 
% %建立网络
% net=newc([0 1;0 1],5,0.1); %设置神经元数目为5
% %得到网络权值，并在图上绘出
% figure;
% plot(P(1,:),P(2,:),'+r');
% w=net.iw{1}
% hold on;
% plot(w(:,1),w(:,2),'ob');
% hold off;
% title('输入样本向量及初始权值');
% xlabel('p(1)');
% ylabel('p(2)');
% figure;
% plot(P(1,:),P(2,:),'+r');
% hold on;
% 
% %训练网络
% net.trainParam.epochs=7;
% net=init(net);
% net=train(net,P);
% %得到训练后的网络权值，并在图上绘出
% w=net.iw{1}
% plot(w(:,1),w(:,2),'ob');
% hold off;
% title('输入样本向量及更新后的权值');
% xlabel('p(1)');
% ylabel('p(2)');
% a=0;
% p = [0.6 ;0.8];
% a=sim(net,p)
% 
% 
% %**************指定输入二维向量及其类别*******************
% P = [-3 -2 -2 0 0 0 0 +2 +2 +3;
% 0 +1 -1 +2 +1 -1 -2 +1 -1 0];
% C = [1 1 1 2 2 2 2 1 1 1];
% %将这些类别转换成学习向量量化网络使用的目标向量
% T = ind2vec(C)
% %用不同的颜色，绘出这些输入向量
% plotvec(P,C),
% title('输入二维向量');
% xlabel('P(1)');
% ylabel('P(2)');
% 
% %建立网络
% net = newlvq(minmax(P),4,[.6 .4],0.1);
% %在同一幅图上绘出输入向量及初始权重向量
% figure;
% plotvec(P,C)
% hold on
% W1=net.iw{1};
% plot(W1(1,1),W1(1,2),'ow')
% title('输入以及权重向量');
% xlabel('P(1), W(1)');
% ylabel('P(2), W(2)');
% hold off;
% 
% %训练网络，并再次绘出权重向量
% figure;
% plotvec(P,C);
% hold on;
% net.trainParam.epochs=150;
% net.trainParam.show=Inf;
% net=train(net,P,T);
% plotvec(net.iw{1}',vec2ind(net.lw{2}),'o');
% %对于一个特定的点，得到网络的输出
% p = [0.8; 0.3];
% a = vec2ind(sim(net,p))
% 
% %%%%%%%%%**********随机生成1000个二维向量，作为样本，并绘出其分布*************
% P = rands(2,1000);
% plot(P(1,:),P(2,:),'+r')
% title('初始随机样本点分布');
% xlabel('P(1)');
% ylabel('P(2)');
% 
% %建立网络，得到初始权值
% net=newsom([0 1; 0 1],[5 6]);
% w1_init=net.iw{1,1}
% %绘出初始权值分布图
% figure;
% plotsom(w1_init,net.layers{1}.distances)
% %分别对不同的步长，训练网络，绘出相应的权值分布图
% for i=10:30:100
%     net.trainParam.epochs=i;
%     net=train(net,P);
%     figure;
%     plotsom(net.iw{1,1},net.layers{1}.distances)
% end
% %对于训练好的网络，选择特定的输入向量，得到网络的输出结果
% p=[0.5;0.3];
% a=0;
% a = sim(net,p)
% 

%读取训练数据
[f1,f2,f3,f4,class] = textread('iris.txt' , '%f,%f,%f,%f,%d',150); %数据格式和读入方式相同

%特征值归一化
[input,minI,maxI] = premnmx( [f1 , f2 , f3 , f4 ]')  ;

%构造输出矩阵
s = length( class) ;
output = zeros( s , 3  ) ;
for i = 1 : s 
   output( i , class( i )  ) = 1 ;
end

%创建神经网络
net = newff( minmax(input) , [10 3] , { 'logsig' 'purelin' } , 'traingdx' ) ; 

%设置训练参数
net.trainparam.show = 50 ;
net.trainparam.epochs = 500 ;
net.trainparam.goal = 0.01 ;
net.trainParam.lr = 0.01 ;

%开始训练
net = train( net, input , output' ) ;

%读取测试数据
[t1 t2 t3 t4 c] = textread('iris.txt' , '%f,%f,%f,%f,%f',150);

%测试数据归一化
testInput = tramnmx ( [t1,t2,t3,t4]' , minI, maxI ) ;

%仿真
Y = sim( net , testInput ) 

%统计识别正确率
[s1 , s2] = size( Y ) ;
hitNum = 0 ;
for i = 1 : s2
    [m , Index] = max( Y( : ,  i ) ) ;
    if( Index  == c(i)   ) 
        hitNum = hitNum + 1 ; 
    end
end
sprintf('识别率是 %3.3f%%',100 * hitNum / s2 )
