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

void lista_insertar_comienzo(Lista *lista,int v)
{
   pNodo p;
   p = (pNodo)malloc(sizeof(tipoNodo));
   (*p).valor=v;
   (*p).siguiente=*lista; //pL 
   (*p).anterior=NULL;
   if(*lista != NULL)
      (**lista).anterior=p;	
   *lista=p; //lista apunta a todo el nodo , el cual tiene una dir de memoria
 
}



void lista_insertar_final(Lista *lista,int v)
{
   pNodo p,q;
   p = (pNodo)malloc(sizeof(tipoNodo));
   q = (pNodo)malloc(sizeof(tipoNodo));
   (*p).valor=v;
   (*p).siguiente=NULL;
   (*p).anterior=NULL;
   if( *lista == NULL)
	*lista = p;
   else{
	q=*lista;
	while( (*q).siguiente != NULL) q = (*q).siguiente;
	(*q).siguiente = p;
	(*p).anterior = q;
   }	
}


 
pNodo lista_buscar(Lista *lista,int x)
{
   pNodo p;
   if( *lista == NULL) return NULL;
   else{
	p = *lista;
	while ( p != NULL && (*p).valor !=x ) p = (*p).siguiente;
	return p;	
   }
}
 
pNodo lista_buscar_anterior(Lista *lista,int x)
{
	pNodo a,p;
	a=NULL;
	p=*lista;
 
	while ( (*p).valor !=x )
	{
		a = p ;
		p = (*p).siguiente;
	}
	return a;
}
 
pNodo lista_buscar_posterior(Lista *lista,int x)
{
	pNodo a,p;
	a=NULL;
	p=*lista;
 
	while ( (*p).valor !=x )
	{
		p = (*p).siguiente;
	}
	a=(*p).siguiente;
	return a;
}
 
void lista_eliminar(Lista lista,Lista *lista1,int x)
{
	pNodo a,p,b;
	p=lista_buscar(&lista,x);
 		
	if(  p == NULL)
	printf("El elemento no esta en la lista\n");
	else	
	{
		a=lista_buscar_anterior(&lista,x);
		b=lista_buscar_posterior(&lista,x);
 	
	if(a==NULL && b==NULL){
			*lista1=NULL;
	}
	else{
		if( a == NULL){
			*lista1=b;
			b->anterior=NULL;
			}

		if( b == NULL){
			a->siguiente=NULL;
			}

		if(a!=NULL && b!=NULL){
			a->siguiente = p->siguiente;
			b->anterior=p->anterior;
		}
	}
		
	free(p);
	}
}


void main() {
   Lista lista1 = NULL;
   pNodo b;
   int n1,n2,i,x,v;
   printf("Ingrese numero de elementos que existira en la lista:\n");
   scanf("%d",&n1);
//----- Aqui se insertara cada elemento de la lista:------
   for(i=0;i<n1;i++){
      printf("Ingrese el dato del %d nodo de la lista1:\n",i+1);
      scanf("%d",&x);
      Insertar(&lista1,x); 
   }
   printf("Lista: ");
   MostrarLista(lista1);
//-----------------------------------------------------------

//----------INSERTANDO AL COMIENZO-----------
   printf("Inserte al comienzo:\n");
   scanf("%d",&v);
   lista_insertar_comienzo(&lista1,v);
   MostrarLista(lista1);
   scanf("%d",&v);
   lista_insertar_comienzo(&lista1,v);
   MostrarLista(lista1);
//-------------------------------------------

//----------INSERTANDO AL FINAL-----------
   printf("Inserte al final:\n");
   scanf("%d",&v);
   lista_insertar_final(&lista1,v);
   MostrarLista(lista1);
   scanf("%d",&v);
   lista_insertar_final(&lista1,v);
   MostrarLista(lista1);
   printf("Ingrese valor a buscar:\n");
   scanf("%d",&x);
//------------------------------------------

//----------BUSCANDO-------------------------
   b=lista_buscar(&lista1,x);
   if(b == NULL)
       printf("El elemento no está en la lista.\n");
   else{
    	printf("El elemento sí está en la lista.\n");
    	b = lista_buscar_anterior(&lista1,x);
    	if(b == NULL)
    	printf("No hay anterior.\n");
    	else
    	printf("El anterior es %d\n",(*b).valor);
    	b = lista_buscar_posterior(&lista1,x);
    	if(b == NULL)
    	printf("No hay posterior.\n");
    	else
    	printf("El posterior es %d\n",(*b).valor);
    }
//-----------------------------------------------


//---------ELIMINANDO----------------------
   printf("Ingrese valor a eliminar:\n");
   scanf("%d",&x);
   lista_eliminar(lista1,&lista1,x);
   MostrarLista(lista1);
   printf("Ingrese valor a eliminar:\n");
   scanf("%d",&x);
   lista_eliminar(lista1,&lista1,x);
   MostrarLista(lista1);
   printf("Ingrese valor a eliminar:\n");
   scanf("%d",&x);
   lista_eliminar(lista1,&lista1,x);
   MostrarLista(lista1);
//-------------------------------------------
}


