#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

int main(){
	
	Mat srcImage=imread("test.jpg",0);
	namedWindow("ԭʼͼ��",0);
	imshow("ԭʼͼ��",srcImage);

	//������ͼ����������ѳߴ磬�߽���0����
	int m=getOptimalDFTSize(srcImage.rows);//��
	int n=getOptimalDFTSize(srcImage.cols);//��

	Mat padded;
	copyMakeBorder(srcImage,padded,0,m-srcImage.rows,0,n-srcImage.cols,BORDER_CONSTANT,Scalar::all(0));//����λ�����׸��

	Mat planes[]={Mat_<float>(padded),Mat::zeros(padded.size(),CV_32F)};

	Mat complexI;

	//����������ϲ������ڴ�Ÿ���Ҷ�任���ʵ�����鲿
	merge(planes,2,complexI);

	//���и���Ҷ�任
	dft(complexI,complexI);

	split(complexI,planes);

	//���㸱ֵ
	magnitude(planes[0],planes[1],planes[0]);
	Mat magnitudeImage=planes[0];

	//������ж����߶����ţ�log(1+m)
	magnitudeImage+=Scalar::all(1);//�����صĲ���������ʹ��Scalar�ṹ
	log(magnitudeImage,magnitudeImage);

	//���������л�������������вü�
	magnitudeImage=magnitudeImage(Rect(0,0,magnitudeImage.cols &-2,magnitudeImage.rows &-2));
    
	normalize(magnitudeImage,magnitudeImage,0,1,NORM_MINMAX);//��һ��û�й�һ��ͼ���ǰ�ɫ��˵��ֵ̫��
	namedWindow("ԭʼ����Ҷ�任",0);
	imshow("ԭʼ����Ҷ�任",magnitudeImage);

	//���ĵ�����
	int cx=magnitudeImage.cols/2;
	int cy=magnitudeImage.rows/2;
	Mat q0=magnitudeImage(Rect(0,0,cx,cy));//ROI��������
	Mat q1=magnitudeImage(Rect(cx,0,cx,cy));//ROI��������
	Mat q2=magnitudeImage(Rect(0,cy,cx,cy));//ROI��������
	Mat q3=magnitudeImage(Rect(cx,cy,cx,cy));//ROI��������

	//��������
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);

	//��һ��
	normalize(magnitudeImage,magnitudeImage,0,1,NORM_MINMAX);

	namedWindow("����Ҷ�任Ƶ��ͼ",0);
	imshow("����Ҷ�任Ƶ��ͼ",magnitudeImage);

	waitKey(0);
	return 0;
}
