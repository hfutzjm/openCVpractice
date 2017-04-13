#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(){
	
	Mat srcImage=imread("test.jpg",0);
	namedWindow("原始图像",0);
	imshow("原始图像",srcImage);

	//将输入图像延扩到最佳尺寸，边界用0补充
	int m=getOptimalDFTSize(srcImage.rows);//行
	int n=getOptimalDFTSize(srcImage.cols);//列

	Mat padded;
	copyMakeBorder(srcImage,padded,0,m-srcImage.rows,0,n-srcImage.cols,BORDER_CONSTANT,Scalar::all(0));//行列位置容易搞混

	Mat planes[]={Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F)};

	Mat complexI;

	//将两个矩阵合并，用于存放傅里叶变换后的实部与虚部
	merge(planes,2,complexI);

	//进行傅里叶变换
	dft(complexI,complexI);

	split(complexI,planes);

	//计算副值
	magnitude(planes[0],planes[1],planes[0]);
	Mat magnitudeImage=planes[0];

	//对其进行对数尺度缩放，log(1+m)
	magnitudeImage+=Scalar::all(1);//对像素的操作，必须使用Scalar结构
	log(magnitudeImage,magnitudeImage);

	//若有奇数列或者奇数项则进行裁剪
	magnitudeImage=magnitudeImage(Rect(0,0,magnitudeImage.cols &-2,magnitudeImage.rows &-2));
    
	normalize(magnitudeImage,magnitudeImage,0,1,NORM_MINMAX);//第一次没有归一，图像是白色，说明值太大
	namedWindow("原始傅里叶变换",0);
	imshow("原始傅里叶变换",magnitudeImage);

	//中心点坐标
	int cx=magnitudeImage.cols/2;
	int cy=magnitudeImage.rows/2;
	Mat q0=magnitudeImage(Rect(0,0,cx,cy));//ROI左上区域
	Mat q1=magnitudeImage(Rect(cx,0,cx,cy));//ROI右上区域
	Mat q2=magnitudeImage(Rect(0,cy,cx,cy));//ROI左下区域
	Mat q3=magnitudeImage(Rect(cx,cy,cx,cy));//ROI右下区域

	//交换象限
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//归一化
	normalize(magnitudeImage,magnitudeImage,0,1,NORM_MINMAX);

	namedWindow("傅里叶变换频谱图",0);
	imshow("傅里叶变换频谱图",magnitudeImage);

	waitKey(0);
	return 0;
}
