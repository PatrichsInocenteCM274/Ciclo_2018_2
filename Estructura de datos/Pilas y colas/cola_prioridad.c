#include <stdio.h>
#include<stdlib.h>

typedef struct _nodo{
   int valor;
   int prioridad;
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
         printf("%d(pri:%d) -> ", nodo->valor,nodo->prioridad);
         nodo = nodo->siguiente;
      }	
   printf("NULL\n");
   }
   
}


void encolar_prioridad(Lista *lista,int v,int prioridad)
{
   pNodo p,q,aux;
   p = (pNodo)malloc(sizeof(tipoNodo));
   q = (pNodo)malloc(sizeof(tipoNodo));
   aux = (pNodo)malloc(sizeof(tipoNodo));
   (*p).valor=v;
   (*p).prioridad=prioridad;
   (*p).siguiente=NULL;
   if( *lista == NULL)
	*lista = p;
   else{
	q=*lista;
        if((*q).prioridad<(*p).prioridad){
					*lista = p;
					(*p).siguiente=q;
					}
	else{
	while((*q).siguiente!=NULL&&((*q).siguiente)->prioridad>=(*p).prioridad) q = (*q).siguiente;
	(*p).siguiente=(*q).siguiente;
	(*q).siguiente = p;
	}
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
   int i,v,prioridad;

for(i=0;i<5;i++){
   printf("Ingrese elemento a encolar y su prioridad:\n");
   scanf("%d%d",&v,&prioridad);
   encolar_prioridad(&lista1,v,prioridad);
   MostrarCola(lista1);
}
/*
while(lista1!=NULL){
   printf("Desencolando:\n");
   desencolar(&lista1);
   MostrarCola(lista1);
}*/


}


