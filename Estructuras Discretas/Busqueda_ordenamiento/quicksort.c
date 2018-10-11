#include <stdio.h>
#include<stdlib.h>

	void qs(int lista[],int limite_izq,int limite_der)
	{
	    int izq,der,temporal,pivote;
	    izq=limite_izq;
	    der = limite_der;
	    pivote = lista[(izq+der)/2];
	 
	    do{
	        while(lista[izq]<pivote && izq<limite_der)izq++;
	        while(pivote<lista[der] && der > limite_izq)der--;
	        if(izq <=der)
	        {
	            temporal= lista[izq];
	            lista[izq]=lista[der];
	            lista[der]=temporal;
	            izq++;
	            der--;
	        }
	    }while(izq<=der);
	    if(limite_izq<der){qs(lista,limite_izq,der);}
	    if(limite_der>izq){qs(lista,izq,limite_der);}
	}
	void quicksort(int lista[],int n)
	{
	    qs(lista,0,n-1);
	}

	void main(){
	    int *lista,n,i;
	    printf("Ingrese numero de elementos a ordener:\n");
	    scanf("%d",&n);
	    lista=(int*)malloc(n*sizeof(int));
	    printf("Ingrese elementos:\n");
	    for (i=0; i<n; i++) {
	       scanf("%d",&lista[i]);
	    }
	    printf("Lista Desordenada \n");
	    for (i=0; i<n; i++) {
	        printf("%d",lista[i]);
	        if(i<n-1)
	            printf(",");
	    }
	    printf("\n");
	    quicksort(lista,n);
	    printf("Lista Ordenada \n");
	    for (int i=0; i<n; i++) {
	        printf("%d",lista[i]);
	        if(i<n-1)
	            printf(",");
	    }
	printf("\n");

	}
