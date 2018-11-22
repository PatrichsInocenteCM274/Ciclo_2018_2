#include<stdio.h>
#include<time.h>
#include<stdlib.h>


void imprimir(int *A,int n){
   int i;
   for(i=0;i<n;i++) printf("%d ",A[i]);
   printf("\n");
}

void menor(int *A,int primero,int ultimo,int n){
  int i,captura;
  int men=A[primero];
  for(i=primero;i<=ultimo;i++) 
	if(men>A[i]){
		 men=A[i];
		 captura=i;
	}
 A[captura]=A[primero];
  A[primero]=men;
}

void mayor(int *A,int primero,int ultimo,int n){ 
  int i,captura;;
  int may=A[primero];
  for(i=primero;i<=ultimo;i++) 
	if(may<A[i]){
		 may=A[i];
		 captura=i;
	}
  A[captura]=A[ultimo];
  A[ultimo]=may;
}




void ordenacion(int *A,int primero,int ultimo,int n){
  
  if(primero>=ultimo) imprimir(A,n);
  
  else{ 
       menor(A,primero,ultimo,n);
       imprimir(A,n);	
       mayor(A,primero,ultimo,n);
       imprimir(A,n);
       ordenacion(A,primero+1,ultimo-1,n);    
  }
}


void main(){
  int *A,n,i;
  printf("Ingrese el numero de elementos del arreglo:\n");
  scanf("%d",&n);
  A=(int*)malloc(n*sizeof(int));
 
  //Ingreso aleatorio de elementos en el array A:
  srand(time(NULL));
  for(i=0;i<n;i++)  A[i]=rand()%10;
  printf("El vector es:\n");
  imprimir(A,n);
  printf("Proceso de ordenacion es:\n");
  ordenacion(A,0,n-1,n);
}
