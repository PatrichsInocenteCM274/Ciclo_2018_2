#include <stdio.h>
#include<stdlib.h>

typedef struct _nodo{
   int valor;
   int eliminado;       // sera 0 si no esta eliminado y 1 si lo esta.
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

void marcar(Lista lista,int x)
{
	pNodo a,p,b;
	p=lista_buscar(&lista,x);
        (p->eliminado)=1;		
}


void main() {
   Lista lista1 = NULL;
   pNodo busca,a,b;
   int n1,i,x,v,op,contador_marcados=0;
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
//---------MENU DE ELIMINACION----------------------
   printf("-----------------------------------------------------------\n");
   do{
   printf("\t\tMENU DE ELIMINACION\n1) Eliminar valor \n2) No eliminar mas valores\nIngrese Opcion:\n");
   scanf("%d",&op);
   switch(op){
   	case 1:   printf("Ingrese valor a eliminar:\n");
		  scanf("%d",&x);
		  marcar(lista1,x);
                  contador_marcados++;
		  break;
   	case 2:   printf("Eliminacion terminada\n");
		  break;
   	default:  printf("Ingrese opcion correcta!\n");
		  break;
   }
   
   }while(op!=2);
   printf("-----------------------------------------------------------\n");
   if(contador_marcados>=(n1-contador_marcados)){
   	busca=lista1;
   	while(busca){
 	if((busca->eliminado)==1){
		a=lista_buscar_anterior(&lista1,busca->valor);
		b=lista_buscar_posterior(&lista1,busca->valor);
 	
		if(a==NULL && b==NULL){
			lista1=NULL;
		}
		else{
			if( a == NULL){
			lista1=b;
			b->anterior=NULL;
			}

			if( b == NULL){
			a->siguiente=NULL;
			}

			if(a!=NULL && b!=NULL){
			a->siguiente = busca->siguiente;
			b->anterior=busca->anterior;
			}
		}
		busca->siguiente=b;
	}
	busca=busca->siguiente;
	}		
   	printf("El numero de elementos eliminados es mayor o igual a los no-eliminados\nPor lo tanto se eliminan,Resultado:\n");
        MostrarLista(lista1);
   }
   else{ 
   printf("El numero de elementos eliminados es menor a los no-eliminados\nPor lo tanto no se eliminan Resultado:\n");
   MostrarLista(lista1);
   }
}


