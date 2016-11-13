


/*!
 * \file Capture.cpp
 *
 * \author ranjiewen
 * \date 十一月 2016
 *
 *  http://www.cnblogs.com/tanfy/p/5552270.html

    解析opencv自带人脸识别源码（……/opencv-3.1.0/samples/cpp/facedetect.cpp）
 */
#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

static void help()
{
	cout << "\nThis program demonstrates the cascade recognizer. Now you can use Haar or LBP features.\n"
		"This classifier can recognize many kinds of rigid objects, once the appropriate classifier is trained.\n"
		"It's most known use is for faces.\n"
		"Usage:\n"
		"./facedetect [--cascade=<cascade_path> this is the primary trained classifier such as frontal face]\n"
		"   [--nested-cascade[=nested_cascade_path this an optional secondary classifier such as eyes]]\n"
		"   [--scale=<image scale greater or equal to 1, try 1.3 for example>]\n"
		"   [--try-flip]\n"
		"   [filename|camera_index]\n\n"
		"see facedetect.cmd for one call:\n"
		"./facedetect --cascade=\"../../data/haarcascades/haarcascade_frontalface_alt.xml\" --nested-cascade=\"../../data/haarcascades/haarcascade_eye_tree_eyeglasses.xml\" --scale=1.3\n\n"
		"During execution:\n\tHit any key to quit.\n"
		"\tUsing OpenCV version " << CV_VERSION << "\n" << endl;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade,
	double scale, bool tryflip);

string cascadeName;
string nestedCascadeName;



int main(int argc, const char** argv)
{
	VideoCapture capture;
	Mat frame, image;
	string inputName;
	bool tryflip;

	// CascadeClassifier是Opencv中做人脸检测的时候的一个级联分类器，现在有两种选择：一是使用老版本的CvHaarClassifierCascade函数，一是使用新版本的CascadeClassifier类。老版本的分类器只支持类Haar特征，而新版本的分类器既可以使用Haar，也可以使用LBP特征。
	CascadeClassifier cascade, nestedCascade;
	double scale;

	cv::CommandLineParser parser(argc, argv,
		"{help h||}"
		"{cascade|D:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml|}"   //默认路径实在安装路径下sample，修改了路径，以便加载load成功
		"{nested-cascade|D:/opencv/sources/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml|}"  //修改路径
		"{scale|1|}{try-flip||}{@filename||}" //文件为空时，设置摄像头，实时检测人脸
		);
	if (parser.has("help"))
	{
		help();
		return 0;
	}

	cascadeName = parser.get<string>("cascade");
	nestedCascadeName = parser.get<string>("nested-cascade");
	scale = parser.get<double>("scale");
	if (scale < 1)
		scale = 1;
	tryflip = parser.has("try-flip");
	inputName = parser.get<string>("@filename");
	std::cout << inputName << std::endl;  // test
	if (!parser.check())
	{
		parser.printErrors();
		return 0;
	}

	// 加载模型
	if (!nestedCascade.load(nestedCascadeName))
		cerr << "WARNING: Could not load classifier cascade for nested objects" << endl;
	if (!cascade.load(cascadeName))
	{
		cerr << "ERROR: Could not load classifier cascade" << endl;
		help();
		return -1;
	}
	// 读取摄像头
	// isdigit检测字符是否为阿拉伯数字 
	if (inputName.empty() || (isdigit(inputName[0]) && inputName.size() == 1))
	{
		int c = inputName.empty() ? 0 : inputName[0] - '0';
		// 此处若系统在虚拟机上，需在虚拟机中设置接管摄像头：虚拟机(M)-> 可移动设备 -> 摄像头名称 -> 连接(断开与主机连接)
		if (!capture.open(c))
			cout << "Capture from camera #" << c << " didn't work" << endl;
		else {
			capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
			capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
		}
	}
	else if (inputName.size())
	{
		image = imread(inputName, 1);
		if (image.empty())
		{
			if (!capture.open(inputName))
				cout << "Could not read " << inputName << endl;
		}
	}
	else
	{
		image = imread("../data/lena.jpg", 1);
		if (image.empty()) cout << "Couldn't read ../data/lena.jpg" << endl;
	}

	if (capture.isOpened())
	{
		cout << "Video capturing has been started ..." << endl;


		for (;;)
		{
			std::cout << "capturing..." << std::endl;  // test
			capture >> frame;
			if (frame.empty())
				break;

			Mat frame1 = frame.clone();
			std::cout << "Start to detect..." << std::endl;  // test
			detectAndDraw(frame1, cascade, nestedCascade, scale, tryflip);

			int c = waitKey(10);
			if (c == 27 || c == 'q' || c == 'Q')
				break;
		}
	}
	else
	{
		cout << "Detecting face(s) in " << inputName << endl;
		if (!image.empty())
		{
			detectAndDraw(image, cascade, nestedCascade, scale, tryflip);
			waitKey(0);
		}
		else if (!inputName.empty())
		{
			/* assume it is a text file containing the
			list of the image filenames to be processed - one per line */
			FILE* f = fopen(inputName.c_str(), "rt");
			if (f)
			{
				char buf[1000 + 1];
				while (fgets(buf, 1000, f))
				{
					int len = (int)strlen(buf), c;
					while (len > 0 && isspace(buf[len - 1]))
						len--;
					buf[len] = '\0';
					cout << "file " << buf << endl;
					image = imread(buf, 1);
					if (!image.empty())
					{
						detectAndDraw(image, cascade, nestedCascade, scale, tryflip);
						c = waitKey(0);
						if (c == 27 || c == 'q' || c == 'Q')
							break;
					}
					else
					{
						cerr << "Aw snap, couldn't read image " << buf << endl;
					}
				}
				fclose(f);
			}
		}
	}

	return 0;
}

void detectAndDraw(Mat& img, CascadeClassifier& cascade,
	CascadeClassifier& nestedCascade,
	double scale, bool tryflip)
{
	double t = 0;
	vector<Rect> faces, faces2;
	const static Scalar colors[] =
	{
		Scalar(255, 0, 0),
		Scalar(255, 128, 0),
		Scalar(255, 255, 0),
		Scalar(0, 255, 0),
		Scalar(0, 128, 255),
		Scalar(0, 255, 255),
		Scalar(0, 0, 255),
		Scalar(255, 0, 255)
	};
	Mat gray, smallImg;

	cvtColor(img, gray, COLOR_BGR2GRAY);
	double fx = 1 / scale;
	resize(gray, smallImg, Size(), fx, fx, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	t = (double)cvGetTickCount();
	cascade.detectMultiScale(smallImg, faces,
		1.1, 2, 0
		//|CASCADE_FIND_BIGGEST_OBJECT
		//|CASCADE_DO_ROUGH_SEARCH
		| CASCADE_SCALE_IMAGE,
		Size(30, 30));
	if (tryflip)
	{
		flip(smallImg, smallImg, 1);
		cascade.detectMultiScale(smallImg, faces2,
			1.1, 2, 0
			//|CASCADE_FIND_BIGGEST_OBJECT
			//|CASCADE_DO_ROUGH_SEARCH
			| CASCADE_SCALE_IMAGE,
			Size(30, 30));
		for (vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end(); r++)
		{
			faces.push_back(Rect(smallImg.cols - r->x - r->width, r->y, r->width, r->height));
		}
	}
	t = (double)cvGetTickCount() - t;
	printf("detection time = %g ms\n", t / ((double)cvGetTickFrequency()*1000.));
	for (size_t i = 0; i < faces.size(); i++)
	{
		Rect r = faces[i];
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i % 8];
		int radius;

		double aspect_ratio = (double)r.width / r.height;
		if (0.75 < aspect_ratio && aspect_ratio < 1.3)
		{
			center.x = cvRound((r.x + r.width*0.5)*scale);
			center.y = cvRound((r.y + r.height*0.5)*scale);
			radius = cvRound((r.width + r.height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
		else
			rectangle(img, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
			cvPoint(cvRound((r.x + r.width - 1)*scale), cvRound((r.y + r.height - 1)*scale)),
			color, 3, 8, 0);
		if (nestedCascade.empty())
			continue;
		smallImgROI = smallImg(r);
		nestedCascade.detectMultiScale(smallImgROI, nestedObjects,
			1.1, 2, 0
			//|CASCADE_FIND_BIGGEST_OBJECT
			//|CASCADE_DO_ROUGH_SEARCH
			//|CASCADE_DO_CANNY_PRUNING
			| CASCADE_SCALE_IMAGE,
			Size(30, 30));
		for (size_t j = 0; j < nestedObjects.size(); j++)
		{
			Rect nr = nestedObjects[j];
			center.x = cvRound((r.x + nr.x + nr.width*0.5)*scale);
			center.y = cvRound((r.y + nr.y + nr.height*0.5)*scale);
			radius = cvRound((nr.width + nr.height)*0.25*scale);
			circle(img, center, radius, color, 3, 8, 0);
		}
	}
	imshow("result", img);
}




/*****************************************************
* \file Capture.cpp
* \date 2016/11/10 0:22
* \author ranjiewen
* \contact: ranjiewen@outlook.com
* \问题描述：
http://www.cnblogs.com/lingshaohu/archive/2011/12/16/2290017.html

* \问题分析：
可以存avi,但是不能打开，待改善
*****************************************************/

//#include <iostream>
//#include <opencv2/opencv.hpp>
//using namespace cv;;
//using namespace std;
//int main()
//{
//	CvCapture* capture = cvCaptureFromCAM(-1);
//	CvVideoWriter* video = NULL;
//	IplImage* frame = NULL;
//	int n;
//	if (!capture) //如果不能打开摄像头给出警告
//	{
//		cout << "Can not open the camera." << endl;
//		return -1;
//	}
//	else
//	{
//		frame = cvQueryFrame(capture); //首先取得摄像头中的一帧
//		video = cvCreateVideoWriter("camera.avi", CV_FOURCC('X', 'V', 'I', 'D'), 25,
//			cvSize(frame->width, frame->height)); //创建CvVideoWriter对象并分配空间
//		//保存的文件名为camera.avi，编码要在运行程序时选择，大小就是摄像头视频的大小，帧频率是32
//		if (video) //如果能创建CvVideoWriter对象则表明成功
//		{
//			cout << "VideoWriter has created." << endl;
//		}
//
//		cvNamedWindow("Camera Video", 1); //新建一个窗口
//		int i = 0;
//		while (i <= 300) // 让它循环200次自动停止录取
//		{
//			frame = cvQueryFrame(capture); //从CvCapture中获得一帧
//			if (!frame)
//			{
//				cout << "Can not get frame from the capture." << endl;
//				break;
//			}
//			n = cvWriteFrame(video, frame); //判断是否写入成功，如果返回的是1，表示写入成功
//			cout << n << endl;
//			cvShowImage("Camera Video", frame); //显示视频内容的图片
//			i++;
//			if (cvWaitKey(2) > 0)
//				break; //有其他键盘响应，则退出
//		}
//
//		cvReleaseVideoWriter(&video);
//		cvReleaseCapture(&capture);
//		cvDestroyWindow("Camera Video");
//	}
//	return 0;
//}