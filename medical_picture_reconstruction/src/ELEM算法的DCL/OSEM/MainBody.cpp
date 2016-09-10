#pragma once
#include "SprsMtxOperator.h"
#include "SparseMtx.h"
#include "OSEM.h"
#include <iostream>
#include <time.h>
#include <string>
using namespace std;

//投影角度数
int AngNum = 128;

//每个角度下平行投影个数
int BinNum = 128;

//图像行数
int ImgRow = 128;

//图像列数
int ImgCol = 128;

const float EPS=2.2204e-16;//EPS的值

int main(int argc, char* argv[])
{	

	void IR(char* FileName, char* filename1,const int ddnumber);
	const int ddnumber = 5;//迭代次数
	char* FileName="Patient_00.txt";//患者数据
	char* filename1="SysMtx.txt";//系统矩阵
	IR(FileName,filename1,ddnumber);
	return 0;
}



void IR(char* FileName, char* filename1,const int ddnumber)
{
	FILE* fid = fopen(FileName, "rt+");
	static int a=0;
	float zhi;
	int c;
	while(1){
		c=fscanf(fid,"%e",&zhi);
		a++;
		if(c==-1)
		{
			
			break;
		}
	}
	fclose(fid);
	Vector newv(a-1);
	fid = fopen(FileName, "rt+");
	for(int i =0;i<newv.iNum;i++)
	{fscanf(fid,"%e ",&zhi);
	newv.setvalue(i,zhi);
	}
	cout<<"加载患者数据完成"<<endl;

	Vector img(ImgRow * ImgCol);
	img.Initilize(1.0);

	SparseMtx newsp(16384,16384,0);
	newsp.Empty();

	FILE* fid1 = fopen(filename1, "rt+");
	float row1;
	float col2;
	float num12;
	cout<<"加载标准矩阵开始加载"<<endl;
	for(int i=0;i<2506949;i++){

		fscanf(fid1,"%e %e %e",&row1,&col2,&num12);
		ELEM newelem(row1,col2,num12);
		newsp.AddElment(newelem);
		if(i%400000==0){
			cout<<"已加载完成:"<<float(i)/2506949*100<<"%"<<endl;
		}
	}
	fclose(fid1);

	cout<<"加载标准矩阵完成"<<endl;
	SprsMtxOperator suanfa;
	Vector ImgTmp(ImgRow * ImgCol);
	ImgTmp.Initilize();

	for(int ddnum=0;ddnum<ddnumber;ddnum++)
	{
		suanfa.MtxVecMultiple(newsp,img,ImgTmp);
		suanfa.Vecplus(ImgTmp,EPS);
		suanfa.VecDiv(newv,ImgTmp,ImgTmp);
		newsp.Transpose();
		//cout<<"完成Mat转置"<<endl;
		suanfa.MtxVecMultiple(newsp,ImgTmp,ImgTmp);
		newsp.Transpose();
		Vector summat(ImgRow * ImgCol);
		summat.Initilize();
		suanfa.MtxColSum(newsp,summat);
		suanfa.Vecplus(summat,EPS);
		suanfa.VecMultiple(img,ImgTmp,img);
		suanfa.VecDiv(img,summat,img);
		
		img.ShowVector();
		system("pause");
	}
}





