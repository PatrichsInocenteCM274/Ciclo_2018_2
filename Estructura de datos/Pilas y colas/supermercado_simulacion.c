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
   Lista cola1 = NULL,cola2=NULL,cola3=NULL;    // ESTAS SERAN LAS COLAS DE LAS CAJAS
   Lista carritos=NULL;                        // AQUI SE TENDRA UNA PILA DE CARRITOS
   int i,v,op,num;
   //INICIALIZANDO CARRITOS:
   for(i=0;i<25;i++){
   apilar(&carritos,i+1);
   }
   
   
   do{
   printf("-----------------------------------------------------------\n");
   printf("\t\tMENU DE SIMULACION\n");
   printf("Estado inicial de carritos:\n");
   MostrarPila(carritos);
   printf("1) Ingresa un cliente a la tienda \n2) Un cliente desea hacer cola para pagar \n3) Un cliente paga en la caja\n4)Salir de simulacion\nIngrese una opcion:\n");
   scanf("%d",&op);
   switch(op){
   	case 1:   
		  desapilar(&carritos);
		  printf("Has quitado un carrito,estado final de carritos:\n");
		  MostrarPila(carritos);
		  break;
   	case 2:   printf("Ingrese a que cola desea ingresar (1,2 o 3):\n");
		  scanf("%d",&num);
		  if(num==1) encolar(&cola1,1);  // 1 sigificara que hay una persona
		  if(num==2) encolar(&cola2,1);  // 1 sigificara que hay una persona	
		  if(num==3) encolar(&cola3,1);  // 1 sigificara que hay una persona
                  
  		  printf("estado final de colas:\nCola1:");
                  MostrarCola(cola1);
		  printf("Cola2:");
		  MostrarCola(cola2);
                  printf("Cola3:");
		  MostrarCola(cola3);
		  break;

	case 3:   
		  break;
	case 4:   printf("Gracias por usar la simulacion\n");
		  break;
      
   	default:  printf("opcion incorrecta\n");
		  break;
   }
   
   }while(op!=4);

}


