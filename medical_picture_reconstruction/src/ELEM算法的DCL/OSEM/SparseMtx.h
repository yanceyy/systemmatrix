#ifndef SPARSEMTX_HEADER_FILE_INCLUDED
#define SPARSEMTX_HEADER_FILE_INCLUDED
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;
#ifndef EPSILON
#define EPSILON       0.00000000001
#endif

class ELEM  //��ά��������      ������----����ϡ����������
{
public:
	int row;
	int col;
	double val;
	ELEM()  //Ĭ�Ϲ��캯��0 0 0
	{
		row = 0;
		col = 0;
		val = 0;
	}
	ELEM(int i, int j, double d)//���캯��������ֵ
	{
		row = i;
		col = j;
		val = d;
	}
	void operator=(ELEM t) //�������д=
	{
		row = t.row;
		col = t.col;
		val = t.val;
	}
	bool operator<(ELEM t)//�������д<
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

	bool operator > (ELEM t)//�������д>
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
		
	bool operator == (ELEM t)//�������д==
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

	bool operator!=(ELEM t)//�������д!=
	{
		return !( *this == t );
	}

	
	bool operator>=(ELEM t)//�������д>=
	{	
		return ( *this > t || *this == t );
	}

	bool operator<=(ELEM t)//�������д<=
	{	
		return ( *this < t || *this == t );
	}
};

class Vector
{
public:
	int iNum;
	double* pdData;
		// ���캯��
	Vector(int iDimen)   //��������Ԫ�صĸ�����iDimenΪ������
	{
		iNum = iDimen;
		pdData = new double[iNum];		
	}

	// ��������
	~Vector()
	{
		delete[] pdData;
	}
	void Initilize()    //��������Ԫ��ȫ��Ϊ0
	{
		memset(pdData, 0, iNum * sizeof(double) );
	}

	void Initilize(double dVal) //��������Ԫ��ȫ��Ϊdval
	{
		int i;
		for ( i = 0; i < iNum; i++ )
		{
			pdData[i] = dVal;
		}
	}

	double Sum() //����ȫ��Ԫ�صĺͲ�����
	{
		double d = 0.0;
		for ( int i = 0; i < iNum; i++ )
		{
			d += pdData[i];
		}
		return d;	
	}

	void ShowVector()  //չʾ����
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


	int SaveVector(char* pchFileName)  //�����������ļ�  //����2����������
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

	void setvalue(int i,double value)//����ĳ��ֵ(mine)
	{
		pdData[i] = value;
	
	}




};

class SparseMtx  //ϡ�����
{
//private:
public:
	int n_rows;
	int n_cols;
	int n_max_ELEM;
	int n_actual_ELEM;
	ELEM *items;

public:
	// ���캯��
	SparseMtx(int rows, int cols, int n_max);
	
	// ��������
	~SparseMtx()
	{
		free(items);
	}
	// ϡ������ʼ��
	void Empty();
	
	// ����ת��
	void Transpose();

	
	// ���Ԫ�أ�����˴�������Ļ���
	bool AddElment(ELEM e);
		
	// ��Ԫ�ذ��н���һ������
	void ElemRowSort();			
	
	// ����ϡ�����洢�ռ䵽���ֵ
	void CutSparMtxMem();

	// ��ʾ���� for debugging
	void ShowElements();
	
	// Ԫ�ؽ���
	void MySwap(ELEM &s1, ELEM &s2);

	// �ݹ��������ע��ݹ��㷨��������������ջ���
	void QuickSort(ELEM* vec,int low,int high);
	// ���浽�ļ�
	void SaveToFile(char* pchFileName);			

};														 
														 
#endif