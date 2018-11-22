
     #include<stdio.h>
     #include<time.h>
     #include<stdlib.h>
     
     int elemayoria(int *A,int n){
     int contador=1,i;
     for(i=0;i<n-1;i++){
	if(A[i]==A[i+1]) contador++;
	else contador=1;
	if(contador>(n/2)) return A[i];
     }			
     return -1;	
     }	

     void ordenar(int *A,int n){
     int i,j,aux;
       for(i=0;i<n-1;i++)
 		for(j=0;j<n-1;j++) {
			if(A[j]>A[j+1]){
				aux=A[j];
				A[j]=A[j+1];
				A[j+1]=aux;
			}
		}

     }	
     void imprimir(int *A,int n){
      int i,elem_mayoria;
      printf("El arreglo creado es:\n");
      for(i=0;i<n;i++) printf("%d ",A[i]);
      printf("\n");
      }
    

     

     void main(){
     int *A,n,i;
     printf("Ingrese el numero de elementos del arreglo:\n");
     scanf("%d",&n);
     A=(int*)malloc(n*sizeof(int));
     
     //Ingreso aleatorio de elementos en el array A:
      srand(time(NULL));
      for(i=0;i<n;i++)  A[i]=rand()%5;
      
      // Imprimiremos el vector creado, lo ordenaremos:
      imprimir(A,n); 
      ordenar(A,n);

      // La funcion elemayoria() nos devolvera -1 si no existe elemento mayoria
      // o nos devolvera el numero que se repite mas de n/2 veces.
      if(elemayoria(A,n)==-1) printf("No existe elemento mayoria\n");
      else printf("El elemento mayoria es %d\n",elemayoria(A,n));
     }
