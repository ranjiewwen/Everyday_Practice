#include <stdio.h>
#include <stdlib.h>
#include "MyImage.h"
#include "BmpInfo.h"


MyImage::MyImage(std::string &readfile, std::string &loadfile)
	:m_readfile(readfile),
	 m_loadfile(loadfile),
	 m_imagedata(NULL)
{}

MyImage::~MyImage()
{
	if (NULL != m_imagedata)
	{
		delete[]m_imagedata;
		m_imagedata = NULL;
	}
}

void MyImage::LoadImage()
{
	//0. 打开文件
	FILE *fp = fopen(m_readfile.c_str(), "rb");
	if (NULL == fp)
	{
		perror("fopen readfile error");
		exit(EXIT_FAILURE);
	}
	//1. 读取bmp文件信息:文件头，信息头，颜色表，像素信息
	WORD bfType;
	int ret = fread(&bfType, sizeof(WORD), 1, fp);
	if (0 == ret)
	{
		perror("read bfType error");
		exit(EXIT_FAILURE);
	}
	if (0x4d42 != bfType)
	{
		std::cout << "此图片非bmp图片" << std::endl;
		exit(EXIT_FAILURE);
	}

	ret = fread(&m_bmpHead, sizeof(m_bmpHead), 1, fp);
	if (0 == ret)
	{
		perror("read bmpHead error");
		exit(EXIT_FAILURE);
	}
	
	ret = fread(&m_bmpInfo, sizeof(m_bmpInfo), 1, fp);
	if (0 == ret)
	{
		perror("read bmpInfo error");
		exit(EXIT_FAILURE);
	}


	int width = m_bmpInfo.biWidth;
	int height = m_bmpInfo.biHeight;
	int widthbyte = (width * m_bmpInfo.biBitCount/8 + 3) / 4 * 4;
	m_imagedata = new unsigned char[widthbyte * height];

	ret = fread(m_imagedata, widthbyte*height, 1, fp);
	if (0 == ret)
	{
		perror("read imagedata error");
		exit(EXIT_FAILURE);
	}

	fclose(fp);
	std::cout << "Load Image Success!" << std::endl;
}

void MyImage::SaveImage()
{
	//0. 创建文件
	FILE *fp = fopen(m_loadfile.c_str(), "wb");
	if (NULL == fp)
	{
		perror("fopen loadfile error");
		exit(EXIT_FAILURE);
	}
	//1. 写入图片信息:文件头，信息头，颜色表，像素信息
	WORD bfType = 0x4d42;
	int ret = fwrite(&bfType, sizeof(WORD), 1, fp);
	if (0 == ret)
	{
		perror("write bfType error");
		exit(EXIT_FAILURE);
	}
	
	ret = fwrite(&m_bmpHead, sizeof(m_bmpHead), 1, fp);
	if (0 == ret)
	{
		perror("write bmpHead error");
		exit(EXIT_FAILURE);
	}
	
	ret = fwrite(&m_bmpInfo, sizeof(m_bmpInfo), 1, fp);
	if (0 == ret)
	{
		perror("write bmpInfo error");
		exit(EXIT_FAILURE);
	}

	int width = m_bmpInfo.biWidth;
	int height = m_bmpInfo.biHeight;
	int widthbyte = (width * m_bmpInfo.biBitCount/8 + 3) / 4 * 4;
	fwrite(m_imagedata, widthbyte*height, 1, fp);
	
	fclose(fp);

	std::cout << "Save Image Success" << std::endl;
}

void MyImage::Convert()
{
	int width = m_bmpInfo.biWidth;
	int height = m_bmpInfo.biHeight;
	int widthbyte = (width * m_bmpInfo.biBitCount / 8 + 3) / 4 * 4;
	for (int i = 0; i < widthbyte*height;)
	{
		int gray = (m_imagedata[i] + m_imagedata[i + 1] + m_imagedata[i + 2])/3;
		m_imagedata[i] = gray;
		m_imagedata[i+1] = gray;
		m_imagedata[i+2] = gray;
		i += 3;
	}
}

//中值滤波：本算法采用3*3的领域范围
void MyImage::MedianFilterOper()
{
	//0. 准备：获取图片的宽，高和像素信息，
	int const num = 3 * 3;
	unsigned char pixel[num] = { 0 }; //保存领域的像素值
	int width = m_bmpInfo.biWidth;
	int height = m_bmpInfo.biHeight;
	int widthbyte = (width * m_bmpInfo.biBitCount / 8 + 3) / 4 * 4;  //保证为4的倍数
	//相对于中心点，3*3领域中的点需要偏移的位置
	int delta[3 * 3][2] = {
		{ -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, -1 }, { 0, 0 }, { 0, 1 }, { 1, -1 }, { 1, 0 }, {1, 1}
    };	
	//1. 中值滤波，没有考虑边缘
	for (int i = 1; i < height-1; ++i)
	{
		for (int j = 1; j < widthbyte-1; ++j)
		{
			//1.1 提取领域值
			for (int k = 0; k < num; ++k)
			{
				pixel[k] = m_imagedata[(i + delta[k][0])*widthbyte + j + delta[k][1]];
			}
			//1.2 排序
			qsort(pixel, num, sizeof(unsigned char), compa);
			//1.3 获取该中心点的值
			m_imagedata[i*widthbyte + j] = pixel[num / 2];
		}
	}
}