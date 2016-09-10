function img = floodFill(img)
    import java.util.LinkedList
    value=1;
    x=1;
    y=1;
    q = LinkedList();
    img_old=img;
    initial = img(x,y);
    dims = size(img);
    q.add([y, x]);
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
    img=logical(img_old+(1-img));
end