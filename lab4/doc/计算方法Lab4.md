# 			计算方法Lab4

#### 							PB20000126葛哲凯

### 一、实验环境

##### vscode，c++

### 二、随机矩阵SVD

##### 自行生成一个4 × 3的随机矩阵A，应用Jacobi方法求解矩阵AAT 的特征值，计算矩阵A的SVD分解。

##### 要求A的每个元素均为[0, 1]区间内的随机数

##### 结果如下：

##### ![image-20230425204709427](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230425204709427.png)

##### 数据带入matlab验算，正确：



### 三、iris（鸢尾花）数据集

##### 输出太多，一页屏幕放不下了。

##### ![image-20230425204933767](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230425204933767.png)

![image-20230425204946033](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230425204946033.png)

##### 使用matplotlib作出原数据集投影到二维平面上的图像：

##### ![image-20230425235122116](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230425235122116.png)

##### 可以看到，对Iris数据集进行PCA分析之后，起到了聚类的效果


### 四、分析Jacobi算法：

##### 使用上面随机生成的矩阵，分别查看$AA^T$和$A^TA$，在Jacobi算法中，非对角元素的平方和的变化：

##### 可以看到，sum缩小的速度是非常快的，在$10^1$的数量级次数下，就减少到$10^{-6}$数量级



![image-20230425210056609](C:\Users\AimerYoung\AppData\Roaming\Typora\typora-user-images\image-20230425210056609.png)



### 五、核心0.代码Jacobi算法

##### 算法过程参考课本

```c++
//Jacobi算法求矩阵特征值
vector<double> Jacobi(vector<vector<double>> matrix){
    int n = matrix.size();  //矩阵阶数
    double epsilon = 1;  
    int p,q;
    vector<double> eigenvalue0(n);
    vector<double> eigenvalue1(n);
    vector<vector<double>> matrix0 = matrix;
    vector<vector<double>> matrix1 = matrix;

    while (epsilon > e){
        double max_element = 0;
        for (int i = 0;i < n;i++){
            for (int j = i + 1;j<n;j++){
                if (abs(matrix1[i][j]) > max_element){
                    max_element = abs(matrix1[i][j]);
                    p = i; q = j;
                }
            }
        }
        double s = (matrix1[q][q]-matrix1[p][p])/(2*matrix1[p][q]);
        double t;

        if (s == 0){
            t = 1;
        }else{
            double t1 = -s - sqrt(s*s+1);
            double t2 = -s + sqrt(s*s+1);
            t = abs(t1) > abs(t2) ? t2 : t1;
        }

        double c = 1/sqrt(1+t*t);
        double d = t/sqrt(1+t*t);


        for (int i = 0;i<n;i++){
            for (int j = 0;j<n;j++){
                matrix0[i][j] = matrix1[i][j];
            }
        }

        for (int i = 0;i < n;i++){
            if (i == p || i == q) continue;
            matrix1[i][p] = c*matrix0[p][i] - d*matrix0[q][i];
            matrix1[p][i] = matrix1[i][p];
            matrix1[i][q] = c*matrix0[q][i] + d*matrix0[p][i];
            matrix1[q][i] = matrix1[i][q];
        }
        matrix1[p][p] = matrix0[p][p] - t*matrix0[p][q];
        matrix1[q][q] = matrix0[q][q] + t*matrix0[p][q];
        matrix1[p][q] = 0;
        matrix1[q][p] = 0;

        for (int i = 0;i < n;i++){
            eigenvalue0[i] = eigenvalue1[i];
            eigenvalue1[i] = matrix1[i][i];
        }
        
        epsilon = norm(eigenvalue0,eigenvalue1);
    
    }

    return eigenvalue1;
}
```

