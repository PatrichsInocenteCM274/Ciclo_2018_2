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
   if(!actual || actual->valor > v) {
      /* Añadimos la lista a continuación del nuevo nodo */
      nuevo->siguiente = actual; 
      nuevo->anterior = NULL;
      if(actual) actual->anterior = nuevo;
      if(!*lista) *lista = nuevo;
   }
   else {
      /* Avanzamos hasta el último elemento o hasta que el siguiente tenga 
         un valor mayor que v */
      while(actual->siguiente &&actual->siguiente->valor <= v) 
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
      printf("Lista ordenada: ");
      while(nodo) {
         printf("%d -> ", nodo->valor);
         nodo = nodo->siguiente;
      }	
   printf("NULL\n");
   }
   
}

void main() {
   Lista lista = NULL;
   pNodo p;
   int n,i,x;
   printf("Ingrese numero de elementos que existira en la lista:\n");
   scanf("%d",&n);
   // Aqui en cada insercion, se ira ordenando la lista:
   for(i=0;i<n;i++){
      printf("Ingrese el dato del %d nodo:\n",i+1);
      scanf("%d",&x);
      Insertar(&lista,x); // Esta funcion insertara en la posicion correcta para que la lista este ordenada.
   }
   MostrarLista(lista);

}


