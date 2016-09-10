function [a,pari]=getpar(I)
Img=I;
[h, w]=size(Img);
peri=0;
    for i=2:h-1
        for j=2:w-1
            if Img(i,j)==1
                numbershu=1;
                a{peri+1}{numbershu}=[i,j];
                numbershu=numbershu+1;
                i1=i;
                j1=j;
                while 1

                    quanzhong=0;
                    if Img(i1,j1-1)==1
                        Img(i1,j1)=0;
                        i1=i1;
                        j1=j1-1;
                        a{peri+1}{numbershu}=[i1,j1];
                        numbershu=numbershu+1;
                        quanzhong=quanzhong+1;
                        
                        continue;
                    end
                    if Img(i1-1,j1-1)==1
                        Img(i1,j1)=0;
                        i1=i1-1;
                        j1=j1-1;
                                                a{peri+1}{numbershu}=[i1,j1];
                        numbershu=numbershu+1;
                        quanzhong=quanzhong+1;
                        continue;
                    end
                    if Img(i1-1,j1)==1
                        Img(i1,j1)=0;
                        i1=i1-1;
                        j1=j1;
                                                a{peri+1}{numbershu}=[i1,j1];
                        numbershu=numbershu+1;
                        quanzhong=quanzhong+1;
                        continue;
                    end
                    if Img(i1-1,j1+1)==1
                        Img(i1,j1)=0;
                        i1=i1-1;
                        j1=j1+1;
                        a{peri+1}{numbershu}=[i1,j1];
                        numbershu=numbershu+1;
                        quanzhong=quanzhong+1;
                        continue;
                    end
                    if Img(i1,j1+1)==1
                        Img(i1,j1)=0;
                        i1=i1;
                        j1=j1+1;
                        a{peri+1}{numbershu}=[i1,j1];
                        numbershu=numbershu+1;
                        quanzhong=quanzhong+1;
                        continue;
                    end
                    if Img(i1+1,j1+1)==1
                        Img(i1,j1)=0;
                        i1=i1+1;
                        j1=j1+1;
                        a{peri+1}{numbershu}=[i1,j1];
                        numbershu=numbershu+1;
                        quanzhong=quanzhong+1;
                        continue;
                    end
                    if Img(i1+1,j1)==1
                        Img(i1,j1)=0;
                        i1=i1+1;
                        j1=j1;
                        a{peri+1}{numbershu}=[i1,j1];
                        numbershu=numbershu+1;
                        quanzhong=quanzhong+1;
                        continue;
                    end
                    if Img(i1+1,j1-1)==1
                        Img(i1,j1)=0;
                        i1=i1+1;
                        j1=j1-1;
                        a{peri+1}{numbershu}=[i1,j1];
                        numbershu=numbershu+1;
                        quanzhong=quanzhong+1;
                        continue;
                    end
                    if quanzhong==0
                        Img(i1,j1)=0;
                        peri=peri+1;
                        break;
                    end

                    
                end
                
            end
        end
    end
    pari=0;
    [~,cellnum]=size(a);
    for i=1:cellnum
        [~,pari(i)]=size(a{i});
    end
end

