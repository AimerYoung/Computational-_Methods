# LU分解（Doolittle分解）

def Doolittle(A,L,U):
    n = len(A)
    for i in range(0,n):
        L[i,i] = 1  

    for k in range(0,n):

        # 计算U的第k行元素
        for j in range(k,n):
            sum = 0
            for r in range(0,k):
                sum = sum + L[k,r]*U[r,j]
            U[k,j] = A[k,j] - sum

        # 计算L的第k行元素
        for i in range(k+1,n):
            sum = 0
            for r in range(0,k):
                sum = sum + L[i,r]*U[r,k]
            L[i,k] = (A[i,k]-sum)/U[k,k]
    
    return (L,U)


