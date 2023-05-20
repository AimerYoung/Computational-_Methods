# 计算方法LAB7

##### PB20000126 葛哲凯

### 一、算法描述

#### Romberg算法：

1. 计算积分区间两端点函数值f(a),f(b), 计算T1;
2. 将区间[a,b]分半，计算f((a+b)/2), T2,S1;
3. 再将区间分半，算出f(a+(b-a)/2)和f(a+3(b-a)/4), 由此计算T4，S2，C1;
4. 再将区间分半，计算T8，S4，C2，进而计算R1;
5. 再将区间分半，重复第四步工作，计算T16，S8，C4，R2，反复进行这一过程，可以计算R1，R2，R4，,,,, ,直到最终两个R之差不超过给定精度即可。

​	其计算过程是将区间逐次分半，加速得到积分近似值，因此称为**逐次分半加速法**

#### 模拟质点运动：

1. 根据$a_x(t),a_y(t)$，使用Romberg算法求得$v_x(t),v_y(t)$
2. 根据$v_x(t),v_y(t)$，使用Romberg算法求得$x(t),y(t)$



### 二、实验结果

当$M=8$时，运行结果如下：

<div>
    <center>
        <img src = "C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230520085742373.png"
             <br>
        <font size = "4">Output in VScode</font>
    </center>
</div>



<div>			<!--块级封装-->
    <center>	<!--将图片和文字居中-->
    <img src="C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230520090237504.png"
         alt="无法显示图片时显示的文字"
         style="zoom:这里写图片的缩放百分比"/>
    <br>		<!--换行-->
    <font size="4">Graph in Mathematica<font>	<!--标题-->
    </center>
</div>



### 三、算法比较

| M                  | 4         | 8        | 12   | 16   | 20   |
| ------------------ | --------- | -------- | ---- | ---- | ---- |
| 达到要求精度的比例 | 0.0686937 | 0.648624 | 1    | 1    | 1    |

当$M \geq 12$后，均达到精度，达到误差要求的次数/调用总次数 = 1



### 四、结果和分析

- ##### 结果与MMA模拟结果一致，y方向速度恒增，x方向速度变化趋势类似正弦波的衰弱分布

- ##### M在一定范围内时，越大，精度越高，计算次数越多,此时精度依赖于M和e，当M大于某个临界值后，M变化不影响精度和计算次数，此时精度只依赖于e。

  ##### 可以将M取值很大，就能保证一定达到设置精度，或取精度次数/总次数>某临界值，减少运算次数，使其大多数达到精度。

<div>
    <center>
    	<img src = "C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230520093457612.png"
         <br>
        <font size = "4" >Simulate in Mathematica</font>
    </center>
</div>

