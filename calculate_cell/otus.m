function I=otus(im)
[h,w]=size(im);
hist=zeros(256);
for i=1:h
    for j=1:w
        hist(im(i,j)+1)=hist(im(i,j)+1)+1;
    end
end
 
T_m=0;
for k1=1:256
    T_m=T_m+(k1-1)*hist(k1)/(h*w);
end
G_B=0;
G_B_max=0;
T_finally=0;
for T=0:255
    T_little=sum(hist(1:T+1));
    T_bigger=sum(hist(T+2:256));
    T_little_p=T_little/(h*w);
    T_bigger_p=T_bigger/(h*w);
    T_little_m=0;
    T_bigger_m=0;
    for k1=1:T+1
       T_little_m=T_little_m+(k1-1)*hist(k1)/(h*w);
    end
    T_little_m=T_little_m/T_little_p;
    for k2=T+2:256
       T_bigger_m=T_bigger_m+(k2-1)*hist(k2)/(h*w);
    end
    T_bigger_m=T_bigger_m/T_bigger_p;
    G_B=T_little_p*(T_little_m-T_m)^2+T_bigger_p*(T_bigger_m-T_m)^2;
    if G_B>G_B_max
        G_B_max=G_B;
        T_finally=T;
    end
end
I=im<=T_finally;
end