function im=fillhole(mi)
[h,w]=size(mi);
I=~mi;
f=zeros(h,w);
for i=1:h
    f(i,1)=1- mi(i,1);
end
for i=1:h
    f(i,w)=1- mi(i,w);
end
for i=1:w
    f(1,i)=1- mi(1,i);
end
for i=1:w
    f(h,i)=1- mi(h,i);
end
 %最外圈取反
f1=f;
while 1
    f=f1;
    for i=2:h-1
        for j=2:w-1
            if f(i-1,j)==1 || f(i,j+1)==1 ||f(i+1,j)==1 ||f(i,j-1)==1
                f1(i,j)=1;
            end
        end
    end
    f1=I&f1;
    if f==f1
        break;
    end
end
im=~f;
end
