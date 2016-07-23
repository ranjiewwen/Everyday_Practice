#include <iostream>
#include "MyImage.h"

int main()
{
	MyImage mybmp(std::string("Image\\init.bmp"), std::string("Image\\result.bmp"));
	mybmp.LoadImage(); //读取RGB图片
	mybmp.Convert(); //转换成灰度图片
	mybmp.MedianFilterOper(); //中值过滤
	mybmp.SaveImage(); //保存图片
}