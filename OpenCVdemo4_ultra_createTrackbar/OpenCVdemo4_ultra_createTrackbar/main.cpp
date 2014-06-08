
//-----------------------------------【程序说明】----------------------------------------------
//  程序名称：   createTrackbar函数 官方sample程序【 浅墨优化&详细注释版】
//	 说明：【OpenCV入门教程之四】 创建Trackbar &图像对比度、亮度值调整  配套博文源码之【番外篇】
//  VisualStudio 2010版   使用OpenCV版本：2.4.8
//	 官方原版示例路径：opencv_source_code/samples/cpp/connected_components.cpp 
//	 配套博文链接：http://blog.csdn.net/poem_qianmo/article/details/21479533
//	 2014年3月18 日 Edited by 浅墨
//	 浅墨的微博：@浅墨_毛星云
//------------------------------------------------------------------------------------------------

//-----------------------------------【头文件包含部分】---------------------------------------
//	描述：包含程序所依赖的头文件
//---------------------------------------------------------------------------------------------- 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

//-----------------------------------【命名空间声明部分】---------------------------------------
//	描述：包含程序所使用的命名空间
//-----------------------------------------------------------------------------------------------   
using namespace cv;
using namespace std;

//-----------------------------------【全局函数声明部分】--------------------------------------
//	描述：全局函数声明
//-----------------------------------------------------------------------------------------------
Mat img;
int threshval = 160;			//轨迹条滑块对应的值，给初值160

//-----------------------------【on_trackbar( )函数】------------------------------------
//	描述：轨迹条的回调函数
//-----------------------------------------------------------------------------------------------
static void on_trackbar(int, void*)
{
	Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);

	//定义点和向量
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//查找轮廓
	findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
	//初始化dst
	Mat dst = Mat::zeros(img.size(), CV_8UC3);
	//开始处理
	if( !contours.empty() && !hierarchy.empty() )
	{
		//遍历所有顶层轮廓，随机生成颜色值绘制给各连接组成部分
		int idx = 0;
		for( ; idx >= 0; idx = hierarchy[idx][0] )
		{
			Scalar color( (rand()&255), (rand()&255), (rand()&255) );
			//绘制填充轮廓
			drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );
		}
	}
	//显示窗口
	imshow( "Connected Components", dst );
}


//-----------------------------------【main( )函数】--------------------------------------------
//	描述：控制台应用程序的入口函数，我们的程序从这里开始
//-----------------------------------------------------------------------------------------------
int main(  )
{
	system("color 5F");  
	//载入图片
	img = imread("1.jpg", 0);
	if( !img.data ) { printf("Oh，no，读取img图片文件错误~！ \n"); return -1; }

	//显示原图
	namedWindow( "Image", 1 );
	imshow( "Image", img );

	//创建处理窗口
	namedWindow( "Connected Components", 1 );
	//创建轨迹条
	createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );
	on_trackbar(threshval, 0);//轨迹条回调函数

	waitKey(0);
	return 0;
}
