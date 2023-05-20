## 										计算方法Lab6

##### 																			PB20000126 葛哲凯

### 一、实验结果

#### 1.输出$f_1,f_2$对$n_1,n_2$划分后FFT的结果：

![image-20230508004701373](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230508004701373.png)

![image-20230508004710939](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230508004710939.png)

![image-20230508004719481](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230508004719481.png)

![image-20230508004731318](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230508004731318.png)

#### 2.N=16，128时，图像如下：

![image-20230508004839533](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230508004839533.png)

![image-20230508004828040](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230508004828040.png)

#### 3.对于$f_1$绘制图像如下：

![image-20230508004917170](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230508004917170.png)

![image-20230508004925068](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230508004925068.png)

#### 4.对$f_2$取前25%频率的g进行IFFT：

![image-20230508005007127](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230508005007127.png)

##### 可以看出取前 25%与取全部的波形相比较为缓和，但总体差距不大，能较好展示波形。

### 二、结果分析

##### N 越大，重建时所保留的波的信息越多。对含噪音的波，当 n 大于某个值后，g 的值趋于 0， 因此可以只取频率靠前的 g 来进行 IFFT，此时误差很小，波形还原很好