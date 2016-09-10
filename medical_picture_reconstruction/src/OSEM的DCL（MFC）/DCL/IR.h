#include "SprsMtxOperator.h"
//SparseMtx newsp(16384,16384,2506949);
SparseMtx prenewsp(16384/2,16384,0);
SparseMtx afternewsp(16384/2,16384,0);
Vector ImgTmp(ImgRow * ImgCol/2);
Vector ImgTmp1(ImgRow * ImgCol);
Vector img(ImgRow * ImgCol);
SparseMtx result(ImgRow,ImgCol,img.iNum);
Vector prenewv(8192);
Vector aftnewv(8192);
static int pyes=0;
const float EPS=0;//EPS的值

void IR(CString FileName, CString filename1,const int ddnumber,Vector& resultvector)
{ 
	if(yesshow ==0)
	{

		//if(fid !=NULL)

		static int a;
		a=16385;
		float abcd;
		//int c;
		FILE* fid;
		_tfopen_s(&fid,FileName,_T("rt+"));
		for(int i =0;i<prenewv.iNum;i++)
		{fscanf(fid,"%e ",&abcd);
		prenewv.setvalue(i,abcd);
		fscanf(fid,"%e ",&abcd);
		aftnewv.setvalue(i,abcd);

		}
		fclose(fid);
	}


	if(pyes == 0)
	{
		FILE* fid1;
		_tfopen_s(&fid1,filename1,_T("rt+"));
		float row1;
		float col2;
		float num12;
		//cout<<"加载标准矩阵开始加载"<<endl;
		while(1){

			int canreadnum=0;
			canreadnum=fscanf_s(fid1,"%e %e %e",&row1,&col2,&num12);
			if(canreadnum != 3){
				break;
			}
			if(int(row1)%2==0)
			{ELEM newelem(row1/2-1,col2-1,num12);
			afternewsp.AddElment(newelem);


			}
			else{
				ELEM newelem((row1-1)/2,col2-1,num12);
				prenewsp.AddElment(newelem);
			}
			
		}
		fclose(fid1);
			pyes = 1;
	}
		SprsMtxOperator suanfa;
		suanfa.MtxVecMultiple(prenewsp,img,ImgTmp);
		suanfa.Vecplus(ImgTmp,EPS);
		suanfa.VecDiv(prenewv,ImgTmp,ImgTmp);
		prenewsp.Transpose();
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
		suanfa.MtxVecMultiple(afternewsp,ImgTmp,ImgTmp1);
		afternewsp.Transpose();
		summat.Initilize();
		suanfa.MtxColSum(afternewsp,summat);
		suanfa.Vecplus(summat,EPS);
		suanfa.VecMultiple(img,ImgTmp1,img);
		suanfa.VecDiv(img,summat,img);
		int i;
		for ( i = 0; i < img.iNum; i++ )
		{
			resultvector.pdData[i]=img.pdData[i];
			int wdad=img.pdData[i];
		}
		suanfa.reshape(img,ImgRow,ImgCol,result);
	}
