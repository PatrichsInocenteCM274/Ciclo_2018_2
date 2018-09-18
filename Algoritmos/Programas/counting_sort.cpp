#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

const int k=10000;

using namespace std;
void generaarray(int *,int);
void escribearray(int *,int );
void countingsort(int *,int k ,int n );

int main(){

unsigned long n;int *p;
//clock_t start_t, end_t,total_t;
int start_t, end_t;double total_t;
cin>>n;
//cin>>k;
p=(int *)malloc(n*sizeof(int));
//pB=(int *)malloc(n*sizeof(int));
generaarray(p,n);
//escribearray(p,n);
start_t  = clock();
countingsort(p,k,n);
end_t = clock();
total_t = (double) (end_t - start_t)/CLOCKS_PER_SEC;
printf("n= %d tiene: %f \n",n,(double)total_t);
//escribearray(pB,n);
//cout<<endl<<*p;
free(p);
//free(pB);
return 0;
}

void generaarray(int *p,int n){
	srand(time(NULL));
	int *pmax=p+n;
	while(p<pmax) *p++=rand()%k;
}

void escribearray(int *p,int n){
	int *pmax=p+n;
	while(p<pmax){
		cout<<*p++<<" ";
	}cout<<endl;
}

void countingsort(int *p,int k,int n){
	int i,j,*C,*B;
	C=(int *)malloc((k+1)*sizeof(int));
	B=(int *)malloc(n*sizeof(int));
	for(i=0;i<=k;i++){
		C[i]=0;
	}
	//escribearray(C,k);
	for(j=0;j<n;j++){
		C[p[j]]=C[p[j]]+1;
	}
	//escribearray(C,k);
	for(i=1;i<=k;i++){
		C[i]=C[i]+C[i-1];
	}
	//escribearray(C,k);
	for (j=n-1;j>=0;j--){
		B[C[p[j]]-1]=p[j];
		C[p[j]]--;
	}
	//escribearray(B,n);
	free(B);
	free(C);
}
