clear all;
img = imread('/Users/wangyang/Music/picture_an/rbc.jpg');
nim = Gray(img);
nim1 = otus(nim);
%nim1 =Tobinary(nim);
nim2 = myimclearborder1(nim1);
nim4=erode(nim2);
nim4=erode(nim4);
nim4=erode(nim4);
nim4=erode(nim4);
%nim5 =floodFill(nim4);
nim5 =fillhole(nim4);
nim6=nim5-erode2(nim5);
[bianjie,zhouchang]=getpar1(nim6);
%[bianjie,zhouchang]=getpar1(nim6);
area = getarea(nim5);
rate = (area.*4.*pi) ./ (zhouchang.*zhouchang) ;
[~,hang] = size(rate);
good_cell=0;
bad_cell=0;
for i=1:hang
    if area(i)<500
        continue;
    end
    if(rate(i)>0.9)
        good_cell=good_cell+1;
[row, col] = size(bianjie{i});
for l=1:col
    img(bianjie{i}{l}(1),bianjie{i}{l}(2),1)=0;
    img(bianjie{i}{l}(1),bianjie{i}{l}(2),2)=255;
    img(bianjie{i}{l}(1),bianjie{i}{l}(2),3)=0;
end
    else
        bad_cell=bad_cell+1;
        [row, col] = size(bianjie{i});
        for l=1:col
    img(bianjie{i}{l}(1),bianjie{i}{l}(2),1)=255;
    img(bianjie{i}{l}(1),bianjie{i}{l}(2),2)=0;
    img(bianjie{i}{l}(1),bianjie{i}{l}(2),3)=0;
        end
    end
end
fprintf('good cells number is %d\nbad cells number is %d\n',good_cell,bad_cell);
imshow(img);    