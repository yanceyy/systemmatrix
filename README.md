系统矩阵生成理论
--------------------------------------
这里以4 * 4单位像素为示例，当对像素点的扫描为4个接收器时，只需均匀选取4个角度的投影即可计算出4*4像素的个像素的数值。
如图示分别选取与水平方向呈0°，45°，90°，135°为投影角度（每相邻两条线之间的距离恒定。
![image](hhttps://github.com/yanceyy/systemmatrix/blob/master/readme_image/IMG_1.png)与水平方向呈0°
![image](hhttps://github.com/yanceyy/systemmatrix/blob/master/readme_image/IMG_2.png)与水平方向呈45°
![image](hhttps://github.com/yanceyy/systemmatrix/blob/master/readme_image/IMG_3.png)与水平方向呈90°
![image](hhttps://github.com/yanceyy/systemmatrix/blob/master/readme_image/IMG_4.png)与水平方向呈135°
下面以与水平方向呈45°第一条线为例,简单叙述各线经过像素点的投影贡献值的计算方式
![image](hhttps://github.com/yanceyy/systemmatrix/blob/master/readme_image/IMG_5.png)
由于线段距离原点为已知且固定的值，可知其长为1.5，那么可分别取出线段上的不重合两点分别为（1.5*cos45°，1.5*sin45°）,(1.5/cos45°,0)那么就可以确定这条唯一直线。
![image](hhttps://github.com/yanceyy/systemmatrix/blob/master/readme_image/IMG_6.png)

由于像素点的边界的所有线段为已知线段，可求得其与投影线的各各交点的坐标，由交点即可计算出各各线段的长度，由线段左焦点的坐标和旋转角度即可确定，线段位于第几个像素点之内。
可得出这条线在稀疏矩阵内的三维坐标形式。
5  2   1.242641
5  1   0.171573
5  5   1.242641
同理，可将像素整体数量进行扩张，可得出128*128像素的系统矩阵。
![image](hhttps://github.com/yanceyy/systemmatrix/blob/master/readme_image/IMG_7.png)

由以上方法生成系统矩阵生成的正弦图像
![image](hhttps://github.com/yanceyy/systemmatrix/blob/master/readme_image/IMG_8.png)
迭代10次生成的图像结果
