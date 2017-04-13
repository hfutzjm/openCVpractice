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
		cout<<"载入图片失败"<<endl;

		waitKey(0);
		return 0;
	}

	//使用SURF算法进行特征点匹配
	int minHessian = 1500;//hessian阈值
	SurfFeatureDetector detector(minHessian);//创建一个特征点检测器
	vector<KeyPoint> keypoint1, keypoint2;//存放特征点

	//寻找特征点
	detector.detect(srcImage1, keypoint1);
	detector.detect(srcImage2, keypoint2);

	//计算描述子
	SurfDescriptorExtractor extractor;
	Mat descriptors1, descriptors2;//用于存放描述子向量，每个向量64维
	extractor.compute(srcImage1, keypoint1, descriptors1);
	extractor.compute(srcImage2, keypoint2, descriptors2);

	//使用BruteForce进行匹配
	//实例化匹配器
	BruteForceMatcher< L2<float> > matcher;
	vector<DMatch> matches;
	matcher.match(descriptors1, descriptors2, matches);

	//绘制匹配结果
	Mat imgMatches;
	drawMatches(srcImage1, keypoint1, srcImage2, keypoint2, matches, imgMatches);

	namedWindow("匹配结果",0);
	imshow("匹配结果",imgMatches);

	waitKey(0);
	return 0;
	
}

