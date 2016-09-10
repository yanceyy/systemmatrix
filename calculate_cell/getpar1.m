function [allarea,pari]=getpar1(I)
Img=I;
number=0;
[h, w]=size(Img);
    for i=2:2:h-1
        for j=2:2:w-1
            if Img(i,j)==1
                [area,Img]=floodFill_par(Img,i,j);
                number=number+1;
                allarea{number}=area;
            end
        end
    end
    
    pari=0;
    [~,cellnum]=size(allarea);
    for i=1:cellnum
        [~,pari(i)]=size(allarea{i});
    end
end
