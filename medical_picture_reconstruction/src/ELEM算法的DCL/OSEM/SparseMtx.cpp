#pragma once
#include "stdafx.h"
#include "SparseMtx.h"
#include<iostream> 
#include<vector> 
#include<stack> 
#include<cstdlib> 
#include<algorithm>
#include <memory.h>
using namespace std;

static bool is_debugging = false;
#ifndef SPAR_MTX_LEN
#define SPAR_MTX_LEN 2000000
#endif
SparseMtx::SparseMtx(int rows, int cols, int n_max) 
{
	this->n_rows = rows;
	this->n_cols = cols;
	this->n_max_ELEM = n_max;
	this->n_actual_ELEM = 0; 
	this->items = (ELEM*) malloc( n_max_ELEM * sizeof(ELEM) );
	if ( NULL == this->items )
	{
		printf("ϡ������캯�������ڴ�ռ�ʧ��\n");
	}
}
void SparseMtx::MySwap(ELEM &s1, ELEM &s2)
{
	ELEM t = s1;
	s1 = s2;
	s2 = t;
}


void SparseMtx::QuickSort(ELEM* arr, int left, int right)
{
	// keyλ�úͶ�Ӧ��ֵ
	int key_pos = left;
	ELEM key_value = arr[key_pos];

	// ѭ��������Χ
	int i=left;
	int j=right;

	// һ�ο�������
	while(i < j)
	{
		// �������ң�����key�ͻ���
		while(arr[i]<key_value && i<right)
			i++;
		if (i<j)
		{
			MySwap(arr[i], arr[key_pos]);
			key_pos = i;
		}


		// ��������С��key�ͻ���
		while(arr[j]>key_value && j>left)
			j--;
		if (i<j)
		{
			MySwap(arr[j], arr[key_pos]);
			key_pos = j;
		}
	}

	// �ݹ���ã�key�����������Ӽ�����һ�ο�������
	if(key_pos>left)
	{
		QuickSort(arr,left,key_pos-1);
	}
	if(key_pos<right)
	{
		QuickSort(arr,key_pos+1,right);
	}
}

/************************************************************************/
/*      Ϊ������ٶȣ������˶��ظ�Ԫ���ж� 
/************************************************************************/
bool SparseMtx::AddElment(ELEM e)
{
	// check����ֹ���
	if ( e.col <0 || e.col>n_cols
		|| e.row <0 || e.row>n_rows)
	{
		printf("OverFlow when adding elements...\n");
		return false;
	}
	else if (this->n_actual_ELEM >= this->n_max_ELEM)// ��Ҫ�������
	{		
		this->n_max_ELEM += SPAR_MTX_LEN;
		printf("׷�ӷ���ռ䣬�µ�n_max_ELEM = %d\n", n_max_ELEM);
		this->items = (ELEM*) realloc(this->items, n_max_ELEM*sizeof(ELEM));	
		if ( NULL == this->items )
		{
			printf("׷�ӷ���ռ�ʧ��\n");
			exit(-1);
		}
		this->items[this->n_actual_ELEM] = e;		
		this->n_actual_ELEM++;
		
		return true;
	}
	else
	{  
		this->items[this->n_actual_ELEM] = e;	
		this->n_actual_ELEM++;
		return true;
	}	
}

void SparseMtx::ShowElements()
{
	for(int i=0; i<this->n_actual_ELEM; i++)

	{   

		printf("(%d, %d)\t%.4f\n", this->items[i].row, this->items[i].col, this->items[i].val);
	}
}

// �ֳ������֣����Ȱ����е㰴�����У�����ÿ���н�������
void SparseMtx::ElemRowSort()
{
	int i, j;
	int iRowNum;
	int iColNum;
	int iTotElemNum;
	ELEM e;
	iRowNum = this->n_rows;
	iColNum = this->n_cols;
	iTotElemNum = this-> n_actual_ELEM;
	
	int* piRowElemNum = new int[iRowNum];
	int* piStartPos = new int[iRowNum];
	int* piStartPosCopy = new int[iRowNum];
	double* pdMem = new double[iColNum];
  
	ELEM* NewItem = new ELEM[iTotElemNum];

	if ( iTotElemNum > 0 ) 
	{ 
		memset( piRowElemNum, 0, iRowNum * sizeof(int) );
		memset( piStartPos, 0, iRowNum * sizeof(int) );
	}
	else
	{
		printf("������û��Ԫ��!\n");
		return;
	}
    
       
	for (i = 0; i < iTotElemNum; i++) 
	{
		piRowElemNum[this->items[i].row]++; //ͳ�Ƶ���Ԫ�صĸ���
	}
	/**//*�����ŵ�ַ*/
	piStartPos[0] = 0;
	for (i = 1; i < iRowNum; i++) 
	{
		piStartPos[i] = piStartPos[i - 1] + piRowElemNum[i - 1];
	}
	
	
	
	// ���Ȱ��д�����ʹ��ͬ�е���������
	memcpy( piStartPosCopy, piStartPos, iRowNum * sizeof(int) );

	for ( i = 0; i < iTotElemNum; i++ ) 
	{
		j = piStartPos[this->items[i].row]; 
		NewItem[j] = this->items[i];		
		piStartPos[this->items[i].row]++;
	}
	// ��ÿһ���µ�����Ԫ�ؽ�������
	
	this->Empty();
	for ( i = 0; i < iRowNum; i++ )
	{
		memset(pdMem, 0, iColNum * sizeof(double) );
		if ( 0 == piRowElemNum[i] )
		{
			continue;
		}
		// ����
		for ( j = piStartPosCopy[i]; j < piStartPosCopy[i] + piRowElemNum[i]; j++ )
		{			
			pdMem[NewItem[j].col] = NewItem[j].val;			
		}
		for ( j = 0; j < iColNum; j++ )
		{
			if ( pdMem[j] > EPSILON )
			{
				e.row = i;
				e.col = j;
				e.val = pdMem[j];
				this->AddElment(e);
			}
		}
	}

	delete[] pdMem;
	delete[] piRowElemNum;
	delete[] piStartPos;
	delete[] piStartPosCopy;
	delete NewItem;

}

void SparseMtx::SaveToFile(char* pchFileName)
{
	int i;
	FILE* fp = fopen(pchFileName, "w+");
	if ( NULL == fp )
	{
		printf("Cannot open file %s\n",pchFileName);
		return;
	}
	
	for( i=0; i< this->n_actual_ELEM; i++)
	{
		fprintf(fp, "%d\t%d\t%f\n", this->items[i].row, this->items[i].col, this->items[i].val);
	}	
	fclose(fp);
}





void SparseMtx::Empty()
{
	for(int i=0; i < this->n_max_ELEM ; i++)
	{
		this->items[i].col   = -1;
		this->items[i].row  = -1;
		this->items[i].val   = -1;
	}
	this->n_actual_ELEM = 0;
}

void SparseMtx::CutSparMtxMem()
{
	this->items = (ELEM*) realloc(items, this->n_actual_ELEM*sizeof(ELEM));
}

/**//*����ת���㷨*/
void SparseMtx::Transpose()
{	
	int i, j;
	int iRowNum;
	int iColNum;
	int iTotElemNum;
	iRowNum = this->n_rows;
	iColNum = this->n_cols;
	iTotElemNum =this-> n_actual_ELEM;
	
	int* piColElemNum = new int[iColNum];
	int* piStartPos = new int[iColNum];
	ELEM* NewItem = new ELEM[iTotElemNum];
  
	if ( iTotElemNum > 0 ) 
	{ 
		memset( piColElemNum, 0, iColNum * sizeof(int) );
		memset( piStartPos, 0, iColNum * sizeof(int) );
	}
	else
	{
		printf("������û��Ԫ��!\n");
		return;
	}
    
       
	for (i = 0; i < iTotElemNum; i++) 
	{
		piColElemNum[this->items[i].col]++; //ͳ�Ƶ�i�е�����Ԫ�ظ���
	}
	/**//*�����ŵ�ַ*/
	piStartPos[0] = 0;
	for (i = 1; i < iColNum; i++) 
	{
		piStartPos[i] = piStartPos[i - 1] + piColElemNum[i - 1];
	}
	/**//*���*/
	for (i = 0; i < iTotElemNum; i++) 
	{
		j = piStartPos[this->items[i].col]; // ʹ��j����һ����ַ
		NewItem[j].row = this->items[i].col;
		NewItem[j].col = this->items[i].row;
		NewItem[j].val = this->items[i].val;
		piStartPos[this->items[i].col]++;
	}
	for (i = 0; i < iTotElemNum; i++) 
	{
		this->items[i] = NewItem[i];
	}

	i = this->n_rows;
	this->n_rows = this->n_cols;
	this->n_cols = i;

	delete[] piColElemNum;
	delete[] piStartPos;
	delete NewItem;
}
