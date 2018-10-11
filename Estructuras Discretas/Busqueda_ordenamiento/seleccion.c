#include<stdio.h>
#include<stdlib.h>
int ordenamientoporSeleccion (int *array,int n){

	int i, j,t, aux, posmen;
	for (i=0; i<n-1; i++){
	posmen=i;
		for (j=i+1; j<n; j++){
			if (array[j]<=array[posmen])
				posmen=j;
		}	
		if (i!=posmen){
			aux=array[posmen];
			array[posmen]=array[i];
			array[i]=aux;
		}
	}
}


//Funcion Principal
void main(){
      int *array,i,n;
      printf("Ingrese numero de elementos:\n");
      scanf("%d", &n);
      printf("Ingresa elementos:\n");
      array=(int*)malloc(n*sizeof(int));
      for (i=0;i<n;i++) scanf("%d", &array[i]);
      ordenamientoporSeleccion(array,n);	
      printf("lista ordenada:\n");
      for (i=0;i<n;i++){
        printf("%d ", array[i]);
      }
      printf("\n");
	
}
