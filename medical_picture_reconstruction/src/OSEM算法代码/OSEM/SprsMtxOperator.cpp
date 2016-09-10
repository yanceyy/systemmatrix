#include "SprsMtxOperator.h"
#include "SparseMtx.h"
#include <iostream>

SprsMtxOperator::SprsMtxOperator(void)
{
}


SprsMtxOperator::~SprsMtxOperator(void)
{
}

// 矩阵乘以向量
int SprsMtxOperator::MtxVecMultiple(const SparseMtx& Mtx, Vector& InVec, Vector& ResultVec)
{
	int i;
	int iRowNum;
	int iColNum;
	int iTotElemNum;
	int iVecNum;
	
	iRowNum = Mtx.n_rows;
	iColNum = Mtx.n_cols;
	iTotElemNum = Mtx.n_actual_ELEM;
	iVecNum = InVec.iNum;
	
	if ( iColNum != iVecNum  || iRowNum != ResultVec.iNum )
	{   cout<<iColNum<<"  "<<iVecNum<<endl;
	    cout<<iRowNum<<" "<<ResultVec.iNum<<endl;;
		printf("Dimensions of matrix and vector mismatch\n");
		return (-1);
	}
	
	Vector NewVector(iRowNum);
	NewVector.Initilize();
		
	for ( i = 0; i < iTotElemNum; i++ )  //iTotElemNum是2506949 iRowNum是16384 row的最大是为16384 col的最大是为16384 pdData最大值为16384
	{   // cout<<NewVector.pdData[Mtx.items[i].row-1]<<"+";
		NewVector.pdData[Mtx.items[i].row] += Mtx.items[i].val*InVec.pdData[Mtx.items[i].col];



		//cout<<Mtx.items[i].val<<"*"<<InVec.pdData[Mtx.items[i].col-1]<<"="<<NewVector.pdData[Mtx.items[i].row-1]<<endl;
	}
	//cout<<Mtx.items[i].val<<"*"<<InVec.pdData[Mtx.items[i].col-1]<<"="<<NewVector.pdData[Mtx.items[i].row-1]<<endl;
	for ( i = 0; i < ResultVec.iNum; i++ )
	{
		ResultVec.pdData[i] = NewVector.pdData[i];
	}	
	return 0;	
}

// 向量乘以矩阵,该乘法也可是使用矩阵转置和MtxVecMultiple函数实现，
// 但是考虑到系统矩阵太大，矩阵转置消耗内存，因此不使用
int SprsMtxOperator::VecMtxMultiple(Vector& InVec, const SparseMtx& Mtx, Vector& ResultVec)
{
	int i;
	int iRowNum;
	int iColNum;
	int iTotElemNum;
	int iVecNum;

	iRowNum = Mtx.n_rows;
	iColNum = Mtx.n_cols;
	iTotElemNum = Mtx.n_actual_ELEM;
	iVecNum = InVec.iNum;
	
	if ( iRowNum != iVecNum  || iColNum != ResultVec.iNum )
	{
		printf("Dimensions of matrix and vector mismatch\n");
		return (-1);
	}

	Vector NewVector(iColNum);
	NewVector. Initilize();
		
	for ( i = 0; i < iTotElemNum; i++ )
	{
		NewVector.pdData[Mtx.items[i].col] += Mtx.items[i].val * InVec.pdData[Mtx.items[i].row];
	}

	for ( i = 0; i < ResultVec.iNum; i++ )
	{
		ResultVec.pdData[i] = NewVector.pdData[i];
	}	
	return 0;	
}

int SprsMtxOperator::VecMultiple(Vector& FirstVec, Vector& SecondVec, Vector& ResultVec)
{
	int i, iFirstNum, iSecondNum;
	iFirstNum = FirstVec.iNum;
	iSecondNum = SecondVec.iNum;
	
	if ( ResultVec.iNum != iFirstNum || ResultVec.iNum != iSecondNum )
	{
		printf("Dimensions of two vectors mismatch\n");
		return (-1);
	}
	Vector NewVec(iFirstNum);
	NewVec.Initilize();
	for ( i = 0; i < iFirstNum; i++ )
	{
		NewVec.pdData[i] = FirstVec.pdData[i] * SecondVec.pdData[i];
	}
	for ( i = 0; i < ResultVec.iNum; i++ )
	{
		ResultVec.pdData[i] = NewVec.pdData[i];
	}		
	return 0;
}

int SprsMtxOperator::VecDiv(Vector& FirstVec, Vector& SecondVec, Vector& ResultVec)
{
	int i, iFirstNum, iSecondNum;
	iFirstNum = FirstVec.iNum;
	iSecondNum = SecondVec.iNum;
	
	if ( iFirstNum != iSecondNum )
	{
		printf("Dimensions of two vectors mismatch\n");
		return (-1);
	}
	Vector NewVec(iFirstNum);
	NewVec.Initilize();
	for ( i = 0; i < iFirstNum; i++ )
	{
		NewVec.pdData[i] = FirstVec.pdData[i] / ( SecondVec.pdData[i] + EPSILON );
	}
	for ( i = 0; i < ResultVec.iNum; i++ )
	{
		ResultVec.pdData[i] = NewVec.pdData[i];
	}	
	return 0;
}


void  SprsMtxOperator::Vecplus(Vector& FirstVec,float a)
{

	int i, iNum;
	iNum = FirstVec.iNum;
	for ( i = 0; i < iNum; i++ )
	{
		FirstVec.pdData[i] +=a;
	}



}


// 向量与一个数相乘
int SprsMtxOperator::VecScale(Vector& InVec, double dScale, Vector& ResultVec)
{
	int i, iNum;
	iNum = InVec.iNum;
	if ( ResultVec.iNum != iNum )
	{
		printf("Dim of output does not equal to input\n");
		return (-1);
	}

	Vector NewVec(iNum);
	NewVec.Initilize();
	for ( i = 0; i < iNum; i++ )
	{
		NewVec.pdData[i] = InVec.pdData[i] * dScale;
	}
	for ( i = 0; i < iNum; i++ )
	{
		ResultVec.pdData[i] = NewVec.pdData[i];
	}	
	return 0;
}

// 计算稀疏矩阵乘积的列和
int SprsMtxOperator::MtxColSum(const SparseMtx& Mtx, Vector& ResultVec)
{
	int i;
	int iRowNum;
	int iColNum;
	int iTotElemNum;
	iRowNum = Mtx.n_rows;
	iColNum = Mtx.n_cols;
	iTotElemNum = Mtx.n_actual_ELEM;
	if ( iColNum != ResultVec.iNum )
	{
		printf("Result vector has error length\n");
		return (-1);
	} 
	ResultVec.Initilize();
	for ( i = 0; i < iTotElemNum; i++ )
	{
		ResultVec.pdData[Mtx.items[i].col] += Mtx.items[i].val;
	}
	return 0;
}

