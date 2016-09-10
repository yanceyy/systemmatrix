#pragma once
#include "SprsMtxOperator.h"
#include "SparseMtx.h"
#include "OSEM.h"
#include <iostream>
#include <time.h>
#include <string>
using namespace std;

//Í¶Ó°½Ç¶ÈÊý
int AngNum = 128;

//Ã¿¸ö½Ç¶ÈÏÂÆ½ÐÐÍ¶Ó°¸öÊý
int BinNum = 128;
//Í¼ÏñÐÐÊý
int ImgRow = 128;

//Í¼ÏñÁÐÊý
int ImgCol = 128;

const float EPS=2.2204e-16;//EPSµÄÖµ

int main(int argc, char* argv[])
{	

	void IR(char* FileName, char* filename1,const int ddnumber);
	const int ddnumber = 5;//µü´ú´ÎÊý
	char* FileName="Patient_01.txt";//»¼ÕßÊý¾Ý
	char* filename1="aa.txt";//ÏµÍ³¾ØÕó
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
	//cout<<(a-1)/2;
	Vector prenewv((a-1)/2);
	Vector aftnewv((a-1)/2);
	fid = fopen(FileName, "rt+");
	for(int i =0;i<prenewv.iNum;i++)
	{fscanf(fid,"%e ",&zhi);
	prenewv.setvalue(i,zhi);
	fscanf(fid,"%e ",&zhi);
	aftnewv.setvalue(i,zhi);
	}
	cout<<"已加载完患者数据"<<endl;

	Vector img(ImgRow * ImgCol);
	img.Initilize(1.0);

	SparseMtx prenewsp(16384/2,16384,0);
	SparseMtx afternewsp(16384/2,16384,0);
	prenewsp.Empty();
	afternewsp.Empty();
	FILE* fid1 = fopen(filename1, "rt+");
	float row1;
	float col2;
	float num12;
	cout<<""<<endl;
	while(1){
        
		int canreadnum=0;
		canreadnum=fscanf(fid1,"%e %e %e",&row1,&col2,&num12);
		//cout<<canreadnum;
		if(canreadnum != 3){
			break;
		}
		//ELEM newelem(row1-1,col2-1,num12);
		if(int(row1)%2==0)
		{ELEM newelem(row1/2-1,col2-1,num12);
		afternewsp.AddElment(newelem);

		
		}
		else{
		ELEM newelem((row1-1)/2,col2-1,num12);
		prenewsp.AddElment(newelem);
		}
		/*if(i%400000==0){
			cout<<"ÒÑ¼ÓÔØÍê³É:"<<float(i)/2506949*100<<"%"<<endl;
		}*/
	}
	fclose(fid1);

	cout<<"已加载完系统矩阵"<<endl;
	SprsMtxOperator suanfa;
	Vector ImgTmp(ImgRow * ImgCol/2);
	ImgTmp.Initilize();
	Vector ImgTmp1(ImgRow * ImgCol);
	ImgTmp1.Initilize();
	for(int ddnum=0;ddnum<ddnumber;ddnum++)
	{
		suanfa.MtxVecMultiple(prenewsp,img,ImgTmp);
		suanfa.Vecplus(ImgTmp,EPS);
	    suanfa.VecDiv(prenewv,ImgTmp,ImgTmp);
		prenewsp.Transpose();
		//cout<<"Íê³ÉMat×ªÖÃ"<<endl;
	    suanfa.MtxVecMultiple(prenewsp,ImgTmp,ImgTmp1);
		prenewsp.Transpose();
		Vector summat(ImgRow * ImgCol);
		summat.Initilize();
		suanfa.MtxColSum(prenewsp,summat);
		suanfa.Vecplus(summat,EPS);
		suanfa.VecMultiple(img,ImgTmp1,img);
		suanfa.VecDiv(img,summat,img);
		
		suanfa.MtxVecMultiple(afternewsp,img,ImgTmp);
		suanfa.Vecplus(ImgTmp,EPS);
		suanfa.VecDiv(aftnewv,ImgTmp,ImgTmp);
		afternewsp.Transpose();
		//cout<<"Íê³ÉMat×ªÖÃ"<<endl;
		suanfa.MtxVecMultiple(afternewsp,ImgTmp,ImgTmp1);
		afternewsp.Transpose();
		//Vector summat(ImgRow * ImgCol);
		summat.Initilize();
		suanfa.MtxColSum(afternewsp,summat);
		suanfa.Vecplus(summat,EPS);
		suanfa.VecMultiple(img,ImgTmp1,img);
		suanfa.VecDiv(img,summat,img);
		img.ShowVector();
		//cout<<img.iNum;
		system("pause");
	}
}





