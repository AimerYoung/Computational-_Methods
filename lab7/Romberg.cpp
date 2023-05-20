#include<iostream>
#include<cmath>
using namespace std;
#define pi 3.1415926535898
double e=0.000001;
int M=20;
int Count_value=0,Sum_total=0;
double Atx(double t){
	return sin(t)/(sqrt(t)+1);
}
double Vtx(double t){
	double R[M][M],h,temp=0;
	h=t;
	int i ,j,k;
	R[0][0]=Atx(t)*h/2;
	for(k=1;k<M;k++){
		temp=0;
		for(i=1;i<=pow(2,k-1);i++){
			temp+=Atx((2*i-1)*h/pow(2,k));
		}
		R[k][0]=(R[k-1][0]+h*temp/pow(2,k-1))/2;
		for(j=1;j<=k;j++){
			R[k][j]=R[k][j-1]+(R[k][j-1]-R[k-1][j-1])/(pow(4,j)-1);
		}
		if(fabs(R[k][k]-R[k-1][k-1])<e){
			Count_value++;
			return R[k][k];
		}
	}
	Sum_total++;
	return R[k-1][k-1];
}
double Xt(double t){
	double R[M][M],h,temp=0;
	h=t;
	int i ,j,k;
	R[0][0]=Vtx(t)*h/2;
	for(k=1;k<M;k++){
		temp=0;
		for(i=1;i<=pow(2,k-1);i++){
			temp+=Vtx((2*i-1)*h/pow(2,k));
		}
		R[k][0]=(R[k-1][0]+h*temp/pow(2,k-1))/2;
		for(j=1;j<=k;j++){
			R[k][j]=R[k][j-1]+(R[k][j-1]-R[k-1][j-1])/(pow(4,j)-1);
		}
		if(fabs(R[k][k]-R[k-1][k-1])<e){
			Count_value++;
			return R[k][k];
		}
	}
	Sum_total++;
	return R[k-1][k-1];
}
double Aty(double t){
	return log(t+1)/(t+1);
}
double Vty(double t){
	double R[M][M],h,temp=0;
	h=t;
	int i ,j,k;
	R[0][0]=Aty(t)*h/2;
	for(k=1;k<M;k++){
		temp=0;
		for(i=1;i<=pow(2,k-1);i++){
			temp+=Aty((2*i-1)*h/pow(2,k));
		}
		R[k][0]=(R[k-1][0]+h*temp/pow(2,k-1))/2;
		for(j=1;j<=k;j++){
			R[k][j]=R[k][j-1]+(R[k][j-1]-R[k-1][j-1])/(pow(4,j)-1);
		}
		if(fabs(R[k][k]-R[k-1][k-1])<e){
			Count_value++;
			return R[k][k];
		}
	}
	Sum_total++;
	return R[k-1][k-1];
}
double Yt(double t){
	double R[M][M],h,temp=0;
	h=t;
	int i ,j,k;
	R[0][0]=Vty(t)*h/2;
	for(k=1;k<M;k++){
		temp=0;
		for(i=1;i<=pow(2,k-1);i++){
			temp+=Vty((2*i-1)*h/pow(2,k));
		}
		R[k][0]=(R[k-1][0]+h*temp/pow(2,k-1))/2;
		for(j=1;j<=k;j++){
			R[k][j]=R[k][j-1]+(R[k][j-1]-R[k-1][j-1])/(pow(4,j)-1);
		}
		if(fabs(R[k][k]-R[k-1][k-1])<e){
			Count_value++;
			return R[k][k];
		}
	}
	Sum_total++;
	return R[k-1][k-1];
}
int main(){
	double t=0.1;
	int i,j,k;
	for(i=0;i<100;i++){
		cout << "{" <<Xt(1.0*i*t) <<"," << Yt(1.0*i*t) << " },";
	}
	cout << Count_value*1.0/(Sum_total+Count_value); 
	return 0;
} 
