function I = myimclearborder(I)

[w, h]=size(I);

for i1=1:w
    I(i1,1) = 0;
end
for i2=1:h
    I(1,i2) = 0;
end
for i3=1:w
    I(i3,h) = 0;
end
for i4=1:h
    I(w,i4) = 0;
end

stack=zeros(2,2);

number=1;
for i1=2:10:w-1
    stack(number,1) = i1;
    stack(number,2) = 2;
    number=number+1;
end
for i2=2:10:h-1
    stack(number,1) = 2;
    stack(number,2) = i2;
    number=number+1;
end
for i3=2:10:w-1
    stack(number,1) = i3;
    stack(number,2) = h-1;
    number=number+1;
end
for i4=2:10:h-1
    stack(number,1) = w-1;
    stack(number,2) = i4;
    number=number+1;
end

number=number-1;



    while number>0

        xx=stack(number,1);
        yy=stack(number,2);
                number=number-1;
    if I(xx+1,yy) == 1 
      
     stack(number+1,1) = xx+1;
      stack(number+1,2) = yy;
      number=number+1;
    end
    if I(xx,yy+1) == 1
       stack(number+1,1) = xx;
      stack(number+1,2) = yy+1;
      number=number+1;
    end
    if I(xx-1,yy) == 1
        stack(number+1,1) = xx-1;
        stack(number+1,2) = yy;
        number=number+1;
    end
    if I(xx,yy-1) == 1
        [number,~] = size(stack);
        stack(number+1,1) = xx;
        stack(number+1,2) = yy-1;
        number=number+1;
        
    end
    if number==0
        break;
    end
  xx = stack(number,1);
  yy = stack(number,2);
 I(xx,yy) = 0;
 
    end
end