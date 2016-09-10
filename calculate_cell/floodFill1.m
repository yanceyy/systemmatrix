function [area,img] = floodFill1(img,y,x)
    import java.util.LinkedList
    value=0;
    area=0;
    q = LinkedList();
    initial = img(y,x);
    dims = size(img);
    q.add([y, x]);
    area=area+1;
    while q.size() > 0

        pt = q.removeLast();
        y = pt(1);
        x = pt(2);

        if (y < dims(1) && img(y+1, x) == initial) % step down
            img(y+1,x) = value;
            q.add([y+1, x]);
            area=area+1;
        end
        if (y > 1 && img(y-1, x) == initial) % step up
            img(y-1,x) = value;
            q.add([y-1, x]); 
            area=area+1;
        end
        if (x < dims(2) && img(y, x+1) == initial) % step right
            img(y,x+1) = value;
            q.add([y, x+1]); 
            area=area+1;
        end
        if (x > 1 && img(y, x-1) == initial) % step left
            img(y,x-1) = value;
            q.add([y, x-1]); 
            area=area+1;
        end
    end
end