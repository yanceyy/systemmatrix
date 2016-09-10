function I = myimclearborder1(img)
    import java.util.LinkedList
    value=0;
    q = LinkedList();
    initial = 1;
    dims = size(img);
    
for i1=1:dims(1)
    if img(i1, 1)==1
    q.add([i1, 1]);
    end
end
for i2=1:dims(2)
    if img(1, i2)==1
    q.add([1, i2]);
    end
end
for i3=1:dims(1)
    if img(i3,dims(2))==1
    q.add([i3, dims(2)]);
    end
end
for i4=1:dims(2)
    if img(dims(1),i4)==1
    q.add([dims(1), i4]);
    end
end

    
    while q.size() > 0

        pt = q.removeLast();
        y = pt(1);
        x = pt(2);

        if (y < dims(1) && img(y+1, x) == initial) % step down
            img(y+1,x) = value;
            q.add([y+1, x]); 
        end
        if (y > 1 && img(y-1, x) == initial) % step up
            img(y-1,x) = value;
            q.add([y-1, x]); 
        end
        if (x < dims(2) && img(y, x+1) == initial) % step right
            img(y,x+1) = value;
            q.add([y, x+1]); 
        end
        if (x > 1 && img(y, x-1) == initial) % step left
            img(y,x-1) = value;
            q.add([y, x-1]); 
        end
    end
    I=img;
end