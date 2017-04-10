#ifndef MAT_H
#define MAT_H

#include<iostream>
#include<vector>

using namespace std;

class Mat
{
	//�����������
	friend ostream &operator<<(ostream &os, const Mat &m);
	//���뺯������
	friend istream &operator>>(istream &is, Mat &m);

	friend const Mat operator+(const Mat &m1, const Mat &m2);//�ǳ�Ա���������غ�������Ҫ����Ϊ�����Ԫ����
	friend const Mat operator-(const Mat &m1, const Mat &m2);

public:
	Mat();
	Mat(size_t i, size_t j);
	Mat(const Mat &m);
	Mat& operator=(const Mat &m);

	Mat& operator+=(const Mat &m);
	Mat& operator-=(const Mat &m);

	~Mat(){};

	int& operator()(size_t i, size_t j);

	size_t Rows()
	{
		return rows;
	}

	size_t Cols()
	{
		return cols;
	}


private:
	size_t rows;
	size_t cols;
	vector<vector<int>> data;

};

#endif