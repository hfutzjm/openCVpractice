#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/features2d/features2d.hpp>
#include<opencv2/nonfree/nonfree.hpp>
#include<opencv2/legacy/legacy.hpp>

using namespace std;
using namespace cv;

int main(void)
{
	Mat srcImage1 = imread("test.jpg", 1);
	Mat srcImage2 = imread("test2.jpg", 1);

	if (!srcImage1.data || !srcImage2.data)
	{
		cout<<"����ͼƬʧ��"<<endl;

		waitKey(0);
		return 0;
	}

	//ʹ��SURF�㷨����������ƥ��
	int minHessian = 1500;//hessian��ֵ
	SurfFeatureDetector detector(minHessian);//����һ������������
	vector<KeyPoint> keypoint1, keypoint2;//���������

	//Ѱ��������
	detector.detect(srcImage1, keypoint1);
	detector.detect(srcImage2, keypoint2);

	//����������
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;//���ڴ��������������ÿ������64ά
	extractor.compute(srcImage1, keypoint1, descriptors1);
	extractor.compute(srcImage2, keypoint2, descriptors2);

	//ʹ��BruteForce����ƥ��
	//ʵ����ƥ����
	BruteForceMatcher< L2<float> > matcher;
	vector<DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);

	//����ƥ����
	Mat imgMatches;
	drawMatches(srcImage1, keypoint1, srcImage2, keypoint2, matches, imgMatches);

	namedWindow("ƥ����",0);
	imshow("ƥ����",imgMatches);

	waitKey(0);
	return 0;
	
}

