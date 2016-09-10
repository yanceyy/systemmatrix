function [allarea]=getarea(I)
Img=I;
allarea=0;
number=0;
[h, w]=size(Img);
    for i=2:2:h-1
        for j=2:2:w-1
            if Img(i,j)==1
                [area,Img]=floodFill1(Img,i,j);
                number=number+1;
                allarea(number)=area;
            end
        end
    end
end
