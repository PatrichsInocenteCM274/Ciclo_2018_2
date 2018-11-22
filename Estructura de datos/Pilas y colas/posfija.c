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

int desapilar(Lista *lista)
{
	pNodo p;
	p=*lista;
 	*lista=p->siguiente;		
	return p->valor;
}

int verifica(char x){
if(x>=48&&x<=57)return 1; // es numero
else return 0;  // es simbolo
}

int numero(char x){
return x-48; 
}

int operacion(int a,int b,char operando){
switch(operando){
case '+':   return a+b;
case '-':   return a-b;
case '*':   return a*b;
case '/':   return a/b;
}

}

void main() {
   Lista lista1 = NULL;
   char posfija[100];
   int i,v,a,b;
   printf("Ingrese notación posfija:\n");
   gets(posfija);
   for(i=0;posfija[i]!='\0';i++){
	if(verifica(posfija[i])==1) apilar(&lista1,numero(posfija[i]));
	else{
		b=desapilar(&lista1);
		a=desapilar(&lista1);
		apilar(&lista1,operacion(a,b,posfija[i]));
	}

   }
/*
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
*/
  MostrarPila(lista1);
}


