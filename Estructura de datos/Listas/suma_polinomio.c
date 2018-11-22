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
      /* Añadimos la lista a continuación del nuevo nodo */
      nuevo->siguiente = actual; 
      nuevo->anterior = NULL;
      if(actual) actual->anterior = nuevo;
      if(!*lista) *lista = nuevo;

}


void MostrarLista(Lista lista,int n) {
   pNodo nodo = lista;
   int potencia=n;
   if(!lista) printf("Lista vacía\n");

   else{
   nodo = lista;
      while(nodo->anterior) nodo = nodo->anterior;
      while(nodo) {
         printf("(%d)X^%d+ ", nodo->valor,potencia--);
         nodo = nodo->siguiente;
      }	
   printf("\n");
   }
   
}

void sumar(Lista lista1,Lista lista2,int n){
  pNodo actual1,actual2,aux;
  int i;
    /* Colocamos actual1 en la ultima posición de la lista1 */
   actual1 = lista1;
   while(actual1->siguiente) actual1 = actual1->siguiente;
   /* Colocamos actual2 en la  ultima posición de la lista2 */
   actual2 = lista2;
   while(actual2->siguiente) actual2 = actual2->anterior;
   //sumamos!!!
   for(i=0;i<=n;i++){ 
   actual1->valor=actual1->valor+actual2->valor; // AQUI SUMAMOS!!!
   actual1 = actual1->anterior;
   actual2 = actual2->anterior;
   }
}

void main() {
   Lista lista1 = NULL;
   Lista lista2 = NULL;
   pNodo p;
   int n1,n2,i,x;
   printf("Ingrese el grado del primer polinomio:\n");
   scanf("%d",&n1);
   printf("Ingrese el grado del segundo polinomio:\n");
   scanf("%d",&n2);
   // Aqui se insertara cada elemento de la lista1:
   for(i=0;i<=n1;i++){
      printf("Ingrese el coeficiente del grado %d del polinomio1:\n",i);
      scanf("%d",&x);
      Insertar(&lista1,x); 
   }
   // Aqui se insertara cada elemento de la lista2:
   for(i=0;i<=n2;i++){
      printf("Ingrese el coeficiente del grado %d del polinomio2:\n",i);
      scanf("%d",&x);
      Insertar(&lista2,x); 
   }
   printf("Primer Polinomio: ");
   MostrarLista(lista1,n1);
   printf("Segundo polinomio: ");
   MostrarLista(lista2,n2);
   printf("SUMA: ");
   if(n1>=n2){
   sumar(lista1,lista2,n2); //sumamos los polinomios
   MostrarLista(lista1,n1);
   }
   else{
   sumar(lista2,lista1,n1); 
   MostrarLista(lista2,n2);
   }
}


