#include <stdio.h>
#include<stdlib.h>

typedef struct _nodo{
   int valor;
   struct _nodo *siguiente;
   struct _nodo *anterior;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;

void Insertar(Lista *lista, int v) {
   pNodo nuevo, actual;

   /* Crear un nodo nuevo */
   nuevo = (pNodo)malloc(sizeof(tipoNodo));
   nuevo->valor = v;
   
   /* Colocamos actual en la primera posición de la lista */
   actual = *lista;
   if(actual) while(actual->anterior) actual = actual->anterior;
   /* Si la lista está vacía o el primer miembro es mayor que el nuevo */
   if(!actual) {
      /* Añadimos la lista a continuación del nuevo nodo */
      nuevo->siguiente = actual; 
      nuevo->anterior = NULL;
      if(actual) actual->anterior = nuevo;
      if(!*lista) *lista = nuevo;
   }
   else {
      /* Avanzamos hasta el último elemento*/
      while(actual->siguiente) 
         actual = actual->siguiente;
      /* Insertamos el nuevo nodo después del nodo anterior */
      nuevo->siguiente = actual->siguiente;
      actual->siguiente = nuevo;
      nuevo->anterior = actual;
      if(nuevo->siguiente) nuevo->siguiente->anterior = nuevo;
   }
}


void MostrarLista(Lista lista) {
   pNodo nodo = lista;

   if(!lista) printf("Lista vacía\n");

   else{
   nodo = lista;
      while(nodo->anterior) nodo = nodo->anterior;
      while(nodo) {
         printf("%d -> ", nodo->valor);
         nodo = nodo->siguiente;
      }	
   printf("NULL\n");
   }
   
}

void visualizarlotes(Lista L,Lista P) {
  int i;
  pNodo nodo = P;
  pNodo busca= L;
   if(!P) printf("Lista P esta vacia, no hay indices y ningun dato de L se imprimira.\n");

   else{
     while(nodo) {
	 for(i=0;i<(nodo->valor)-1;i++){
	   busca = busca->siguiente;
	 }
	 printf("elemento %d de L es:%d\n",nodo->valor,busca->valor);
	 busca= L;
         nodo = nodo->siguiente;
      }	
   }
   
}


void main() {
   Lista L=NULL,P= NULL;
   pNodo b;
   int n1,n2,i,x,v;
 printf("-------------------------------------------------------------\n");
   printf("Ingrese numero de elementos que existira en la lista L:\n");
   scanf("%d",&n1);
//----- Aqui se insertara cada elemento de la lista L:------
   for(i=0;i<n1;i++){
      printf("Ingrese el dato del %d nodo de la lista L:\n",i+1);
      scanf("%d",&x);
      Insertar(&L,x); 
   }
 printf("-------------------------------------------------------------\n");
 printf("Ingrese numero de elementos que existira en la lista P:\n");
   scanf("%d",&n2);
//----- Aqui se insertara cada elemento de la lista P:------
   for(i=0;i<n2;i++){
      printf("Ingrese el dato del %d nodo de la lista P:\n",i+1);
      scanf("%d",&x);
      Insertar(&P,x); 
   }
 printf("-------------------------------------------------------------\n");
   printf("Lista L:\n");
   MostrarLista(L);
   printf("Lista P:\n");
   MostrarLista(P);
 printf("-------------------------------------------------------------\n");
    printf("Elementos de L que estan en posiciones dadas por P:\n");
   visualizarlotes(L,P);

}


