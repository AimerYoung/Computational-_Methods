import numpy as np
import LU

TestA = np.mat([[2,1,1],[1,3,2],[1,2,2]])

A1 = np.mat([[1/9,1/8,1/7,1/6,1/5],[1/8,1/7,1/6,1/5,1/4],[1/7,1/6,1/5,1/4,1/3],
             [1/6,1/5,1/4,1/3,1/2],[1/5,1/4,1/3,1/2,1]])

A2 = np.mat([[4,-1,1,3],[16,-2,-2,5],[16,-3,-1,7],[6,-4,2,9]])

def InfiniteNorm(X,n):

    # ∞范数函数

    max = 0
    for i in range(0,n):
        max = abs(X[i]) if abs(X[i]) > max else max
    return max


def main(A):
    n = len(A)

    # 方便幂法的计算，预处理A=L*U
    U = np.zeros((n,n))
    L = np.zeros((n,n))
    (L,U) = LU.Doolittle(A,L,U)
    # 幂法
    MATRIX = np.zeros((1,n))
    X = np.linspace(1.0,1.0,n)
    Y = np.linspace(1.0,1.0,n)
    y = np.linspace(1.0,1.0,n)
    k = 0       #计数k
    while True:
        max = InfiniteNorm(X,n)
        # print(max)
        for i in range(0,n):
            Y[i] = X[i]/max    #计算Y(k)
        MATRIX = np.r_[MATRIX,[X]]           #存储X(k)至MATRIX的第k+1行
        # MATRIX = np.r_[MATRIX,[Y]]
        k = k + 1
        # 通过LU分解解方程：A*X(k+1) = Y(k) 
        # 解方程组:Ly = Y
        for i in range(0,n):
            sum = 0
            for j in range(0,i):
                sum = sum + L[i,j]*y[j] 
            y[i] = Y[i] - sum
        # 解方程组:UX(k+1) = y
        for i in range(n-1,-1,-1):
            sum = 0
            for j in range(i+1,n):
                sum = sum + U[i,j]*X[j]
            X[i] = (y[i] - sum)/U[i,i]
        if (InfiniteNorm((MATRIX[k]-X),n) < 0.00001):
            λ = 1/InfiniteNorm((MATRIX[k]),n)
            break
    return (MATRIX,λ,Y)

(MATRIX,λ,V) = main(A2)
(a,b) = np.shape(MATRIX)
print("X(k+1)如下：")
for i in range(0,a):
    print(MATRIX[i])

print("矩阵最小特征值为：" + str(λ))
print("对应的特征向量为：" + str(V))
