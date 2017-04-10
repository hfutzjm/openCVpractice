#include<iostream>
#include<cassert>
#include"Mat.h"

using namespace std;

ostream& operator<<(ostream &os, const Mat &m)
{//该函数为Mat类的友元函数，因此可以访问Mat的private成员变量
	for (size_t i=0; i<m.rows; i++)
	{
		for (size_t j=0; j<m.cols; j++)
		{
			os << m.data[i][j] << " ";
		}
		os << endl;
	}
	os << endl;

	return os;
}

istream& operator>>(istream &is, Mat &m)
{
	for (size_t i=0; i<m.rows; i++)
	{
		for (size_t j=0; j<m.cols; j++)
		{
			is >> m.data[i][j];
		}
	}
	return is;
}

 Mat const operator+(const Mat &m1, const Mat &m2)
{
	Mat tmp = m1;
	tmp += m2;
	return tmp;
}

const Mat operator-(const Mat &m1, const Mat &m2)
{
	Mat tmp = m1;
	tmp -= m2;
	return tmp;
}
Mat::Mat()
{
	rows = 0;
	cols = 0;
	data.clear();
}

Mat::Mat(size_t i, size_t j)
{
	rows = i;
	cols = j;

	vector<vector<int>> temdata(rows, vector<int>(cols,0));
	data=temdata;
}

Mat::Mat(const Mat &m)
{
	rows = m.rows;
	cols = m.cols;
	data = m.data;
}

Mat& Mat::operator=(const Mat &m)
{
	rows = m.rows;
	cols = m.cols;
	data = m.data;
	
	return *this;
}

Mat& Mat::operator+=(const Mat &m)
{
	if(rows==m.rows && cols==m.cols)
	{
	  for (size_t i=0; i<m.rows; i++)
	  {
		for (size_t j=0; j<m.cols; j++)
		{
			data[i][j]+=m.data[i][j];
		}
	  }
	}
	else
	{
		cout<<"mat must have the same size"<<endl;
	}
	return *this;
	
}

Mat& Mat::operator-=(const Mat &m)
{
	if(rows==m.rows && cols==m.cols)
	{
	  for (size_t i=0; i<m.rows; i++)
	  {
		for (size_t j=0; j<m.cols; j++)
		{
			data[i][j]-=m.data[i][j];
		}
	  }
	}
	else
	{
		cout<<"mat must have the same size"<<endl;
	}
	return *this;
	
}

int& Mat::operator()(size_t i, size_t j)
{
	assert(i>=0 && j>=0 && i<rows && j<cols);
	return data[i][j];
}