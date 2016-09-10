function I=Tobinary(im)
[h,w]=size(im);
T=sum(sum(im))/(w*h);
while 1
im_little=zeros(h,w);
im_bigger=zeros(h,w);
im_bigger_num=0;
im_little_num=0;
for i=1:h
    for j=1:w
        if(im(i,j)>T)
            im_bigger(i,j)=im(i,j);
            im_bigger_num=im_bigger_num+1;
        else
            im_little(i,j)=im(i,j);
            im_little_num=im_little_num+1;
        end                                                                                                      
    end
end
T_new=round((sum(sum(im_little))/im_little_num+sum(sum(im_bigger))/im_bigger_num)/2);
if T_new==T
    break;
end
T=T_new;
end
I=im<=T;
end

