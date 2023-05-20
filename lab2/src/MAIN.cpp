#include<iostream>  
#include<math.h>
using namespace std; 

// 定义常数
const double ε = 0.0001;
const double e = 2.7182818284;
const double n = 100;
const double h = 0.01;
const double a = 0.5;
double A[99][99] = {0};
double B[99] = {0};
double Y[99],Y1[99],Y2[99],Acc[99];

int Initial(){

    // 初始化系数矩阵A和常数矩阵B

    for(int i = 1;i < 98;i++){
        A[i][i-1] = ε;
        A[i][i] = -(2*ε+h);
        A[i][i+1] = ε+h;
    }
    A[0][0] = -(2*ε+h);
    A[98][98] = -(2*ε+h);
    A[0][1] = ε+h;
    A[98][97] = ε;

    for(int i = 0;i < 98;i++){
        B[i] = a*h*h;
    }
    B[98] = a*h*h-h-ε;
    return 0;
}

double InfiniteNorm(double A[],double B[]){

    // 定义∞范数函数

    int i = 0;
    double max = 0;
    while (i < 99){
        max = max>fabs(A[i]-B[i]) ? max : fabs(A[i]-B[i]);
        i++;
    }
    return max;
}

double TwoNorm(double A[],double B[]){

    // 定义2范数函数

    int i = 0;
    double s = 0;
    while (i < 99){
        s = s + pow((A[i]-B[i]),2);
        i++;
    }
    s = sqrt(s);
    return s;
}

double* Gauss_Seidel(double A[99][99],double B[99]){

    // 定义Gauss_Seidel函数
    // 根据y(0)=0,y(1)=1,均匀初始化Y1,Y2

    for (int i = 0;i < 99;i++){
        Y2[i] = (i+1)*0.01;
    }

    while (InfiniteNorm(Y1,Y2) > 0.000001){
        for (int i = 0;i < 99;i++){
            Y1[i] = Y2[i];
        }
        for (int i = 0;i < 99;i++){
            double s = 0;
            for (int j = 0;j < 99;j++){
                s = s + A[i][j]*Y2[j];
            }
            Y2[i] = (B[i]-s+A[i][i]*Y2[i])/A[i][i];
        }  
    }
    return Y2;
}

double* GaussEliminationWithPartialPivoting(double A[99][99],double B[99]){

    // 列主元高斯消元法

    for (int i = 0;i < 99;i++){
        int k = i;
        for (int j = i+1;j < 99;j++){
            if (fabs(A[k][i]) < fabs(A[j][i])){
                k = j;
            }
        }
        for (int j = i+1;j < 99;j++){
            double t = A[i][j];
            A[i][j] = A[k][j];
            A[k][j] = t;
        }
        double t = B[i];
        B[i] = B[k];
        B[k] = t;
        for (int j = i + 1;j < 99;j++){
            A[j][i] = A[j][i]/A[i][i];
            for(int k = i + 1;k < 99;k++){
                A[j][k] = A[j][k]-A[j][i]*A[i][k];
            }
            B[j] = B[j]-A[j][i]*B[i];
        }
    }
    
    for (int i = 98;i >= 0;i--){
        for (int j = i+1;j < 99;j++){
            B[i] = B[i]-A[i][j]*B[j];
        }
        B[i] = B[i]/A[i][i];
    }
    
    return B;
}

double* Accurate(double Acc[99]){
    for (int i = 0;i < 99;i++){
        double x = h*(i+1);
        Acc[i] = (1-a)*(1-pow(e,-x/ε))/(1-pow(e,-1/ε))+a*x;
    }
    return Acc;
}

int main(){
    Initial();
    Gauss_Seidel(A,B);
    Accurate(Acc);
    //GaussEliminationWithPartialPivoting(A,B);
    for (int i = 0;i < 99;i++){
        cout << Y2[i] <<" ";
    }
    double twonorm = TwoNorm(Acc,Y2);
    cout << endl<<"近似解与精确解的二范数为："<<twonorm <<endl;
    return 0;
}

