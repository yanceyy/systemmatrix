function [Img]=spratecell(I)
Img=I;
[h,w]=size(I);
img_old=Img;
% while 1
for i=2:h-1
    for j=2:w-1
        quanzhong=0;
        if img_old(i-1,j)==0
            quanzhong= quanzhong+1;
        end
        if img_old(i+1,j)==0
            quanzhong= quanzhong+1;
        end
        if img_old(i,j+1)==0
            quanzhong= quanzhong+1;
        end
        if img_old(i,j-1)==0
            quanzhong= quanzhong+1;
        end
        if img_old(i-1,j-1)==0
            quanzhong= quanzhong+1;
        end
        if img_old(i-1,j+1)==0
            quanzhong= quanzhong+1;
        end
        if img_old(i+1,j-1)==0
            quanzhong= quanzhong+1;
        end
        if img_old(i+1,j+1)==0
            quanzhong= quanzhong+1;
        end
        
        if quanzhong~=8
            Img(i,j)=0;
        end
        end
end
%         if Img==img_old
%             break;
%         end
%         
%         img_old=Img;
% end


end