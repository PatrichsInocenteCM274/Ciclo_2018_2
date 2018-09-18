#include<stdio.h>
#include<stdlib.h>


int heap_size;

void MAX_HEAPIFY(int *a,int i){
    int j,temp,flag=1;
    
    
    while(2*i<=heap_size && flag==1)
    {
        j=2*i;    //j points to left child
        if(j+1<=heap_size && a[j+1] > a[j])
            j=j+1;
        if(a[i] > a[j])
            flag=0;
        else
        {
            temp=a[i];
            a[i]=a[j];
            a[j]=temp;
            i=j;
        }
    }

}
 

void BUILD_MAX_HEAP(int *a,int n){
	int i;
	heap_size=n;
	for(i=n/2;i>=1;i--) MAX_HEAPIFY(a,i);
}



void main(){
	int *a,i,aux,n;
	printf("Ingresa numero de elementos:\n");
	scanf("%d",&n);	
	a=(int *)malloc((n+1)*sizeof(int));
	printf("Ingresa elementos:\n");
	for(i=1;i<n+1;i++) scanf("%d",&a[i]);
	BUILD_MAX_HEAP(a,n);
	for(i=heap_size;i>=2;i--){
		aux=a[1];
		a[1]=a[heap_size];
		a[heap_size]=aux;
		heap_size=heap_size-1;
		MAX_HEAPIFY(a,1);
	}
	for(i=1;i<n+1;i++) printf("%d ",a[i]);
	printf("\n");

}
