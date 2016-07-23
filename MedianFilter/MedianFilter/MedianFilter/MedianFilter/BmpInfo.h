#ifndef __BMPINFO_H__
#define __BMPINFO_H__

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef long LONG;

//位图文件头BITMAGFILEHEADER
typedef struct tagBITMAPFILEHEADER
{
    //WORD bfType; //位图文件类型，必须为BM
	DWORD bfSize; //位图文件的大小，字节单位
	WORD bfReserved1; //位图文件保留字，必须为0
	WORD bfReserved2; //位图文件保留字，必须为0
	DWORD bfOffBits; //位图文件头到数据的偏移
}BITMAPFILEHEADER;

//位图信息头BITMAPINFOHEADER
typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize; //该结构所占字节数
	LONG biWidth; //位图的宽度，像素单位
	LONG biHeight; //位图的高度，像素单位
	WORD biPlanes; //目标设备的位面数，必须为1
	WORD biBitCount; //颜色深度，即每个像素所占的位数
	DWORD biCompression; //位图的压缩类型
	DWORD biSizeImage; //位图的大小，字节单位
	LONG biXPelsPerMeter; //位图的水平分辨率
	LONG biYPelsPerMeter; //位图的垂直分辨率
	DWORD biClrUsed; //位图实际使用的颜色表中颜色数
	DWORD biClrImportant; //位图显示中比较重要的颜色数
}BITMAPINFOHEADER;

//颜色表RGBQUAD
typedef struct tagRGBQUAD
{
	BYTE rgbBlue; //该颜色的蓝色分量
	BYTE rgbGreen; //该颜色的绿色分量
	BYTE rgbRed; //该颜色的红色分量
	BYTE rgbReserved; //保留值
}RGBQUAD;

//像素信息IMAGEDATA
typedef struct tagIMAGEDATA
{
	BYTE blue;
	BYTE green;
	BYTE red;
}IMAGEDATA;

#endif