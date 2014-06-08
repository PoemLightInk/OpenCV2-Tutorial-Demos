
//-----------------------------------������˵����----------------------------------------------
//  �������ƣ�   createTrackbar���� �ٷ�sample���� ǳī�Ż�&��ϸע�Ͱ桿
//	 ˵������OpenCV���Ž̳�֮�ġ� ����Trackbar &ͼ��Աȶȡ�����ֵ����  ���ײ���Դ��֮������ƪ��
//  VisualStudio 2010��   ʹ��OpenCV�汾��2.4.8
//	 �ٷ�ԭ��ʾ��·����opencv_source_code/samples/cpp/connected_components.cpp 
//	 ���ײ������ӣ�http://blog.csdn.net/poem_qianmo/article/details/21479533
//	 2014��3��18 �� Edited by ǳī
//	 ǳī��΢����@ǳī_ë����
//------------------------------------------------------------------------------------------------

//-----------------------------------��ͷ�ļ��������֡�---------------------------------------
//	����������������������ͷ�ļ�
//---------------------------------------------------------------------------------------------- 
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

//-----------------------------------�������ռ��������֡�---------------------------------------
//	����������������ʹ�õ������ռ�
//-----------------------------------------------------------------------------------------------   
using namespace cv;
using namespace std;

//-----------------------------------��ȫ�ֺ����������֡�--------------------------------------
//	������ȫ�ֺ�������
//-----------------------------------------------------------------------------------------------
Mat img;
int threshval = 160;			//�켣�������Ӧ��ֵ������ֵ160

//-----------------------------��on_trackbar( )������------------------------------------
//	�������켣���Ļص�����
//-----------------------------------------------------------------------------------------------
static void on_trackbar(int, void*)
{
	Mat bw = threshval < 128 ? (img < threshval) : (img > threshval);

	//����������
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//��������
	findContours( bw, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );
	//��ʼ��dst
	Mat dst = Mat::zeros(img.size(), CV_8UC3);
	//��ʼ����
	if( !contours.empty() && !hierarchy.empty() )
	{
		//�������ж������������������ɫֵ���Ƹ���������ɲ���
		int idx = 0;
		for( ; idx >= 0; idx = hierarchy[idx][0] )
		{
			Scalar color( (rand()&255), (rand()&255), (rand()&255) );
			//�����������
			drawContours( dst, contours, idx, color, CV_FILLED, 8, hierarchy );
		}
	}
	//��ʾ����
	imshow( "Connected Components", dst );
}


//-----------------------------------��main( )������--------------------------------------------
//	����������̨Ӧ�ó������ں��������ǵĳ�������￪ʼ
//-----------------------------------------------------------------------------------------------
int main(  )
{
	system("color 5F");  
	//����ͼƬ
	img = imread("1.jpg", 0);
	if( !img.data ) { printf("Oh��no����ȡimgͼƬ�ļ�����~�� \n"); return -1; }

	//��ʾԭͼ
	namedWindow( "Image", 1 );
	imshow( "Image", img );

	//����������
	namedWindow( "Connected Components", 1 );
	//�����켣��
	createTrackbar( "Threshold", "Connected Components", &threshval, 255, on_trackbar );
	on_trackbar(threshval, 0);//�켣���ص�����

	waitKey(0);
	return 0;
}
