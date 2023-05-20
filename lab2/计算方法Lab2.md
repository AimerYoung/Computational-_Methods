# 		计算方法Lab2

#### 					PB20000126 葛哲凯

### 算法：

算法①：Gauss_Seidel迭代算法

算法②：列主元高斯消元法

算法均在书本上有描述和伪代码。

### 实验结果：

一、Gauss_Seidel迭代算法：

使用while结构控制算法，取精确度为||Y1-Y2||<sub>∞</sub><0.000001时退出

![image-20230329235327029](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230329235327029.png)

使用近似解与精确解的差的二范数来表示误差

得到结果如下：

ε = 1时：

![image-20230330003926466](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230330003926466.png)

ε = 0.1时：

![image-20230330003942455](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230330003942455.png)

ε = 0.01时：

![image-20230330003958580](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230330003958580.png)

ε = 0.0001时：

![image-20230330004011413](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230330004011413.png)

二、列主元高斯消元法

ε = 1时：

![image-20230330003901165](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230330003901165.png)

ε = 0.1时：

![image-20230330003844674](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230330003844674.png)

ε = 0.01时：

![image-20230330003829228](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230330003829228.png)

ε = 0.0001时：

![image-20230330003814515](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230330003814515.png)

### 分析：

#### ①两种算法下，||Y1-Y2||<sub>2</sub>均在0.01左右，说明近似得比较好，精确解与近似解在0.001的精确度上都一样，在这个精确度下作图也难以肉眼看出差别。

#### ②两种算法都比较稳定，不会因为系数ε的剧烈变化而导致精确性的剧烈变化。