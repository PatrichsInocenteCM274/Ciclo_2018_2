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

void ensamblar(Lista lista1,Lista lista2){
  pNodo actual1,actual2,aux;
    /* Colocamos actual1 en la ultima posición de la lista1 */
   actual1 = lista1;
   while(actual1->siguiente) actual1 = actual1->siguiente;
   /* Colocamos actual2 en la primera posición de la lista2 */
   actual2 = lista2;
   while(actual2->anterior) actual2 = actual2->anterior;
   //Ensamblamos!!!
   aux=actual1->siguiente;
   actual1->siguiente=actual2;
   actual2->anterior=aux;
}

void main() {
   Lista lista1 = NULL;
   Lista lista2 = NULL;
   pNodo p;
   int n1,n2,i,x;
   printf("Ingrese numero de elementos que existira en la Primera lista:\n");
   scanf("%d",&n1);
   printf("Ingrese numero de elementos que existira en la Segunda lista:\n");
   scanf("%d",&n2);
   // Aqui se insertara cada elemento de la lista1:
   for(i=0;i<n1;i++){
      printf("Ingrese el dato del %d nodo de la lista1:\n",i+1);
      scanf("%d",&x);
      Insertar(&lista1,x); 
   }
   // Aqui se insertara cada elemento de la lista2:
   for(i=0;i<n2;i++){
      printf("Ingrese el dato del %d nodo de la lista 2:\n",i+1);
      scanf("%d",&x);
      Insertar(&lista2,x); 
   }
   printf("Primera Lista: ");
   MostrarLista(lista1);
   printf("Segunda Lista: ");
   MostrarLista(lista2);
   ensamblar(lista1,lista2); //Ensamblamos las listas! La lista 1 sera la que acoja a lista2
   printf("Lista Unida: ");
   MostrarLista(lista1); // mostramos lista 1 ya que esta adherio a lista 2.
}


