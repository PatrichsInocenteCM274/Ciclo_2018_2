#include <stdio.h>
#include<stdlib.h>

typedef struct _nodo{
   int valor;
   struct _nodo *siguiente;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

void MostrarCola(Lista lista) {
   pNodo nodo = lista;

   if(!lista) printf("Cola vacía\n");

   else{
   nodo = lista;

      while(nodo) {
         printf("%d -> ", nodo->valor);
         nodo = nodo->siguiente;
      }	
   printf("NULL\n");
   }
   
}

void encolar(Lista *lista,int v)
{
   pNodo p,q;
   p = (pNodo)malloc(sizeof(tipoNodo));
   q = (pNodo)malloc(sizeof(tipoNodo));
   (*p).valor=v;
   (*p).siguiente=NULL;
   if( *lista == NULL)
	*lista = p;
   else{
	q=*lista;
	while( (*q).siguiente != NULL) q = (*q).siguiente;
	(*q).siguiente = p;
   }	
}

void desencolar(Lista *lista)
{
	pNodo p;
	p=*lista;
 	*lista=p->siguiente;		
	free(p);
}

void main() {
   Lista lista1 = NULL;
   pNodo frente,final;
   int i,v;

for(i=0;i<5;i++){
   printf("Encolando:\n");
   scanf("%d",&v);
   encolar(&lista1,v);
   MostrarCola(lista1);
}
while(lista1!=NULL){
   printf("Desencolando:\n");
   desencolar(&lista1);
   MostrarCola(lista1);
}


}


