#ifndef __MYIMAGE_H__
#define __MYIMAGE_H__

/*!
 * \file MyImage.h
 * \date 2016/07/23 19:30
 *
 * \author ranjiewen
 * \contact: ranjiewen@outlook.com
 *
 * \brief 图相处理中值滤波
 *
 * TODO: long description
 *
 * \note
*/

#include <iostream>
#include <string>
#include "BmpInfo.h"

class MyImage
{
public:
	MyImage(std::string &readfile, std::string &loadfile);
	~MyImage();

	void LoadImage();//读取图像
	void SaveImage();//输出图像
	void Convert();//将RGB图转换成灰度图
	void MedianFilterOper();//对图像进行中值滤波操作

private:
	static int compa(const void *a, const void *b) //排序中的比较函数
	{
		return *(char *)a - *(char *)b;
	}
private:
	std::string m_readfile; //原始图片路径
	std::string m_loadfile; //输出图片路径
	BITMAPFILEHEADER m_bmpHead; 
	RGBQUAD m_bmpPla[256];
	BITMAPINFOHEADER m_bmpInfo;
	unsigned char *m_imagedata;
};

#endif