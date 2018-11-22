
   #include <stdio.h>
    #include<stdlib.h>

//Busca la posicion
int busquedaBinaria(int *a, int n,int x){

	int inf=0, sup=n-1, med;
	int i=0;
	
	while(inf<=sup){
	
		med=(inf+sup)/2;
		
		i++;
		
		if(a[med]==x){
			return med;
		
		}else if(x<a[med]){
				sup=med-1;
			}else{
				inf=med+1;
			}			
	}
	return -1;	
}


//Funcion principal
int main(){

      int *array,i,n,pos,x;
      printf("Ingrese numero de elementos:\n");
      scanf("%d", &n);
      printf("Ingresa elementos:\n");
      array=(int*)malloc(n*sizeof(int));
      for (i=0;i<n;i++) scanf("%d", &array[i]);
      printf("Ingrese el numero que se desea buscar su posicion: \n");
      scanf("%d", &x);
      pos=busquedaBinaria(array,n, x);
	if(pos==-1){
		printf("\nNo se encuentra el numero\n");	
	}else{
	
		printf("El numero %d esta en la posicion: %d\n",x,pos+1);
	
	}
	
	
}
