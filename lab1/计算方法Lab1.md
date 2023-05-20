#          计算方法Lab1

####                      PB20000126 葛哲凯

## 算法：

### 	核心为二分法，在圆O上找点T，连接P、Q点，研究连线形成的角度，不断细分使之符合要求

#### 1.输入P、Q点的坐标

#### 2.在圆O上取初始的T<sub>0</sub>点，TP与圆O相切,T<sub>1</sub>取为T<sub>0</sub>和S在圆O上的中点；若物点Q在直线AB之下，则取AQ

#### 与圆的交点为T0

如下图，PT<sub>0</sub>⊥AT<sub>0</sub>，T<sub>1</sub>为S和T<sub>0</sub>在圆上的中点

#### 3.连接TP和TQ，研究θ<sub>1</sub>和θ<sub>2</sub>的关系，若θ<sub>1</sub>>θ<sub>2</sub>,则说明真正的反射点在T<sub>0</sub>和S之间，否则说明真正的反射点在T<sub>1</sub>和T<sub>0</sub>之间

如下图，θ<sub>1</sub>为∠PT<sub>1</sub>B，θ<sub>2</sub>为∠QT<sub>1</sub>B

#### 4.按第三步中的判断，更改新的二分上下限，找到新的S，T<sub>0</sub>，T<sub>1</sub>，重复判断

#### 5.直至某个时刻，|θ<sub>1</sub>-θ<sub>2</sub>|<0.00001时，结果的精度将达到四位有效数字或更高，退出循环

#### 6.根据此时的反射点T的坐标，以及物理知识：像点R在PT的延长线上，且RT=QT，求出像点R的坐标

#### 7.完成

![image-20230319005833227](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319005833227.png)



#### 代码：

```python
import numpy as np
import math

# p<0,m<0,n>0
p = float(input("输入观察点P的x坐标:"))  
x0 = -1
y0 = 0  # P点坐标
m, n =input("输入物点Q的坐标:").split()
m=float(m)
n=float(n)

# T0点坐标，取为P与圆O在第二象限相切的点
x1=1.0/p
y1=-np.sqrt(p*p-1.0)/p

# 若物点Q在直线QT0之下，则取AQ与圆的交点为T0
theta1 = (-1)*math.atan(n/m)
theta2 = (-1)*math.atan(y1/x1)
if (2*theta1 < theta2):
    x1 = m/np.sqrt(m*m+n*n)
    y1 = n/np.sqrt(m*m+n*n)


# 下面循环对应算法3-5步
# 经过计算验证，当epsilon<0.00001时，满足有效数字精确到小数点后四位
while True:
    tx0 = (x0+x1)/2.0
    ty0 = (y0+y1)/2.0
    OT0 = np.array([tx0,ty0])
    tx = tx0/np.linalg.norm(OT0)
    ty = ty0/np.linalg.norm(OT0)
    TP = np.array([p-tx,0-ty])
    TQ = np.array([m-tx,n-ty])
    OT = np.array([tx,ty])
    OTP = math.acos(np.dot(TP,OT)/(np.linalg.norm(TP)*np.linalg.norm(OT)))  #即θ1
    OTQ = math.acos(np.dot(TQ,OT)/(np.linalg.norm(TQ)*np.linalg.norm(OT)))  #即θ2
    epsilon = OTP-OTQ
    if (abs(epsilon) < 0.00001):
        break
    elif(epsilon > 0):
        x1 = tx
        y1 = ty
    else:
        x0 = tx
        y0 = ty

# 计算像点R的坐标，根据R在PT延长线上
rtx = (tx-p)*np.linalg.norm(TQ)/(np.linalg.norm(TP))
rty = (ty)*np.linalg.norm(TQ)/(np.linalg.norm(TP))
rx = tx + rtx
ry = ty + rty

print("T=("+str(tx)+","+str(ty)+")")
print("R=("+str(rx)+","+str(ry)+")")
```



## 实验结果：

#### 测试数据：

![image-20230319010349470](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319010349470.png)

![image-20230319010414376](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319010414376.png)

#### 实验数据：

![image-20230319010458316](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319010458316.png)

![image-20230319011625335](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319011625335.png)

![image-20230319010612746](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319010612746.png)

![image-20230319011703775](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319011703775.png)

![image-20230319011724128](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319011724128.png)

![image-20230319011754395](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319011754395.png)

![image-20230319011811729](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319011811729.png)

![image-20230319011832781](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319011832781.png)

## 总结：

实验结果符合预期，不论物点Q的位置是否在y比较大的位置或贴近于x轴的位置，最终精度都能够达到四位有效数字

使用2分法来数值计算比解析算法更高效有有实际意义。解析方法如下：显然难以求出结果

![image-20230319012451304](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319012451304.png)

![image-20230319012502634](C:\Users\15384\AppData\Roaming\Typora\typora-user-images\image-20230319012502634.png)

### 精确性问题：算法是通过角度来反馈精确性，并不完全等同于长度。

### 稳定性问题：稳定，不会出问题。