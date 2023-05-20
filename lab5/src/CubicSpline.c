#include<stdio.h>
#include <stdlib.h>
#include<math.h>
int main(){
	int i,j,k,n;
	double x[21],y[21],h[20],d[19],M[21],l[19],u[19];
	FILE *fp;
    if((fp=fopen("expoint.txt","r"))==NULL)
    {
        printf("Can not open file!\n");
        exit(1);
    }
    n=0;
    
	 while(!feof(fp))   
    {
    
		
        fscanf(fp,"%lf %lf",&x[n],&y[n]);
        //printf("%lf %lf\n",x[i],y[i]);
        
    	n++;
    }
    x[9]=0;y[9]=10.0;
    for(i=1;i<n;i++){
    	h[i-1]=x[i]-x[i-1];
    	
	}
	for(i=1;i<n-1;i++){
    	l[i-1]=h[i]/(h[i]+h[i-1]);
    	u[i-1]=1-l[i-1];
    	d[i-1]=6*((y[i+1]-y[i])/h[i]-(y[i]-y[i-1])/h[i-1])/(h[i]+h[i-1]) ;
    	//printf("%lf\n",d[i-1]);
    	
	}
	
	double Cmat[n-2][n-2],V[n-2],U[n-2],W[n-2],m[n-2];
	for(i=0;i<n-2;i++){
		Cmat[i][i]=2.0;
		if(i!=0)
		Cmat[i][i-1]=u[i];
			
		
		if(i!=n-3)
		Cmat[i][i+1]=l[i];
		
	
	}
	for(i=0;i<n-2;i++){
	
		if(i==0){
			U[i]=2.0;
			m[i]=d[i]/U[i];
		}
		
		else{
			
			U[i]=2.0-0.5*V[i-1];
			m[i]=(d[i]-0.5*m[i-1])/U[i];
			
		}
		V[i]=0.5/U[i];
	}
	for(i=n-3;i>=0;i--){
		if (i==n-3)
			M[i+1]=m[i];
		else
			M[i+1]=m[i]-V[i]*M[i+2];
		
	}
	M[0]=0.0;
	M[n-1]=0.0;
	printf("M:\n",M[i]);
	for(i=0;i<n;i++){
		printf("%lf \n",M[i]);
		} 
	printf("S(x) on each interval:\n",M[i]);
	for(i=0;i<n-1;i++){
		printf("S(x)=%lf(x^3)+%lf(x^2)+%lf(x)+%lf\t %.1lf<=x<=%.1lf\n",(M[i+1]-M[i])/(6*h[i]), -(x[i]*M[i+1]-x[i+1]*M[i])/(2*h[i]), (y[i+1]-y[i])/h[i]+(M[i]-M[i+1])*h[i]/(6.0)-(x[i+1]*x[i+1]*M[i]-x[i]*x[i]*M[i+1])/(2*h[i]) , (x[i+1]*x[i+1]*x[i+1]*M[i]-x[i]*x[i]*x[i]*M[i+1])/(6*h[i])+(x[i+1]*y[i]-x[i]*y[i+1])/h[i]-(x[i+1]*M[i]-x[i]*M[i+1])*h[i]/6.0,x[i],x[i+1]); 
		} 
    
} 
