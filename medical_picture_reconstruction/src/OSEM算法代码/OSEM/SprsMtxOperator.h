#pragma once
#include "SparseMtx.h"

#ifndef EPSILON
#define EPSILON       0.000000001
#endif

class SprsMtxOperator
{
public:
	SprsMtxOperator(void);
	~SprsMtxOperator(void);
 
	// 矩阵与向量相乘
	int MtxVecMultiple(const SparseMtx& Mtx, Vector& InVec, Vector& ResultVec);

	// 向量与矩阵相乘
	int VecMtxMultiple(Vector& InVec, const SparseMtx& Mtx, Vector& ResultVec);

	// 向量逐项相乘
	int VecMultiple(Vector& FirstVec, Vector& SecondVec, Vector& ResultVec);

	// 向量逐项相除
	int VecDiv(Vector& FirstVec, Vector& SecondVec, Vector& ResultVec);

	// 向量的每一项乘以一个因子
	int VecScale(Vector& FirstVec, double dScale, Vector& ResultVec);

	// 计算稀疏矩阵乘积的列和
	int MtxColSum(const SparseMtx& Mtx, Vector& ResultVec);

	void Vecplus(Vector& FirstVec,float a);//向量的每一项加上一个因子
	



	
};

