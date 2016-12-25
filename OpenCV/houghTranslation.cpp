/*!
 * \file houghTranslation.cpp
 *
 * \author ranjiewen
 * \date 2016/12/25 16:31
 *
 * 
 */

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <fstream>
using namespace std;
using namespace cv;


//全局变量申明
Mat g_srcImage, g_dstImage, g_midImage, circleImage;//原始图、中间图和效果图
vector<Vec4i> g_lines;//定义一个矢量结构g_lines用于存放得到的线段矢量集合
vector<Vec3f> circles;
//变量接收的TrackBar位置参数
int g_nthreshold=100;
ofstream text; //输出流写文件

//函数申明
static void on_HoughLines(int, void*);//回调函数
static void ShowHelpText();
void drawDetectLines(Mat& image, const vector<Vec4i>& lines, Scalar & color);
void drawDetectCircles(Mat& image, const vector<Vec3f> &circles, Scalar & color);


int main(int agrc,char** argv[])
{
	//改变console字体颜色
	system("color 4F");  
	ShowHelpText();


	//载入原始图和Mat变量定义   
	Mat g_srcImage = imread("CAL_GRAY768_Pro.bmp");  //工程目录下应该有一张名为1.jpg的素材图
	//显示原始图  
	//imshow("【原始图】", g_srcImage);  


	//创建滚动条
	namedWindow("【效果图】",1);
	createTrackbar("值", "【效果图】",&g_nthreshold,200,on_HoughLines);
	//createTrackbar("值", "【效果图】", &g_nthreshold, 200, on_HoughCircle);


	//进行边缘检测和转化为灰度图
	Canny(g_srcImage, g_midImage, 50, 150, 3);//进行一次canny边缘检测
	//imshow("边缘图",g_midImage);
	cvtColor(g_midImage,g_dstImage, COLOR_GRAY2BGR);//转化边缘检测后的图为灰度图
	//调用一次回调函数，调用一次HoughLinesP函数
	on_HoughLines(g_nthreshold,0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI/180, 80, 50, 10 );


	cvtColor(g_srcImage, circleImage, COLOR_BGR2GRAY);
	GaussianBlur(circleImage, circleImage, Size(9, 9), 2, 2);
	//数的调整是关键，一定要知道各参数的调整才能调出合适的参数,感觉最小投票数对结果影响较大
	HoughCircles(circleImage, circles, HOUGH_GRADIENT, 1, 5, 100, 25, 0, 50);   


	text.open("textRecord.txt",ios::out);
	drawDetectLines(g_srcImage, g_lines, Scalar(0, 255, 0));
	drawDetectCircles(g_srcImage, circles, Scalar(0, 255, 0));
	text.close();

	//显示效果图  
	imshow("【效果图】", g_dstImage);  
	imshow("效果图", g_srcImage);
	imwrite("canny_result.bmp", g_dstImage); //保存图
	imwrite("hough_trans.bmp", g_srcImage); //保存图

	waitKey(0);  

	return 0;  

}



void drawDetectLines(Mat& image, const vector<Vec4i>& lines, Scalar & color)
{
	text << "检测到的直线总数:" << lines.size() <<"两个坐标为一组。"<< endl;
	// 将检测到的直线在图上画出来
	vector<Vec4i>::const_iterator it = lines.begin();
	while (it != lines.end())
	{
		Point pt1((*it)[0], (*it)[1]);
		Point pt2((*it)[2], (*it)[3]);
		line(image, pt1, pt2, color, 2); //  线条宽度设置为2
		++it;
	}
	for (int i = 0; i < lines.size(); i++)
	{
		char str[_MAX_PATH];
		sprintf_s(str, _MAX_PATH, "第%d条直线两个端点坐标：", i + 1);

		text << str << "    (" << (lines.at(i)) << ")" << endl;
	}
	text << endl;
}

void drawDetectCircles(Mat& image, const vector<Vec3f> &circles, Scalar & color)
{
	text << "检测到的圆的总数：" << circles.size() << endl;
	for (size_t i = 0; i < circles.size(); i++)
	{
		//参数定义
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);

		char str[_MAX_PATH];
		sprintf_s(str, _MAX_PATH, "第%d个圆心坐标：   ", i + 1);
		text << str << "   (" << circles[i][0] << "," << circles[i][1] << ")         " << "圆的半径：" << radius << endl;

		//绘制圆心
		circle(image, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(image, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}

}

static void  on_HoughCircle(int ,void*)
{
	GaussianBlur(g_midImage, g_midImage, Size(9, 9), 2, 2);

	//【4】进行霍夫圆变换
	vector<Vec3f> circles;
	HoughCircles(g_midImage, circles, HOUGH_GRADIENT, 1.5, 10, 200, 100, 0, 0);

	//【5】依次在图中绘制出圆
	for (size_t i = 0; i < circles.size(); i++)
	{
		//参数定义
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle(g_srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(g_srcImage, center, radius, Scalar(155, 50, 255), 3, 8, 0);
	}
}

//---【on_HoughLines( )函数】-------------------
//		描述：【顶帽运算/黑帽运算】窗口的回调函数
//----------------------------------------------
static void on_HoughLines(int, void*)
{
	//定义局部变量储存全局变量
	Mat dstImage=g_dstImage.clone();
	Mat midImage=g_midImage.clone();

	//调用HoughLinesP函数
	vector<Vec4i> mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI/180, g_nthreshold+1, 50, 10 );

	//循环遍历绘制每一条线段
	for( size_t i = 0; i < mylines.size(); i++ )
	{
		Vec4i l = mylines[i];
		line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23,180,55), 1, LINE_AA);
	}
	//显示图像
	imshow("【效果图】",dstImage);
}

static void ShowHelpText()
{
	//输出欢迎信息和OpenCV版本
	
	printf("\n\n\t\t\t   当前使用的OpenCV版本为：" CV_VERSION );
	printf("\n\n  ----------------------------------------------------------------------------\n");

	//输出一些帮助信息
	printf("\n\n\n\t请调整滚动条观察图像效果~\n\n");


}
