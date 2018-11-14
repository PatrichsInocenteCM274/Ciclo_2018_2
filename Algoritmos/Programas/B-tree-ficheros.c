
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
char READ[300]="\0";
char nombre[5]="a.txt";
char texto[4];
#define t 2
int posicion;
int cont_keys=0;
int keys[200];
typedef struct Node {
	struct Node *p;
	struct Node *c[2*t+1];
	int n; 		//Hasta 2t-1
	int leaf;       //Es 1 si es hoja
	int key[2*t];
	FILE *fichero;
	char nombre[5];
	int impreso;    //Si es 1 ha sido ya impreso.
} Node;


typedef struct Tree{
	struct Node *root;
} Tree;


void DISK_READ(Node *x){
	strcat(READ," --> ");
	strcat(READ,x->nombre);
}




void DISK_WRITE(Node *x){
	int i;
	x->fichero= fopen(x->nombre,"w+");
	for(i=1;i<=x->n;i++){
		sprintf(texto, "%d", x->key[i]);
		fputs(strcat(texto,"\n"),x->fichero);
	}
	fclose(x->fichero);
}


Node *ALLOCATE_NODE(){
	int i;
	Node *x;
	x=calloc(1, sizeof(Node));
	strcpy(x->nombre,nombre);
	x->fichero= fopen(x->nombre,"w+");
	fclose(x->fichero);
	nombre[0]++;
	return x;
}


Node *B_TREE_SEARH(Node *x,int k){   // B-tree search busca una key, si esta existe devolvera
	int i=1;                     // el nodo y el indice donde se encuentra.
	while(i<=x->n && k>(x->key[i]) ) 
			i=i+1;
	if(i<=x->n && k==(x->key[i])){
			posicion=i;
			return x;
	}
	else{
		if(x->leaf) 
			return NULL;
		else{
			DISK_READ(x->c[i]);
			return B_TREE_SEARH(x->c[i],k);
		}
	}
}


void B_TREE_CREATE(Tree *tree){
	Node *x;
	x=ALLOCATE_NODE();
	x->fichero=NULL;
	x->leaf=1; //TRUE
	x->n=0;
	DISK_WRITE(x);
	tree->root=x;
}

void B_TREE_SPLIT_CHILD(Tree *tree,Node *x,int i){
	int j;
	Node *z;
	Node *y;
	z=ALLOCATE_NODE();
	y=x->c[i];
	z->leaf=y->leaf;
	z->n=t-1;
	for(j=1; j<=t-1; j++){
		z->key[j]=y->key[j+t];
	}
	if(!(y->leaf)){
		for(j=1; j<=t; j++){
			z->c[j]=y->c[j+t];
		}
	}
	
	y->n=t-1;
	//EN ANALISIS
	for(j=(x->n)+1; j<(i+1); j++){
		
		x->c[j+1]=x->c[j];
		//printf("%d\n",tree->root->n);
	}
	
	//-----------------------------
	x->c[i+1]=z;
	for(j=x->n; j<=i; j++){
		x->key[j+1]=x->key[j];
	}
	x->key[i]=y->key[t];
	
	x->n=(x->n)+1;
	DISK_WRITE(y);
	DISK_WRITE(z);
	DISK_WRITE(x);
}


void B_TREE_INSERT_NONFULL (Tree *tree,Node *x,int k){
	int i;
	i=x->n;
	if(x->leaf){
		while(i>=1 && k<x->key[i]){
				x->key[i+1]=x->key[i];
				i=i-1;
		}
		x->key[i+1]=k;
		x->n=(x->n)+1;
		
		DISK_WRITE(x);
	}
	
	else{	
		while(i>=1 && k<x->key[i]){
				i=i-1;
		}
		i=i+1;
		//DISK_READ(x->c[i]);
		
		if(x->c[i]->n==(2*t-1)){
			B_TREE_SPLIT_CHILD(tree,x,i);
			//printf("%d\n",tree->root->n);
			if(k>x->key[i])
				i=i+1;
		}
		
		B_TREE_INSERT_NONFULL(tree,x->c[i],k);
		
	}

}



void B_TREE_INSERT(Tree *tree, int k){
	Node *r=tree->root,*s;
	if(r->n==(2*t-1)){		
		s=ALLOCATE_NODE();
		tree->root = s;
		s->fichero=NULL;
		s->leaf=0; //FALSE
		s->n=0;
		s->c[1]=r;
		B_TREE_SPLIT_CHILD(tree,s,1);
		B_TREE_INSERT_NONFULL(tree,s,k);
	}
	else{ 
		B_TREE_INSERT_NONFULL(tree,r,k);

		}	
}


void imprime(Node *x){
	Node *busqueda;
	int i;
	printf("\n\tArbol\n-------------------------\n");
	for(i=cont_keys-1;i>=0;i--){
	 	strcat(READ,x->nombre);
		busqueda = B_TREE_SEARH(x,keys[i]);
		printf("%s (%d)\n",READ,keys[i]);
		READ[0]='\0';
	}

}

void ordenar(){
	int i,j,aux;
	for(i=0;i<cont_keys;i++)
		for(j=0;j<cont_keys;j++)
			if(keys[i]<keys[j]){
				aux=keys[i];
				keys[i]=keys[j];
				keys[j]=aux;
			}
}


int main(){	
    	Tree *tree;
	Node *busqueda=NULL;
	B_TREE_CREATE(tree);
    	int op,key_busqueda,num,key,i;
	
	do{
  	 printf("-----------------------------------------------------------\n");
   	printf("\t\tMENU DE B-tree\n");
   	printf("1)  Insertar  \n2)  Busqueda \n3)  Imprimir\n");
	printf("4)  Eliminar\n5)  Salir y borrar ficheros generados\n\nIngrese una opcion:\n");
   	scanf("%d",&op);
   	switch(op){
   		case 1:   printf("Cuantas Keys desea ingresar?\n");
			  scanf("%d",&num);
			  printf("Ingrese las keys:\n");
			  for(i=0;i<num;i++){
				scanf("%d",&key);
				keys[cont_keys]=key;
				B_TREE_INSERT(tree,key);
				cont_keys++;
			  }
			  break;
			  

   		case 2:   printf("Ingrese Key a buscar:\n");
			  scanf("%d",&key_busqueda);
			  strcat(READ,tree->root->nombre);
		          busqueda = B_TREE_SEARH(tree->root,key_busqueda);
			  if(busqueda!=NULL){
				printf("Se encontro! En el nodo: %s ",busqueda->nombre); 
				printf("posicion: %d\n",posicion);
				printf("Su ruta de nodos es:\n");
				puts(READ);
			  }
			  else 
				printf("No se encontro!\n");
			  READ[0]='\0';   //limpia la ruta.
			  break;
		

		case 3:   if(cont_keys!=0){
				ordenar(); //ordena las llaves ingresadas
				printf("llaves:\n");
				for(i=0;i<cont_keys;i++) printf("%d ",keys[i]);
			  	imprime(tree->root);
			  }
			  else
				printf("No hay nodos\n");
			  break;
			 
		case 4:   printf("PROXIMAMENTE,trabajamos en mejorar el sevicio de eliminación.\n");
			  break;


		case 5:  printf("Gracias por usar nuestro Software,Adios.\n");	
			  break;
      
   		default:  printf("Opcion incorrecta,vuelva a intentarlo.\n");	
			  break;
   	}
   
   	}while(op!=5);
	
	// TERMINADO EL PROGRAMA Y BORRAMOS LOS FICHEROS CREADOS:
	nombre[0]='a';
	for(i=0;i<30;i++){
	op=remove(nombre);
	nombre[0]++;
	}
	//------------------------------------------------------
return 0;
}

