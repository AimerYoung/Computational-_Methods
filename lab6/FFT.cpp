#include <iostream>
#include<math.h>
#include <complex.h>
//FFT
const double pi = acos(-1.0);
typedef struct											
{
	double real;
	double imag;
}complex;

int FFT(complex *f,int n,complex *g){
	int i,j,k;
	//printf ("%d\n",n);
	if(n==1){
		*g=*f;
		return 0;}
	complex g0[n/2],g1[n/2],f0[n/2],f1[n/2]; 
	for(i=0;i<n/2;i++){
		f0[i]=f[2*i];
		f1[i]=f[2*i+1];
	}
	
	FFT(f0,n/2,g0);
	FFT(f1,n/2,g1);
	
	
	complex wn,w0;
	wn.imag =-sin(2*pi/n);
	wn.real =cos(2*pi/n); 
	w0.imag =0;w0.real =1;
	for(k=0;k<n/2;k++){
		g[k].imag =(g0[k].imag +w0.imag *g1[k].real+w0.real *g1[k].imag )/2 ;
		g[k].real  =(g0[k].real +w0.real *g1[k].real -w0.imag *g1[k].imag)/2 ;
		g[k+n/2].imag =(g0[k].imag -w0.imag *g1[k].real -w0.real *g1[k].imag)/2 ;
	
		g[k+n/2].real =(g0[k].real-w0.real*g1[k].real+w0.imag *g1[k].imag)/2 ;
		w0.imag =w0.imag*wn.real+w0.real*wn.imag ;
		w0.real  =w0.real*wn.real-w0.imag *wn.imag ;
	}         
	return 0;
}
int IFFT(complex *f,int n,complex *g){
	int i,j,k;
	//printf ("%d\n",n);
	if(n==1){
		g->imag =f->imag ;
		g->real =f->real;
		return 0;}
	complex g0[n/2],g1[n/2],f0[n/2],f1[n/2]; 
	for(i=0;i<n/2;i++){
		f0[i]=f[2*i];
		f1[i]=f[2*i+1];
	}
	
	IFFT(f0,n/2,g0);
	IFFT(f1,n/2,g1);
	
	
	complex wn,w0;
	wn.imag =sin(2*pi/n);
	wn.real =cos(2*pi/n); 
	w0.imag =0;w0.real =1;
	for(k=0;k<n/2;k++){
		g[k].imag =(g0[k].imag +w0.imag *g1[k].real+w0.real *g1[k].imag ) ;
		g[k+n/2].imag =(g0[k].imag -w0.imag *g1[k].real -w0.real *g1[k].imag);
		g[k].real  =(g0[k].real +w0.real *g1[k].real -w0.imag *g1[k].imag);
		g[k+n/2].real =(g0[k].real-w0.real*g1[k].real+w0.imag *g1[k].imag) ;
		w0.imag =w0.imag*wn.real+w0.real*wn.imag ;
		w0.real  =w0.real*wn.real-w0.imag *wn.imag ;
	}         
	return 0;
}
int main(){
	int n=16;
	int i,j,k;
	complex f[n],g[n],f_2[n],g_2[n],gh[n],fh[n];
	for(i=0;i<n;i++) {
		f[i].real=0.7*sin(2*pi*2*i/n) + sin(2*pi*5*i/n)+0.3*rand()/(RAND_MAX+1.0);
		f[i].imag =0.0;
		//printf ("%lf\n",f[i].real );
	}
	
	FFT(f,n,g);
	for(i=0;i<n;i++) {
		if(i<=n/4){
		
		 	gh[i].real=g[i].real ;
			gh[i].imag =g[i].imag ;
	    }
		else{
			gh[i].real=0.0 ;
			gh[i].imag =0.0;
		}
		
	}
	//IFFT(g,n,f);
	IFFT(gh,n,fh);
	for(i=0;i<n;i++) {printf ("%.6lf\n",fh[i].real  );}
}
