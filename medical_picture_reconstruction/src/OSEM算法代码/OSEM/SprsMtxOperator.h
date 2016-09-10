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
 
	// �������������
	int MtxVecMultiple(const SparseMtx& Mtx, Vector& InVec, Vector& ResultVec);

	// ������������
	int VecMtxMultiple(Vector& InVec, const SparseMtx& Mtx, Vector& ResultVec);

	// �����������
	int VecMultiple(Vector& FirstVec, Vector& SecondVec, Vector& ResultVec);

	// �����������
	int VecDiv(Vector& FirstVec, Vector& SecondVec, Vector& ResultVec);

	// ������ÿһ�����һ������
	int VecScale(Vector& FirstVec, double dScale, Vector& ResultVec);

	// ����ϡ�����˻����к�
	int MtxColSum(const SparseMtx& Mtx, Vector& ResultVec);

	void Vecplus(Vector& FirstVec,float a);//������ÿһ�����һ������
	



	
};

