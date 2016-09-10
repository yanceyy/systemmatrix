#include "SprsMtxOperator.h"
SparseMtx newsp(16384,16384,2506949);
Vector ImgTmp(ImgRow * ImgCol);
Vector img(ImgRow * ImgCol);
SparseMtx result(ImgRow,ImgCol,img.iNum);
Vector newv(16384);
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
	//_tfopen_s(&fid,FileName,_T("rt+"));
	/*for(int i=0;;i++){
		c=fscanf_s(fid,"%e  ",&abcd);
		a++;
		if(c==-1)
		{

			break;
		}
	}
	fclose(fid);
	*/
	//Vector newv(a-1);
	_tfopen_s(&fid,FileName,_T("rt+"));
	for(int i =0;i<newv.iNum;i++)
	{fscanf(fid,"%e  ",&abcd);
	newv.setvalue(i,abcd);

	}
	//cout<<"加载患者数据完成"<<endl;
	//newv.ShowVector();  //显示读取的向量
	fclose(fid);
	}


	/*Vector img(ImgRow * ImgCol);
	img.Initilize(1.0);*/
	if(pyes == 0)
	{
		//SparseMtx newsp(16384,16384,2506949);
		newsp.Empty();

		FILE* fid1;
		_tfopen_s(&fid1,filename1,_T("rt+"));
		float row1;
		float col2;
		float num12;
		//cout<<"加载标准矩阵开始加载"<<endl;
		for(int i=0;i<2506949;i++){

			fscanf_s(fid1,"%e",&row1);

			fscanf_s(fid1,"%e",&col2);

			fscanf_s(fid1,"%e",&num12);
			newsp.setelement(i,int(row1),int(col2),num12);
			if(i%400000==0){
				//cout<<"已加载完成:"<<float(i)/2506949*100<<"%"<<endl;
			}
		}
		fclose(fid1);
		pyes = 1;
	}
	//cout<<"加载标准矩阵完成"<<endl;
	SprsMtxOperator suanfa;
	/*Vector ImgTmp(ImgRow * ImgCol);
	ImgTmp.Initilize();
	*/
	//	for(int ddnum=0;ddnum<ddnumber;ddnum++)
	//	{
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
	SparseMtx result(ImgRow,ImgCol,img.iNum);
	//img.ShowVector();
	//system("pause");
	//	}
	int i;
	for ( i = 0; i < img.iNum; i++ )
	{
		resultvector.pdData[i]=img.pdData[i];
		//cout<<endl;
	}
	suanfa.reshape(img,ImgRow,ImgCol,result);
}
