
function histLBP=getLBPHist(I,r,c)
%取的I分区的LBP直方图
%
%输入： r,c--分区的数目，r*c个分区
%
%返回：histLBP---连接I的各个分块的LBP直方图而形成的代表I的LBP复合特征向量

[m,n]=size(I);
%计算分区的大小
mPartitionSize=floor(m/r);
nPartitionSize=floor(n/c);
for ii=1:r-1
    for jj=1:c-1
        Sub=I((ii-1)*mPartitionSize+1:ii*mPartitionSize,(jj-1)*nPartitionSize+1:jj*nPartitionSize);
      %  hist{ii}{jj}=LBP();
    end
end

