#include <stdio.h>
#include<stdlib.h>

typedef struct _nodo{
   int valor;
   struct _nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

void MostrarPila(Lista lista) {
   pNodo nodo = lista;

   if(!lista) printf("Pila vacía\n");

   else{
   nodo = lista;

      while(nodo) {
         printf("%d -> ", nodo->valor);
         nodo = nodo->siguiente;
      }	
   printf("NULL\n");
   }
   
}

void apilar(Lista *lista,int v)
{
   pNodo p;
   p = (pNodo)malloc(sizeof(tipoNodo));
   (*p).valor=v;
   (*p).siguiente=*lista; 	
   *lista=p; 
 
}

void desapilar(Lista *lista)
{
	pNodo p;
	p=*lista;
 	*lista=p->siguiente;		
	free(p);
}

void main() {
   Lista lista1 = NULL;
   pNodo b;
   int i,v;

for(i=0;i<5;i++){
   printf("APILANDO:\n");
   scanf("%d",&v);
   apilar(&lista1,v);
   MostrarPila(lista1);
}
while(lista1!=NULL){
   printf("Desapilando:\n");
   desapilar(&lista1);
   MostrarPila(lista1);
}


}


