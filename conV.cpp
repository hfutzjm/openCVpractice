#include<iostream>

using namespace std;

int** map0(int **arr, int n, int r)
{//将多余的行列填充为0，以进行卷积操作
    int len = n+2*r;//行，列均要扩充r
    
	//创建填充二维数组
	int **newArr = new int *[len];
	for (int i=0; i<len; i++)
	{
		newArr[i] = new int[len];//len*len的二维数组
	}
    
	//首先将数组全赋值为0
    for (int i=0;i<len;i++)
    {
        for(int j=0;j<len;j++)
        {
            newArr[i][j] = 0;
        }
    }
    
	//将原数组的相应数值填充到newArr
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            newArr[i+r][j+r] = arr[i][j];
        }
    }
    
    return newArr;
}

//卷积函数，需要输入核函数，被卷积的矩阵，卷积的坐标，卷积核大小
int conV(int **kern, int **newF, int i, int j, int r)
{
    int res=0;//卷积值

    for (int m=0; m<(2*r+1); m++)
    {
        for(int n=0; n<(2*r+1); n++)
        {
            res += kern[m][n]*newF[i+m][j+n]; //应该是newF[i+r-(r-m)][j+r-(r-n)]
        }
    }
    return res;
}

int main(void)
{
    int n;
    int r;
    cin>>n>>r;
    
    int **F = new int *[n];//输入矩阵

	for (int i=0; i<n; i++)
	{
		F[i] = new int[n];//创建2*2 矩阵F
	}

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cin>>F[i][j];
        }
    }
    
    int **ker = new int *[2*r+1];//核函数

	for (int i=0; i<(2*r+1); i++)
	{
		ker[i] = new int [2*r+1];
	}

    for(int i=0;i<2*r+1;i++)
    {
        for(int j=0;j<2*r+1;j++)
        {
            ker[i][j]=1;//核的系数均为1;
        }
    }
    
    
    int **F1 = map0(F,n,r);//填充行和列
    
    int **W = new int *[n];//储存卷积后的值

	for (int i=0; i<n; i++)
	{
		W[i] = new int[n];
	}
    
	//进行卷积
    for (int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
             W[i][j] = conV(ker, F1, i ,j, r);
             cout<<W[i][j]<<" ";
        }
		cout<<endl;
    }
    
    return 0;
}