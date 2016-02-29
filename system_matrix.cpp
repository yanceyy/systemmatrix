  #include <iostream>
  #include <math.h>
  #include <vector>
  #include <algorithm>
  float pi=3.1415926;
  const int row=4;
  using namespace std;
  int hang=0;
  FILE* cp=fopen("/Users/yancey/Desktop/dsda.txt","wt");
  typedef struct FloatPoint_struct{
         float x;
         float y;
   } FloatPoint;

  typedef struct Line_struct{
  	 FloatPoint Start;
           FloatPoint End;
   } Line;


  FloatPoint*  GetLineIntersection(Line RefLine1, Line RefLine2)
  {
    FloatPoint* Intersection=new FloatPoint ;
    float K1,K2,Delta_X1,Delta_Y1,Delta_X2,Delta_Y2;
    Delta_X1=RefLine1.End.x-RefLine1.Start.x;
    Delta_Y1=RefLine1.End.y-RefLine1.Start.y;
    Delta_X2=RefLine2.End.x-RefLine2.Start.x;
    Delta_Y2=RefLine2.End.y-RefLine2.Start.y;

     if (Delta_X1==0) 
     	{
  		if (Delta_X2==0)  return NULL;
  		else
  			{
  			   K2=(float)Delta_Y2/((float)(Delta_X2));
  			   Intersection->x=RefLine1.Start.x;
      			   Intersection->y=K2*(Intersection->x- RefLine2.Start.x)+ RefLine2.Start.y ;
      			   return Intersection;
  			}
     	}
     else if (Delta_X2==0)
     	{
     	    K1=(float)Delta_Y1/((float)(Delta_X1));
  	   Intersection->x=RefLine2.Start.x;
      	   Intersection->y=K1*(Intersection->x- RefLine1.Start.x)+ RefLine1.Start.y ;
      	   return Intersection;
     	}
     else
     	{
     	    K1=(float)Delta_Y1/((float)(Delta_X1));
  	    K2=(float)Delta_Y2/((float)(Delta_X2));
  	   if(K1==K2) return NULL;
  	   else
  	   	{
  	   	   Intersection->x=(RefLine2.Start.y-RefLine1.Start.y-(K2*RefLine2.Start.x-K1*RefLine1.Start.x))/(K1-K2);
    		   Intersection->y=K1*(Intersection->x-RefLine1.Start.x)+RefLine1.Start.y;
    		   return Intersection;
  	   	}
     	}
   
  }//end of getintersection
  struct Line_struct xzhou={0,0,1,0};
  struct Line_struct yzhou={0,0,0,1};

  struct Line_struct a[row];
  struct Line_struct b[row];
  struct Line_struct c[row];


  int main()

  {
    for(int i=0;i<row;i++)
    {  float false1 = 1;
       int r=i;
      if(i>=2)
      {
        false1 = -1;
        r -= 2;
      }

      a[i].Start.x=0;
      a[i].Start.y=(r+1)*false1;
      a[i].End.x=1;
      a[i].End.y=(r+1)*false1;
      b[i].Start.x=(r+1)*false1;
      b[i].Start.y=0;
      b[i].End.x=(r+1)*false1;
      b[i].End.y=1;
    }
  for(int z=0;z<row;z++)
  {
  for(int i=0;i<row;i++)
   { vector<FloatPoint_struct> vec;

    float false1 = 0.5;
      int r=z;
      if(z>=2)
      {
        false1 = -0.5;

        r -= 2;
      }
      c[z].Start.x=0;
      c[z].Start.y=(2*r+1)*false1;
      c[z].End.x=1*cos(i*pi/row/2);
      c[z].End.y=(2*r+1)*false1+1*sin(i*pi/row/2);

  struct FloatPoint_struct *d;
  struct FloatPoint_struct newpoint;

  d=GetLineIntersection(c[z],xzhou);
  if(d!=NULL)
  {
    
  if(d->x>=-2&&d->x<=2&&d->y<=2&&d->y>=-2)

  {newpoint.x=d->x;
  newpoint.y=d->y;
  vec.push_back(newpoint);
  }
  }

  d=GetLineIntersection(c[z],yzhou);
  if(d!=NULL)
  {
    
  if(d->x>=-2&&d->x<=2&&d->y<=2&&d->y>=-2)

  {newpoint.x=d->x;
  newpoint.y=d->y;
  vec.push_back(newpoint);
  }
  }

  for(int t=0;t<row;t++){

  d=GetLineIntersection(c[z],b[t]);
  if(d!=NULL)
  {
    
  if(d->x>=-2&&d->x<=2&&d->y<=2&&d->y>=-2)

  {newpoint.x=d->x;
  newpoint.y=d->y;
  vec.push_back(newpoint);
  }
  }
  d=GetLineIntersection(c[z],a[t]);
  if(d!=NULL)
  {
    
  if(d->x>=-2&&d->x<=2&&d->y<=2&&d->y>=-2)

  {newpoint.x=d->x;
  newpoint.y=d->y;
  vec.push_back(newpoint);
  }
  }
  }



 // cout<<vec.size()<<endl;;
  for(int vecnum=0;vecnum<vec.size()-1;vecnum++)
  {
    for(int vecnum1=0;vecnum1<vec.size()-1-vecnum;vecnum1++)
    {  
      if(vec[vecnum1].x>vec[vecnum1+1].x)
      {struct FloatPoint_struct exchangepoint={vec[vecnum1].x,vec[vecnum1].y};
       vec[vecnum1].x=vec[vecnum1+1].x;
       vec[vecnum1].y=vec[vecnum1+1].y;
       vec[vecnum1+1].x=exchangepoint.x;
       vec[vecnum1+1].y=exchangepoint.y;
      }
    }
  }
  
    hang++;
    for(int abc=0;abc<vec.size()-1;abc++)
     { float distance=sqrt((vec[abc].x-vec[abc+1].x)*(vec[abc].x-vec[abc+1].x)+(vec[abc].y-vec[abc+1].y)*(vec[abc].y-vec[abc+1].y));
      //cout<<distance<<endl;
      if(vec[abc].x>=0&&vec[abc].y>=0)
      { int newnum=row*row/2+int(vec[abc].x)*4+(row/2-int(vec[abc].y));
         cout<<hang<<"  "<<newnum<<"  "<<distance<<endl;
         fprintf(cp, "%d %d %f\n",hang,newnum,distance );
      }
      else if (vec[abc].x>=0&&vec[abc].y<0)
      {
        int newnum=row*row/2+int(vec[abc].x)*4+row/2+ceil(-vec[abc].y);
      cout<<hang<<"  "<<newnum<<"  "<<distance<<endl;
      fprintf(cp, "%d %d %f\n",hang,newnum,distance );
      }
      else if(vec[abc].x<0&&vec[abc].y<0)
      {
        int newnum=(2-ceil(-vec[abc].x))*row+row/2+ceil(-vec[abc].y);
        cout<<hang<<"  "<<newnum<<"  "<<distance<<endl;
        fprintf(cp, "%d %d %f\n",hang,newnum,distance );
      }
      else
      {
       int newnum=2-int(vec[abc].y)+row*(row/2-ceil(-vec[abc].x));
       cout<<hang<<"  "<<newnum<<"  "<<distance<<endl;
       fprintf(cp, "%d %d %f\n",hang,newnum,distance );
      }
     }
  //排序函数


  /*if(i==1&&z==2){
    for(int abc=0;abc<vec.size();abc++)
     {
      cout<<"("<<vec[abc].x<<","<<vec[abc].y<<")"<<endl;
     }
  }
  //测试使用
  */


  }

  }
  }