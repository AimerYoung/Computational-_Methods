#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <fstream>

using namespace std;
const double e = 1e-6;

//生成随机的4×3的矩阵，每个元素是[0,1]上的随机数
vector<vector<double>> generate_matrix(int rows, int cols){
    //定义一个随机数生成器 
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);

    //定义一个新的矩阵
    vector<vector<double>> matrix(rows, vector<double>(cols));

    // 为矩阵赋值
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = dis(gen);
        }
    }

    // 返回指向矩阵的指针
    return matrix;
}

double norm(vector<double> array1,vector<double> array2){
    double result = 0;
    int n = array1.size();
    for (int i = 0;i < n;i++){
        result = abs(array1[i]-array2[i]) > result ? abs(array1[i]-array2[i]) : result;
    }
    return result;
} 

// 打印矩阵
void Print(vector<vector<double>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// 定义将矩阵和它的转置相乘的函数  tag=U:AA';tag=V:A'A
vector<vector<double>> multiply_transpose(vector<vector<double>> matrix,char tag) {
    int rows = matrix.size();    // 矩阵的行数
    int cols = matrix[0].size(); // 矩阵的列数
    
    // 定义一个新矩阵
    vector<vector<double>> resultU(rows, vector<double>(rows));
    vector<vector<double>> resultV(cols, vector<double>(cols));

    // 计算新矩阵
    if (tag == 'U'){
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < rows; j++) {
                for (int k = 0; k < cols; k++) {
                    resultU[i][j] = resultU[i][j] + matrix[i][k] * matrix[j][k];    
                }
            }
        }
        return resultU;
    }
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < cols; j++) {
            for (int k = 0; k < rows; k++) {
                resultV[i][j] = resultV[i][j] + matrix[k][i] * matrix[k][j]; 
            }
        }
    }
    return resultV;
}

//Jacobi算法求矩阵特征值
vector<double> Jacobi(vector<vector<double>> matrix){
    int n = matrix.size();  //矩阵阶数
    double epsilon = 1;  
    int p,q;
    vector<double> eigenvalue0(n);
    vector<double> eigenvalue1(n);
    vector<vector<double>> matrix0 = matrix;
    vector<vector<double>> matrix1 = matrix;

    cout << "trend of sum:" <<endl;
    while (epsilon > e){

        //计算矩阵非对角元素的平方和，判断是否呈下降趋势
        double sum = 0;
        for (int i = 0;i < n;i++){
            for (int j = 0;j < n;j++){
                if (i == j) continue;
                sum = sum + matrix0[i][j]*matrix0[i][j];
            }
        }
        cout<<sum<<' '<<endl;

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

//求特征向量
vector<vector<double>> eigvec(vector<vector<double>> matrix, vector<double> eig){
    int n = matrix.size();
    vector<double> b(n); //某个特征向量
    vector<vector<double>> result(n,vector<double>(n));  //n个特征向量的矩阵
    vector<vector<double>> a;

    for (int t = 0;t < n;t++){
        a = matrix;
        for(int i=0;i<b.size();i++)
            b[i]=0;

        for (int i = 0;i < n - 1;i++){
            a[i][i] = a[i][i] - eig[t];
            a[n-1][i] = 0;
        }
        a[n-1][n-1] = 1;
        b[n-1] = 1;

        for (int k = 0;k < n - 1;k++){
            for (int i = k + 1 ;i < n;i++){
                a[i][k] = a[i][k]/a[k][k];
                    for (int j = k + 1 ;j<n;j++){
                        a[i][j] = a[i][j]-a[i][k]*a[k][j];
                    }
                    b[i] = b[i] - a[i][k]*b[k];
            }
        }
        
        for (int i = n-2;i >= 0;i--){
            for (int j = i+1;j < n ;j++){
                b[i] = b[i]-a[i][j]*b[j];
            }
            b[i] = b[i]/a[i][i];
        }

        //计算特征向量的模长
        double norm = 0;  
        for (int i = 0;i<n;i++){
            norm = norm + b[i]*b[i]; 
        }
        norm = sqrt(norm);

        for (int i = 0; i < n; i++) {
            b[i] = b[i] / norm;
            result[i][t] = b[i];
        }
    }
    return result;
}

void random(int rows, int cols){
    vector<vector<double>> matrix = generate_matrix(4, 3);
    cout<<"Generate random matrix A:"<<endl;
    for (int i = 0;i < rows;i++){
        for (int j = 0;j < cols;j++){
            cout << matrix[i][j]<<' ';
        }
        cout<<endl;
    }
    cout << endl;

    vector<vector<double>> matrixU = multiply_transpose(matrix,'U');
    vector<vector<double>> matrixV = multiply_transpose(matrix,'V');

    vector<double> eigU = Jacobi(matrixU);
    vector<double> eigV = Jacobi(matrixV);

    cout<<"Solve eigenvalues of matrix AA':"<<endl;
    vector<vector<double>> sigma(rows,vector<double>(rows));
    for (int i = 0;i < rows;i++){
        sigma[i][i] = eigU[i];
        cout << eigU[i]<<' ';
    }
    cout << endl;

    vector<vector<double>> arrU = eigvec(matrixU,eigU);
    vector<vector<double>> arrV = eigvec(matrixV,eigV);

    cout<<"SVD of matrix A = UsigmaV"<<endl;
    cout<<endl;
    cout<<"U:"<<endl;
    for (int i = 0;i < rows;i++){
        for (int j = 0;j < rows;j++){
            cout<<arrU[j][i]<<' ';
        }
        cout<<endl;
    }
    cout << endl;

    cout<<"sigma:"<<endl;
    for (int i = 0;i < rows;i++){
        for (int j = 0;j < rows;j++){
            if (i == j){
                cout<<eigU[i]<<' ';
            }
            cout<<0<<' ';
        }
        cout<<endl;
    }
    cout << endl;

    cout<<"V:"<<endl;
    for (int i = 0;i < cols;i++){
        for (int j = 0;j < cols;j++){
            cout<<arrV[j][i]<<' ';
        }
        cout<<endl;
    }
    cout << endl;
}

//Iris数据集
void Iris(void){

    ifstream infile("iris.txt"); // 打开文件
    if (!infile) { // 判断文件是否成功打开
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    
    vector<vector<double>> data0(4);
    vector<vector<double>> data1(4);
    vector<vector<double>> data2(4);
    vector<vector<vector<double>>> data(3,vector<vector<double>>(4));
    double d1,d2,d3,d4;
    int tag,count0 = 0,count1 = 0,count2 = 0;
    char c;
    string line;

    //读取数据
    while(getline(infile,line)){

        istringstream iss(line);
        iss >> d1;
        iss >> c;
        iss >> d2;
        iss >> c;
        iss >> d3;
        iss >> c;
        iss >> d4;
        iss >> c;
        iss >> tag;
        data[tag][0].push_back(d1);
        data[tag][1].push_back(d2);
        data[tag][2].push_back(d3);
        data[tag][3].push_back(d4);
    }
    
    //去中心化
    for (int i = 0;i < 3;i++){
        vector<double> ave(4,0);
        for(int j = 0;j < 50;j++){
            for (int k = 0;k < 4;k++){
            ave[k] = ave[k] + data[i][k][j]; 
            }
        }

        
        for (int j = 0;j < 4;j++){
            ave[j] = ave[j]/50;
        }
        

        for (int j = 0;j < 50;j++){
            for (int k = 0;k < 4;k++){
                data[i][k][j] = data[i][k][j] - ave[k]; 
            }
        }
    }
    
    //计算协方差矩阵
    cout<<"Caculate Covariance matrix:"<<endl;
    vector<vector<vector<double>>> Cov(3,vector<vector<double>>(4,vector<double>(4)));
    for (int i = 0;i < 3;i++){
        Cov[i] = multiply_transpose(data[i],'U');
    }
    for (int i = 0;i < 3;i++){
        cout << "tag = "<< i <<':'<<endl;
        for (int j = 0; j < 4;j++){
            for (int k = 0;k < 4;k++){
                Cov[i][j][k] = Cov[i][j][k]/50;
                cout<<Cov[i][j][k]<<' ';
            }
            cout << endl;
        }
    }
    cout << endl;

    //求解应用Jacobi方法求解特征值
    cout<<"Solve eigenvalues by Jacobi:"<<endl;
    vector<vector<double>> eigenvalues(3,vector<double>(4));
    for (int i = 0;i < 3 ;i++){
        cout << "tag = "<<i<<endl;
        eigenvalues[i] = Jacobi(Cov[i]);
        for (int j = 0;j < 4;j++){
            cout <<eigenvalues[i][j]<<' ';
        }
        cout << endl;
    }
    cout << endl;

    //找到最大的两个特征值
    cout <<"fine biggest two: "<<endl;
    vector<vector<double>> max2(3,vector<double>(2));
    vector<vector<double>> pq(3,vector<double>(2));
    for (int i = 0;i < 3;i++){
        cout << "tag = "<<i<<endl;
        for (int j = 0;j < 4;j++){
            if (eigenvalues[i][j] > max2[i][1]){
                if (eigenvalues[i][j] > max2[i][0]){
                    max2[i][1] = max2[i][0] > max2[i][1] ? max2[i][0] : max2[i][1];
                    max2[i][0] = eigenvalues[i][j];
                }else{
                    max2[i][1] = eigenvalues[i][j];
                }
            }
        }
        cout << max2[i][0] << ' ' << max2[i][1] << endl;
    }
    cout << endl;

    //计算特征向量
    cout<<"calculate eigenvectors:"<<endl;
    vector<vector<vector<double>>> eigenvectors(3,vector<vector<double>>(4,vector<double>(4))) ;
    for (int i = 0;i < 3;i++){
        cout <<"tag = "<< i << endl;
        eigenvectors[i] = eigvec(Cov[i],eigenvalues[i]);
        for (int j = 0; j < 4;j++){
            for (int k = 0;k < 4;k++){
                cout << eigenvectors[i][k][j] << ' ';
            }
            cout << endl;
        }
    }


    //投影到二维平面上
    //由于需要画图，所以此步骤使用python完成


    infile.close(); // 关闭文件
}

int main(){
    //随机4×3矩阵
    random(4,3);
    

    //鸢尾花数据集
    //Iris();
    

    return 0;
}