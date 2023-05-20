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
