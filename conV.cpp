#include<iostream>

using namespace std;

int** map0(int **arr, int n, int r)
{//��������������Ϊ0���Խ��о������
    int len = n+2*r;//�У��о�Ҫ����r
    
	//��������ά����
	int **newArr = new int *[len];
	for (int i=0; i<len; i++)
	{
		newArr[i] = new int[len];//len*len�Ķ�ά����
	}
    
	//���Ƚ�����ȫ��ֵΪ0
    for (int i=0;i<len;i++)
    {
        for(int j=0;j<len;j++)
        {
            newArr[i][j] = 0;
        }
    }
    
	//��ԭ�������Ӧ��ֵ��䵽newArr
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            newArr[i+r][j+r] = arr[i][j];
        }
    }
    
    return newArr;
}

//�����������Ҫ����˺�����������ľ��󣬾�������꣬����˴�С
int conV(int **kern, int **newF, int i, int j, int r)
{
    int res=0;//���ֵ

    for (int m=0; m<(2*r+1); m++)
    {
        for(int n=0; n<(2*r+1); n++)
        {
            res += kern[m][n]*newF[i+m][j+n]; //Ӧ����newF[i+r-(r-m)][j+r-(r-n)]
        }
    }
    return res;
}

int main(void)
{
    int n;
    int r;
    cin>>n>>r;
    
    int **F = new int *[n];//�������

	for (int i=0; i<n; i++)
	{
		F[i] = new int[n];//����2*2 ����F
	}

    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cin>>F[i][j];
        }
    }
    
    int **ker = new int *[2*r+1];//�˺���

	for (int i=0; i<(2*r+1); i++)
	{
		ker[i] = new int [2*r+1];
	}

    for(int i=0;i<2*r+1;i++)
    {
        for(int j=0;j<2*r+1;j++)
        {
            ker[i][j]=1;//�˵�ϵ����Ϊ1;
        }
    }
    
    
    int **F1 = map0(F,n,r);//����к���
    
    int **W = new int *[n];//���������ֵ

	for (int i=0; i<n; i++)
	{
		W[i] = new int[n];
	}
    
	//���о��
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