function [Img]=erode(I)
Img2=I;
Img=I;
[h,w]=size(I);
for i=2:h-1
    for j=2:w-1
        quanzhong=0;
        if Img2(i-1,j)==0
            quanzhong= quanzhong+1;
        end
        if Img2(i+1,j)==0
            quanzhong= quanzhong+1;
        end
        if Img2(i,j+1)==0
            quanzhong= quanzhong+1;
        end
        if Img2(i,j-1)==0
            quanzhong= quanzhong+1;
        end
        
        if quanzhong>=3
            Img(i,j)=0;
        end   
        end
    end
end