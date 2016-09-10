#ifndef SPARSEMTX_HEADER_FILE_INCLUDED
#define SPARSEMTX_HEADER_FILE_INCLUDED
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;
#ifndef EPSILON
#define EPSILON       0.00000000001
#endif

class ELEM  //三维向量用来      估计是----保存稀疏矩阵的数据
{
public:
	int row;
	int col;
	double val;
	ELEM()  //默认构造函数0 0 0
	{
		row = 0;
		col = 0;
		val = 0;
	}
	ELEM(int i, int j, double d)//构造函数传行列值
	{
		row = i;
		col = j;
		val = d;
	}
	void operator=(ELEM t) //运算符重写=
	{
		row = t.row;
		col = t.col;
		val = t.val;
	}
	bool operator<(ELEM t)//运算符重写<
	{
		if(row < t.row)
			return true;
		else if(row == t.row && col < t.col)
		{
			return true;
		}
		else
			return false;
	}

	bool operator > (ELEM t)//运算符重写>
	{
		if(row > t.row)
			return true;
		else if(row == t.row && col > t.col)
		{
			return true;
		}
		else
			return false;
	}
		
	bool operator == (ELEM t)//运算符重写==
	{
		if(row == t.row && col == t.col)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator!=(ELEM t)//运算符重写!=
	{
		return !( *this == t );
	}

	
	bool operator>=(ELEM t)//运算符重写>=
	{	
		return ( *this > t || *this == t );
	}

	bool operator<=(ELEM t)//运算符重写<=
	{	
		return ( *this < t || *this == t );
	}
};

class Vector
{
public:
	int iNum;
	double* pdData;
		// 构造函数
	Vector(int iDimen)   //设置向量元素的个数（iDimen为个数）
	{
		iNum = iDimen;
		pdData = new double[iNum];		
	}

	// 析构函数
	~Vector()
	{
		delete[] pdData;
	}
	void Initilize()    //设置向量元素全部为0
	{
		memset(pdData, 0, iNum * sizeof(double) );
	}

	void Initilize(double dVal) //设置向量元素全部为dval
	{
		int i;
		for ( i = 0; i < iNum; i++ )
		{
			pdData[i] = dVal;
		}
	}

	double Sum() //计算全部元素的和并返回
	{
		double d = 0.0;
		for ( int i = 0; i < iNum; i++ )
		{
			d += pdData[i];
		}
		return d;	
	}

	void ShowVector()  //展示向量
	{
		int i;
		for ( i = 0; i < iNum; i++ )
		{
			printf("%f ", pdData[i] );
			cout<<endl;
		}
	
	}

	void showmyv()
	{
		int i;
		for(i = 0;i<20;i++)
		{
            printf("%f ", pdData[i] );
			cout<<endl;
		}


	}


	int SaveVector(char* pchFileName)  //保存向量到文件  //输入2进制流？？
	{
		FILE* fp;
		if ( NULL == (fp = fopen(pchFileName, "wb")) )
		{
			printf("Fail to open writen file\n");
			return (-1);
		}

		if ( iNum != fwrite(pdData, sizeof(double), iNum, fp) )
		{
			printf("Error data size\n ");
			return (-1);
		}
		return 0;
	}	

	void setvalue(int i,double value)//设置某个值(mine)
	{
		pdData[i] = value;
	
	}




};

class SparseMtx  //稀疏矩阵
{
//private:
public:
	int n_rows;
	int n_cols;
	int n_max_ELEM;
	int n_actual_ELEM;
	ELEM *items;

public:
	// 构造函数
	SparseMtx(int rows, int cols, int n_max);
	
	// 析构函数
	~SparseMtx()
	{
		free(items);
	}
	// 稀疏矩阵初始化
	void Empty();
	
	// 矩阵转置
	void Transpose();

	
	// 添加元素，添加了处理溢出的机制
	bool AddElment(ELEM e);
		
	// 对元素按行进行一次排序
	void ElemRowSort();			
	
	// 缩减稀疏矩阵存储空间到最低值
	void CutSparMtxMem();

	// 显示函数 for debugging
	void ShowElements();
	
	// 元素交换
	void MySwap(ELEM &s1, ELEM &s2);

	// 递归快速排序，注意递归算法处理大的数据容易栈溢出
	void QuickSort(ELEM* vec,int low,int high);
	// 保存到文件
	void SaveToFile(char* pchFileName);			

};														 
														 
#endif