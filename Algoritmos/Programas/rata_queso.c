#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//--------------------PREPARANDO FUNCION GETCH() ----------------------	
// Esta funcion nos permitira RECIBIR un caracter sin necesidad del enter.
static struct termios old, new;
void initTermios(int echo){

  	tcgetattr(0, &old); 
 	new = old; 
  	new.c_lflag &= ~ICANON; 
  	if (echo) {
      		new.c_lflag |= ECHO; 
  	} else {
      		new.c_lflag &= ~ECHO; 
  	}
  	tcsetattr(0, TCSANOW, &new); 
}

void resetTermios(void){

  	tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo){
  	char ch;
  	initTermios(echo);
  	ch = getchar();
  	resetTermios();
  	return ch;
}

/* Read 1 character without echo */
char getch(void){ 

  	return getch_(0);
}

//---------------------------------------------------------------------


typedef struct Node {
	struct Node *next;
	struct Node *prev;
	int value;
} Node;


typedef struct List {
	 int count;
	struct Node *first;
	struct Node *last;
	int color;
	int d,f;
	int G,H;
	int fila;
        int columna;
	struct List *pi;
} List;


List *List_create(){
	return calloc(1, sizeof(List));
}

void List_insertar(List *list, int value){
	Node *node = calloc(1, sizeof(Node));
        node->value = value;
        if(list->last == NULL) {
		list->first = node;
		list->last = node;
        } else {
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}
	list->count++;
        return;
}

void Print_list(List *list){
	Node *p;
	p = list->first;    
	while(p != NULL){
	    	printf("%d; ",p->value);
	    	p = p->next;
	}
	printf("\b\b  \n");
	return;
}



typedef struct QueueNode{
	List *list;
	struct QueueNode *next;
	
} QueueNode;

typedef struct Queue{	
	struct QueueNode *first;
	struct QueueNode *last;
	int size;
} Queue;

Queue *Queue_create(){
	Queue *Q = calloc(1, sizeof(Queue));
	Q->size = 0;
	return Q;
}

void Enqueue(Queue *Q,List *list){
	QueueNode *node = calloc(1, sizeof(QueueNode));
	node->list = list;
	if(Q->last == NULL) {
	  Q->first = node;
	  Q->last = node;
	} else {
	  Q->last->next = node;
	  Q->last = node;
	}
	Q->size++;
	return;
}

List *Dequeue(Queue *Q){
	QueueNode *node = Q->first;
	if(node->next==NULL){
	  Q->first = NULL;
	  Q->last = NULL;
	}
	else
		Q->first = node->next;
	List *l = node->list;
	free(node);
	Q->size--;
	return l;
}

void BFS(List **G,int n,int nod){
	List *s = G[nod];
	int i;
	for(i=1;i<=n;i++){
		List *u = G[i];
		if(u==s)
			continue;
		u->color = 1;
		u->d = INT_MAX;
		u->pi = NULL;
	}
	s->color = 0;
	s->d = 0;
	s->pi = NULL;
	Queue *Q = Queue_create();
	Enqueue(Q,s);
	while(Q->size){
		List *u = Dequeue(Q);
		Node *nd = u->first;
		while(nd!=NULL){
			List *v = G[nd->value];
			if(v->color==1){
				v->color = 0;
				v->d = u->d + 1;
				v->pi = u;
				Enqueue(Q,v);
			}
			u->color = -1;
			nd=nd->next;
		}
	}
}

void DFS_Visit(List **G,int n,List *u,int *time){
	(*time)++;
	u->d = *time;
	u->color = 0;
	Node *nd = u->first;
	while(nd!=NULL){
		List *v = G[nd->value];
		if(v->color==1){
			v->pi = u;
			DFS_Visit(G,n,v,time);
		}
		nd=nd->next;
	}
	u->color = -1;
	(*time)++;
	u->f = *time;
	return;
}

void DFS(int alto,int ancho,List **G,int n,int fq,int cq){
	int i;
	for(i=1;i<=n;i++){
		List *u = G[i];
		u->color = 1;
		u->pi = NULL;
	}
	int time = 0;
	List *u = G[(fq-1)*ancho+cq];      // Busqueda en profundidad del nodo queso.
	DFS_Visit(G,n,u,&time);	           // Busqueda en profundidad del nodo queso.
	for(i=1;i<=n;i++){
		List *u = G[i];
		if(u->color==1)
			DFS_Visit(G,n,u,&time);		
	}
	return;
}

int verifica(int valor,int camino[],int num_listas){
	int i;
	for(i=1;i<=num_listas;i++)
		if(camino[i]==valor) return 0;
	return 1;
}

void actualizar(int alto,int ancho,int mapa[][ancho],int fr,int cr,int fq,int cq){
	FILE* fichero;
	fichero = fopen("Mapa.txt","r");
  	int i,j;
  	for(i=0;i<alto;i++)
			for(j=0;j<ancho;j++)
				fscanf (fichero,"%d",&mapa[i][j]);
  	mapa[fr-1][cr-1]=2;
  	mapa[fq-1][cq-1]=3;
}

void imprimir(int alto,int ancho,int mapa[][ancho]){
  	int i,j;
  	for(i=0;i<alto;i++){
		printf("|");
		for(j=0;j<ancho;j++){
			if(mapa[i][j]==0)printf("    |");
			if(mapa[i][j]==1)printf("####|");
			if(mapa[i][j]==2)printf("-o8 |");
			if(mapa[i][j]==3)printf(" (] |");
			if(mapa[i][j]==4)printf(" x  |");
		}
  	printf("\n");
  	}	

}


void Busquedas(int alto,int ancho,int mapa[][ancho],List **grafo,int fr,int cr,int fq,int cq){
	List *aux;
	int mum_lista_q=(fq-1)*ancho+(cq);
	int mum_lista_r=(fr-1)*ancho+(cr);
	int num_listas=alto*ancho;

//--------------------------------BUSQUEDA BFS -----------------------------

	actualizar(alto,ancho,mapa,fr,cr,fq,cq);
	printf("Por Busqueda BFS:\n");
	BFS(grafo,num_listas,mum_lista_q);  // Aplicando BFS
  	aux=grafo[mum_lista_r];
  	while(aux->pi->pi!=NULL){
  			aux=aux->pi;
  			mapa[aux->fila][aux->columna]=4;
 	}
	imprimir(alto,ancho,mapa);
	printf("Ruta:\n");
	aux=grafo[mum_lista_r];
  	while(aux->pi->pi!=NULL){
  			aux=aux->pi;
  			printf("%d%d ",aux->fila+1,aux->columna+1);
  	}
	printf("\n");
//--------------------------------------------------------------------------

//--------------------------------BUSQUEDA DFS -----------------------------
	actualizar(alto,ancho,mapa,fr,cr,fq,cq);
	printf("\nPor Busqueda DFS:\n");
			
	DFS(alto,ancho,grafo,num_listas,fq,cq);      // Aplicando DFS
	aux=grafo[mum_lista_r];
	while(aux->pi->pi!=NULL){
			aux=aux->pi;
  			mapa[aux->fila][aux->columna]=4;
  	}
	imprimir(alto,ancho,mapa);
	printf("Ruta:\n");
	aux=grafo[mum_lista_r];
  	while(aux->pi->pi!=NULL){
  			aux=aux->pi;
  			printf("%d%d ",aux->fila+1,aux->columna+1);
  	}
	printf("\n");
//--------------------------------------------------------------------------

	actualizar(alto,ancho,mapa,fr,cr,fq,cq);

}



void main(void) {
	int alto=15,ancho=15;
	int fr=4,cr=2,fq=3,cq=10;	
  	int mapa[alto][ancho],i,fil,col;
	int num_listas = alto*ancho;
  	char c;
  	List *grafo[num_listas+1],*aux;
  	for(i=1;i<=num_listas;i++) grafo[i]=List_create();
  	for(i=1;i<=num_listas;i++){
				grafo[i]->fila=((i-1)/ancho); 
				grafo[i]->columna=((i-1)%ancho);
	}
  	actualizar(alto,ancho,mapa,fr,cr,fq,cq);

  //--------------LISTAS DE ADYACENCIA SEGUN EL MAPA----------------------------
  	for(i=1;i<=num_listas;i++){
        	fil=grafo[i]->fila;
        	col=grafo[i]->columna;
		//arriba
		if(fil>0 && mapa[fil-1][col]!=1) List_insertar(grafo[i],i-ancho);
		//izquierda
		if(col>0 && mapa[fil][col-1]!=1) List_insertar(grafo[i],i-1);
		//derecha
		if(col<(ancho-1) && mapa[fil][col+1]!=1) List_insertar(grafo[i],i+1);
		//abajo
		if(fil<(alto-1) && mapa[fil+1][col]!=1) List_insertar(grafo[i],i+ancho);
  	}

  //-----------------------------------------------------------------------------


 	imprimir(alto,ancho,mapa);
        
	while(1){
  		c = getch();
  		if(c=='u'||c=='U'){
			system("@cls||clear");
			if(fq>1&&mapa[fq-2][cq-1]==0)fq--;
			Busquedas(alto,ancho,mapa,grafo,fr,cr,fq,cq);
		}

  		if(c=='n'||c=='N'){
			system("@cls||clear");
			if(fq<alto&&mapa[fq][cq-1]==0)fq++;
			Busquedas(alto,ancho,mapa,grafo,fr,cr,fq,cq);
		}

  		if(c=='h'||c=='H'){
			system("@cls||clear");
			if(cq>1&&mapa[fq-1][cq-2]==0)cq--;
			Busquedas(alto,ancho,mapa,grafo,fr,cr,fq,cq);
		}

  		if(c=='j'||c=='J'){
			system("@cls||clear");
			if(cq<ancho&&mapa[fq-1][cq]==0)cq++;
			Busquedas(alto,ancho,mapa,grafo,fr,cr,fq,cq);
		}

  		if(c=='w'||c=='W'){
			system("@cls||clear");
			if(fr>1&&mapa[fr-2][cr-1]==0)fr--;
			Busquedas(alto,ancho,mapa,grafo,fr,cr,fq,cq);
		}

  		if(c=='z'||c=='Z'){
			system("@cls||clear");
			if(fr<alto&&mapa[fr][cr-1]==0)fr++;
			Busquedas(alto,ancho,mapa,grafo,fr,cr,fq,cq);
		}

  		if(c=='a'||c=='A'){
			system("@cls||clear");
			if(cr>1&&mapa[fr-1][cr-2]==0)cr--;
			Busquedas(alto,ancho,mapa,grafo,fr,cr,fq,cq);
		}

  		if(c=='s'||c=='S'){
			system("@cls||clear");
			if(cr<ancho&&mapa[fr-1][cr]==0)cr++;
			Busquedas(alto,ancho,mapa,grafo,fr,cr,fq,cq);
		}

	}

  return;
} 	
