function [ I ] = Gray(im)
Img = im;
[height,width,color] = size(Img);
I = zeros(height,width);
I = uint8(I);
for i = 1:height
    for j = 1:width     
        I(i,j)=0.299*Img(i,j,1)+0.587*Img(i,j,2)+0.114*Img(i,j,3);
    end
end

