#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int sub_hor_ant[17],sub_vert_ant[17],vida_sub[17];
int ene_hor_ant[17],ene_vert_ant[17],vida_ene[17];
int vida_raton=900,vida_gato=900;
int bomba1_hor_ant=2,bomba1_vert_ant=5;
int bomba2_hor_ant=7,bomba2_vert_ant=63;
int bomba3_hor_ant=60,bomba3_vert_ant=6;
int bomba4_hor_ant=67,bomba4_vert_ant=58;
int p_hor_ant,p_vert_ant;
int en_hor_ant=61,en_vert_ant=64; // posici{on inicial del enemigo
char menu,posicion1,posicion2,posicion3,posicion4;
int eleccion;
int vida_nuestra_torreAA=900,vida_torre_enemigaCC=900,vida_nuestra_torreBB=900,vida_torre_enemigaDD=900;
char xa[1]="A";
//--------------------PREPARANDO FUNCION GETCH() ----------------------	
// Esta funcion nos permitira RECIBIR un caracter sin necesidad del enter.
/*
    timer0_int() interrupt 1 using 2
    {
    unsigned char temp1;
    unsigned char temp2;
    siguen las sentencias C ejecutables;
    }*/

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
  	//resetTermios();
  	return ch;
}

/* Read 1 character without echo */
char getch(){ 
	
  	return getch_(0);
	
}

//---------------------------------------------------------------------


//--------------------------ESTRUCTURAS NECESARIAS---------------------
//----------------------------PARA EL PROGRAMA-------------------------

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

typedef struct QueueNode{
	List *list;
	struct QueueNode *next;
	
} QueueNode;

typedef struct Queue{	
	struct QueueNode *first;
	struct QueueNode *last;
	int size;
} Queue;

//---------------------------------------------------------------------
//---------------------------------------------------------------------

//--------------------------FUNCIONES NECESARIAS-----------------------
//---------------------PARA EL BFS Y CREACION DE COLAS-----------------

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
//---------------------------------------------------------------------

//--------------------FUNCION BUSQUEDA BFS-----------------------------

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

//---------------------------------------------------------------------

void escribir_personaje(int p_hor,int p_vert,FILE* fichero){
	int a;
	a=fseek(fichero,140*(p_vert_ant)+2*p_hor_ant,SEEK_SET);
	fwrite("0", 1, 1, fichero);
	a=fseek(fichero,140*(p_vert)+2*p_hor,SEEK_SET);
	fwrite("2", 1, 1, fichero);
	p_hor_ant=p_hor;
	p_vert_ant=p_vert;
}


//-------------FUNCIONES DE ACTUALIZACION E IMPRESION EN EL TERMINAL------
void portada_cred();
void portada_r();
void portada_con();
void portada_j();
void ganaste();
void perdiste();

void ganaste(){
	char cadena[200];
	FILE* fichero;	
		eleccion=4;
		fichero = fopen("ganaste.txt","r+");
		system("@cls||clear");
		while(fgets(cadena,140,fichero)!=NULL){
		printf("\t%s",cadena);
		}
	do{
		menu=getch();
	}while(menu!='\n');
}



void perdiste(){
	char cadena[200];
	FILE* fichero;	
		eleccion=4;
		fichero = fopen("perdiste.txt","r+");
		system("@cls||clear");
		while(fgets(cadena,140,fichero)!=NULL){
		printf("\t%s",cadena);
		}
	do{
		menu=getch();
	}while(menu!='\n');
}


void portada_cred(){
	char cadena[200];
	FILE* fichero;	
		eleccion=4;
		fichero = fopen("portada_cred.txt","r+");
		system("@cls||clear");
		while(fgets(cadena,140,fichero)!=NULL){
		printf("\t%s",cadena);
		}
	do{
		menu=getch();
		if(menu=='w')portada_con();
		if(menu=='s')portada_j();
	}while(menu!='\n');

}



void portada_con(){
	char cadena[200];
	FILE* fichero;
	char c;
		eleccion=3;
		fichero = fopen("portada_con.txt","r+");
		system("@cls||clear");
		while(fgets(cadena,140,fichero)!=NULL){
		printf("\t%s",cadena);
		}
	do{
		menu=getch();
		if(menu=='w')portada_r();
		if(menu=='s')portada_cred();
	}while(menu!='\n');

}

void portada_r(){
	char cadena[200];
	FILE* fichero;
		eleccion=2;
		fichero = fopen("portada_r.txt","r+");
		system("@cls||clear");
		while(fgets(cadena,140,fichero)!=NULL){
		printf("\t%s",cadena);
		}
	do{
		menu=getch();
		if(menu=='w')portada_j();
		if(menu=='s')portada_con();
	}while(menu!='\n');

}

void portada_j(){
	char cadena[200];
	FILE* fichero;
	char c;
	     
		eleccion=1;
		fichero = fopen("portada_j.txt","r+");
		system("@cls||clear");
		while(fgets(cadena,140,fichero)!=NULL){
		printf("\t%s",cadena);
		}
	do{
		menu=getch();
		if(menu=='w')portada_cred();
		if(menu=='s')portada_r();
	}while(menu!='\n');

}

void creditos(){
	char cadena[200];
	FILE* fichero;
	char c;    
		eleccion=1;
		fichero = fopen("creditos.txt","r+");
		system("@cls||clear");
		while(fgets(cadena,140,fichero)!=NULL){
		printf("\t%s",cadena);
		}
		do{
			c=getch();
		}while(c!='\n');
		
}

void controles(){
	char cadena[200];
	FILE* fichero;
	char c;    
		eleccion=1;
		fichero = fopen("controles.txt","r+");
		system("@cls||clear");
		while(fgets(cadena,140,fichero)!=NULL){
		printf("\t%s",cadena);
		}
		do{
			c=getch();
		}while(c!='\n');
}

void reglas(){
	char cadena[200];
	FILE* fichero;
	char c;    
		eleccion=1;
		fichero = fopen("reglas.txt","r+");
		system("@cls||clear");
		while(fgets(cadena,140,fichero)!=NULL){
		printf("\t%s",cadena);
		}
		do{
			c=getch();
		}while(c!='\n');
}


void actualizar(int alto,int ancho,char mapa[][ancho],int horizontal,
		int vertical,int p_hor,int p_vert){
	FILE* fichero;
	int a;
	fichero = fopen("mapa_actual.txt","r+");
  	int i,j;
	
	escribir_personaje(p_hor,p_vert,fichero);

  	for(i=0;i<alto;i++){
	      a=fseek(fichero,140*(i+vertical)+2*horizontal,SEEK_SET);
	      for(j=0;j<ancho;j++)
				fscanf (fichero,"%c",&mapa[i][j]);
        }
	fclose(fichero);
}

void	escribir_personajes(){
	int i,a;
	FILE *fichero;
	sub_hor_ant[1]=3 ; sub_vert_ant[1]=16;
	sub_hor_ant[2]=6 ; sub_vert_ant[2]=16;
	sub_hor_ant[3]=2 ; sub_vert_ant[3]=24;
	sub_hor_ant[4]=7 ; sub_vert_ant[4]=24;
	sub_hor_ant[5]=2 ; sub_vert_ant[5]=2;
	sub_hor_ant[6]=7 ; sub_vert_ant[6]=2;
	sub_hor_ant[7]=3 ; sub_vert_ant[7]=8;
	sub_hor_ant[8]=5 ; sub_vert_ant[8]=8;
	sub_hor_ant[9]=7 ; sub_vert_ant[9]=20;
	sub_hor_ant[10]=9 ; sub_vert_ant[10]=20;
	sub_hor_ant[11]=2 ; sub_vert_ant[11]=58;
	sub_hor_ant[12]=6 ; sub_vert_ant[12]=57;
	sub_hor_ant[13]=9 ; sub_vert_ant[13]=50;
	sub_hor_ant[14]=9 ; sub_vert_ant[14]=63;
	sub_hor_ant[15]=5 ; sub_vert_ant[15]=44;
	sub_hor_ant[16]=5 ; sub_vert_ant[16]=33;	

	ene_hor_ant[1]=64 ; ene_vert_ant[1]=33 ;	
	ene_hor_ant[2]=58 ; ene_vert_ant[2]=33 ;
	ene_hor_ant[3]=64 ; ene_vert_ant[3]=45 ;
	ene_hor_ant[4]=58 ; ene_vert_ant[4]=45 ;
	ene_hor_ant[5]=61 ; ene_vert_ant[5]=55 ;
	ene_hor_ant[6]=61 ; ene_vert_ant[6]=59 ;
	ene_hor_ant[7]=64 ; ene_vert_ant[7]=61 ;
	ene_hor_ant[8]=58 ; ene_vert_ant[8]=61 ;
	ene_hor_ant[9]=64 ; ene_vert_ant[9]=63 ;
	ene_hor_ant[10]=58 ; ene_vert_ant[10]=63;
	ene_hor_ant[11]=66 ; ene_vert_ant[11]=8;
	ene_hor_ant[12]=58 ; ene_vert_ant[12]=8;
	ene_hor_ant[13]=66 ; ene_vert_ant[13]=16;
	ene_hor_ant[14]=58 ; ene_vert_ant[14]=16;
	ene_hor_ant[15]=54 ; ene_vert_ant[15]=2;
	ene_hor_ant[16]=60 ; ene_vert_ant[16]=24;
	fichero = fopen("mapa_actual.txt","r+");
	for(i=1;i<=16;i++){
        a=fseek(fichero,140*(sub_vert_ant[i])+2*sub_hor_ant[i],SEEK_SET);
	fwrite(xa, 1, 1, fichero);//escribir subitos
	xa[0]++;
	}
	xa[0]='a';
	for(i=1;i<=16;i++){
   	a=fseek(fichero,140*(ene_vert_ant[i])+2*ene_hor_ant[i],SEEK_SET);
	fwrite(xa, 1, 1, fichero);//escribir subitos
	xa[0]++;
	}
	for(i=1;i<=16;i++){
   	vida_sub[i]=100;
	vida_ene[i]=100; 
	}
	
	fclose(fichero);	
}

void mapita(int alto,int ancho,char mapa[][ancho],int i,int j){
			if(mapa[i][j]=='0')printf("    ");
			if(mapa[i][j]=='1')printf("░##░");
			if(mapa[i][j]=='2')printf("~Ω8>");
			if(mapa[i][j]=='3')printf("*Ö*m");
			if(mapa[i][j]=='4')printf("░░░░");
			if(mapa[i][j]=='5')printf(">--▶");
			if(mapa[i][j]=='6')printf("  ▶ ");
			if(mapa[i][j]=='7')printf("sub*");
			if(mapa[i][j]=='8')printf("ene*");
			if(mapa[i][j]=='9')printf("  | ");
			if(mapa[i][j]=='A')printf("Sub1");
			if(mapa[i][j]=='B')printf("Sub2");
			if(mapa[i][j]=='C')printf("Sub3");
			if(mapa[i][j]=='D')printf("Sub4");
			if(mapa[i][j]=='E')printf("Sub5");
			if(mapa[i][j]=='F')printf("Sub6");
			if(mapa[i][j]=='G')printf("Sub7");
			if(mapa[i][j]=='H')printf("Sub8");
			if(mapa[i][j]=='I')printf("Sub9");
			if(mapa[i][j]=='J')printf("SubA");
			if(mapa[i][j]=='K')printf("SubB");
			if(mapa[i][j]=='L')printf("SubC");
			if(mapa[i][j]=='M')printf("SubD");
			if(mapa[i][j]=='N')printf("SubE");
			if(mapa[i][j]=='O')printf("SubF");
			if(mapa[i][j]=='P')printf("SubG");
			if(mapa[i][j]=='a')printf("Ene1");
			if(mapa[i][j]=='b')printf("Ene2");
			if(mapa[i][j]=='c')printf("Ene3");
			if(mapa[i][j]=='d')printf("Ene4");
			if(mapa[i][j]=='e')printf("Ene5");
			if(mapa[i][j]=='f')printf("Ene6");
			if(mapa[i][j]=='g')printf("Ene7");
			if(mapa[i][j]=='h')printf("Ene8");
			if(mapa[i][j]=='i')printf("Ene9");
			if(mapa[i][j]=='j')printf("EneA");
			if(mapa[i][j]=='k')printf("EneB");
			if(mapa[i][j]=='l')printf("EneC");
			if(mapa[i][j]=='m')printf("EneD");
			if(mapa[i][j]=='n')printf("EneE");
			if(mapa[i][j]=='o')printf("EneF");
			if(mapa[i][j]=='p')printf("EneG");
			if(mapa[i][j]=='q')printf("░AA░");
			if(mapa[i][j]=='r')printf("░BB░");
			if(mapa[i][j]=='s')printf("░CC░");
			if(mapa[i][j]=='t')printf("░DD░");
			if(mapa[i][j]=='u')printf(">>>>");
			if(mapa[i][j]=='v')printf(">>>>");
			if(mapa[i][j]=='w')printf("◄--<");
}

void imprimir(int alto,int ancho,char mapa[][ancho]){
  	int i,j;
	system("@cls||clear");	
	printf("\n\n     VIDA ALIADOS ");
	for(i=0;i<=ancho*2;i++)printf("▓");
	printf("▓  VIDA ENEMIGOS\n");
	char contador='1';
	int indice=1;
  	for(i=0;i<alto;i++){
			if(i==1){
				if(vida_nuestra_torreAA>=100)printf("    TORREAA: %d  ▓",vida_nuestra_torreAA);
				if(vida_nuestra_torreAA<100&&vida_nuestra_torreAA>9)printf("    TORREAA: %d   ▓",vida_nuestra_torreAA);
				if(vida_nuestra_torreAA<=9)printf("    TORREAA: %d    ▓",vida_nuestra_torreAA);
			}
			if(i%2!=0&&i<=3&&i>1){
				if(vida_nuestra_torreBB>=100)printf("    TORREBB: %d  ▓",vida_nuestra_torreBB);
				if(vida_nuestra_torreBB<100&&vida_nuestra_torreBB>9)printf("    TORREBB: %d   ▓",vida_nuestra_torreBB);
				if(vida_nuestra_torreBB<=9)printf("    TORREBB: %d    ▓",vida_nuestra_torreBB);
			}
			if(i%2!=0&&i>4){
				if(vida_sub[indice]>=100)printf("       Sub%c: %d  ▓",contador,vida_sub[indice]);
				if(vida_sub[indice]<100&&vida_sub[indice]>9)printf("       Sub%c: %d   ▓",contador,vida_sub[indice]);
				if(vida_sub[indice]<=9)printf("       Sub%c: %d    ▓",contador,vida_sub[indice]);
												
			}
			
			if(i%2==0)printf("    ------------- ▓");
			for(j=0;j<ancho;j++){
				mapita(alto,ancho,mapa,i,j);
			}
			if(i==1)printf("▓  TORRECC: %d\n",vida_torre_enemigaCC);
  			if(i%2!=0&&i<=3&&i>1)printf("▓  TORREDD: %d\n",vida_torre_enemigaDD);
			if(i%2!=0&&i>4){printf("▓     Ene%c: %d\n",contador,vida_ene[indice]);contador++,indice++;if(contador==':')contador='A';}
			if(i%2==0)printf("▓  -------------\n");
  	}	
	printf("    ------------- ▓");
	for(i=0;i<=ancho*2;i++)printf("▓");
	printf("  -------------\n");
	if(vida_nuestra_torreAA>=100)printf("     RATON : %d  ▓",vida_raton);
	if(vida_nuestra_torreAA<100&&vida_nuestra_torreAA>9)printf("     RATON : %d   ▓",vida_raton);
	if(vida_nuestra_torreAA<=9)printf("     RATON : %d    ▓",vida_raton);
	for(i=0;i<=ancho*2;i++)printf("▓");
	printf("    GATO : %d\n",vida_gato);
}

//---------------------------------------------------------------------


//---------------------FUNCION PRINCIPAL-------------------------------

int main() {
	char cadena[200];
	float tiempo;
	FILE* fichero,*fichero_copia_seguridad;
	int heigth=66,weidth=70;
	int x,y,a,b=1,i,fil,col;
	fichero = fopen("mapa_actual.txt","r+");
	int alto=36,ancho=56,horizontal=0,vertical=0,flag=0;
	int p_hor=7,p_vert=6,en_vert,en_hor;
	char c,li;
	char posicion_nueva,mapa[alto][ancho],revisa;
	int num_listas=heigth*weidth,mum_lista_p,mum_lista_en,mum_lista_en_antig;
	p_hor_ant=p_hor;
	p_vert_ant=p_vert;

//--------- CREACION DEL GRAFO SEGUN "MAPA.txt"-----------------------

	List *grafo[num_listas+1],*aux,*aux1,*auxs[16],*auxe[16],*aux2,*aux3,*aux4,*aux5;
  	for(i=1;i<=num_listas;i++) grafo[i]=List_create();
  	for(i=1;i<=num_listas;i++){
				grafo[i]->fila=((i-1)/weidth); 
				grafo[i]->columna=((i-1)%weidth);
	}

//------------FINAL DE CREACION --------------------------------------

//--------- ADYACENCIAS DEL MAPA SEGUN "MAPA.txt"--------------------------------------------
	for(i=1;i<=num_listas;i++){

        	fil=grafo[i]->fila;
        	col=grafo[i]->columna;
		//arriba
		a=fseek(fichero,140*(fil-1)+2*col,SEEK_SET);
		fscanf (fichero,"%c",&revisa);
		if(fil>0 && revisa!='1' && revisa!='4'&& revisa!='q' && revisa!='r'&&revisa!='s' && revisa!='t') List_insertar(grafo[i],i-weidth);
		//izquierda
		a=fseek(fichero,140*(fil)+2*(col-1),SEEK_SET);
		fscanf (fichero,"%c",&revisa);
		if(col>0 && revisa!='1' && revisa!='4'&& revisa!='q' && revisa!='r'&&revisa!='s' && revisa!='t') List_insertar(grafo[i],i-1);
		//derecha
		a=fseek(fichero,140*(fil)+2*(col+1),SEEK_SET);
		fscanf (fichero,"%c",&revisa);
		if(col<(weidth-1) && revisa!='1' && revisa!='4'&& revisa!='q' && revisa!='r'&&revisa!='s' && revisa!='t') List_insertar(grafo[i],i+1);
		//abajo
		a=fseek(fichero,140*(fil+1)+2*col,SEEK_SET);
		fscanf (fichero,"%c",&revisa);
		if(fil<(heigth-1) && revisa!='1' && revisa!='4'&& revisa!='q' && revisa!='r'&&revisa!='s' && revisa!='t') List_insertar(grafo[i],i+weidth);
  	}
	fclose(fichero);

//-----------FINAL DE ADYACENCIAS-----------------------------------------------------------
	
	//algunas inicializaciones necesarias:
	mum_lista_p=(p_vert-1)*weidth+(p_hor);
	mum_lista_en=(en_vert_ant-1)*weidth+(en_hor_ant);
	BFS(grafo,num_listas,mum_lista_p);//le pasamos la ubicación del ratón en la lista
	portada_j();  //Muestra un castillo y sus opciones.
	while(1){
	if(eleccion==4){creditos();portada_j();}
	if(eleccion==3){controles();portada_j();}
	if(eleccion==2){reglas();portada_j();}
	if(eleccion==1){break;}
	}

	//posicion inicial del enemigo
	fichero = fopen("mapa_actual.txt","r+");
        a=fseek(fichero,140*(en_vert_ant)+2*en_hor_ant,SEEK_SET);
	fwrite("3", 1, 1, fichero);
	fclose(fichero);
	fichero = fopen("mapa_actual.txt","w");
 	fichero_copia_seguridad=fopen("mapa_actual_copia_original.txt","r");
	while(fgets(cadena,140,fichero_copia_seguridad)!=NULL){
					fputs(cadena,fichero);
	}
	fclose(fichero);
	fclose(fichero_copia_seguridad);
	escribir_personajes();//escribe subitos y enemigos
  	actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
 	imprimir(alto,ancho,mapa);
        aux2=grafo[(bomba1_vert_ant-1)*weidth+(bomba1_hor_ant)]; 
        aux3=grafo[(bomba2_vert_ant-1)*weidth+(bomba2_hor_ant)]; 
        aux4=grafo[(bomba3_vert_ant-1)*weidth+(bomba3_hor_ant)]; 
        aux5=grafo[(bomba4_vert_ant-1)*weidth+(bomba4_hor_ant)]; 
	aux=grafo[(en_vert_ant-1)*weidth+(en_hor_ant)]; 
	for(int k=1;k<=16;k++){
 				auxs[k]=grafo[(sub_vert_ant[k]-1)*weidth+(sub_hor_ant[k])]; 
 				auxe[k]=grafo[(ene_vert_ant[k]-1)*weidth+(ene_hor_ant[k])];
 	}	
	while(1){
	//-------------CONTROL DE PERSONAJE ----------------------------------------------

  		
		c = getch();

  		if(c=='w'||c=='W'){
			fichero = fopen("mapa_actual.txt","r+");
			a=fseek(fichero,140*(p_vert-1)+2*p_hor,SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			fclose(fichero);
			if(vertical>0&&posicion_nueva=='0'){ vertical--;p_vert--;}
			else if(posicion_nueva=='0') p_vert--;
			mum_lista_p=(p_vert-1)*weidth+(p_hor);
			BFS(grafo,num_listas,mum_lista_p); 			
			actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
			imprimir(alto,ancho,mapa);

		}
  		if(c=='s'||c=='S'){
			fichero = fopen("mapa_actual.txt","r+");
			a=fseek(fichero,140*(p_vert+1)+2*p_hor,SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			fclose(fichero);
			if(vertical<(66-alto)&&posicion_nueva=='0'){vertical++;p_vert++;}
			else if(posicion_nueva=='0')  p_vert++;
			mum_lista_p=(p_vert-1)*weidth+(p_hor);
			BFS(grafo,num_listas,mum_lista_p); 
			actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
			imprimir(alto,ancho,mapa);

		}
  		if(c=='a'||c=='A'){
			fichero = fopen("mapa_actual.txt","r+");
			a=fseek(fichero,140*(p_vert)+2*(p_hor-1),SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			fclose(fichero);
			if(horizontal>0&&posicion_nueva=='0'){horizontal--;p_hor--;}
			else if(posicion_nueva=='0') p_hor--;	
			mum_lista_p=(p_vert-1)*weidth+(p_hor);
			BFS(grafo,num_listas,mum_lista_p); 
			actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
			imprimir(alto,ancho,mapa);

		}
  		if(c=='d'||c=='D'){
			fichero = fopen("mapa_actual.txt","r+");
			a=fseek(fichero,140*(p_vert)+2*(p_hor+1),SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			fclose(fichero);
			if(horizontal<(70-28)&&posicion_nueva=='0'){horizontal++;p_hor++;}
			else if(posicion_nueva=='0') p_hor++;
			mum_lista_p=(p_vert-1)*weidth+(p_hor);
			BFS(grafo,num_listas,mum_lista_p); 		
			actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
			imprimir(alto,ancho,mapa);
		}
		
		if(c=='k'||c=='K'){
			fichero = fopen("mapa_actual.txt","r+");
			a=fseek(fichero,140*(p_vert-1)+2*p_hor,SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			if(posicion_nueva>='a'&&posicion_nueva<='p')vida_ene[posicion_nueva-96]=vida_ene[posicion_nueva-96]-10;
			if(posicion_nueva!='1'&&posicion_nueva!='4'){
				a=fseek(fichero,140*(p_vert-1)+2*p_hor,SEEK_SET);
				fwrite("u", 1, 1, fichero);
			}
			a=fseek(fichero,140*(p_vert)+2*(p_hor-1),SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			if(posicion_nueva>='a'&&posicion_nueva<='p')vida_ene[posicion_nueva-96]=vida_ene[posicion_nueva-96]-10;
			if(posicion_nueva!='1'&&posicion_nueva!='4'){
				a=fseek(fichero,140*(p_vert)+2*(p_hor-1),SEEK_SET);
				fwrite("u", 1, 1, fichero);
			}
			a=fseek(fichero,140*(p_vert+1)+2*p_hor,SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			if(posicion_nueva>='a'&&posicion_nueva<='p')vida_ene[posicion_nueva-96]=vida_ene[posicion_nueva-96]-10;
			if(posicion_nueva!='1'&&posicion_nueva!='4'){
				a=fseek(fichero,140*(p_vert+1)+2*p_hor,SEEK_SET);
				fwrite("u", 1, 1, fichero);
			}
			a=fseek(fichero,140*(p_vert)+2*(p_hor+1),SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			if(posicion_nueva>='a'&&posicion_nueva<='p')vida_ene[posicion_nueva-96]=vida_ene[posicion_nueva-96]-10;
			if(posicion_nueva!='1'&& posicion_nueva!='4'){
				a=fseek(fichero,140*(p_vert)+2*(p_hor+1),SEEK_SET);
				fwrite("u", 1, 1, fichero);
			}
			fclose(fichero);
			actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
			imprimir(alto,ancho,mapa);
			while(1){
				c=getch();
				if(c=='t')			
				break;
			}
			fichero = fopen("mapa_actual.txt","r+");
			a=fseek(fichero,140*(p_vert-1)+2*p_hor,SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			if(posicion_nueva=='u'){
				a=fseek(fichero,140*(p_vert-1)+2*p_hor,SEEK_SET);
				fwrite("0", 1, 1, fichero);
			}
			a=fseek(fichero,140*(p_vert)+2*(p_hor-1),SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			if(posicion_nueva=='u'){
				a=fseek(fichero,140*(p_vert)+2*(p_hor-1),SEEK_SET);
				fwrite("0", 1, 1, fichero);
			}
			a=fseek(fichero,140*(p_vert+1)+2*p_hor,SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			if(posicion_nueva=='u'){
				a=fseek(fichero,140*(p_vert+1)+2*p_hor,SEEK_SET);
				fwrite("0", 1, 1, fichero);
			}
			a=fseek(fichero,140*(p_vert)+2*(p_hor+1),SEEK_SET);
			fscanf (fichero,"%c",&posicion_nueva);
			if(posicion_nueva=='u'){
				a=fseek(fichero,140*(p_vert)+2*(p_hor+1),SEEK_SET);
				fwrite("0", 1, 1, fichero);
			}
			fclose(fichero);
			actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
			imprimir(alto,ancho,mapa);	
		}
	//-------------FINAL DE CONTROL DE PERSONAJE -------------------------------------------

		if(c=='t'||c=='T'){
		//-------------MUESTREO DE ENEMIGOS -------------------------------------------	
				BFS(grafo,num_listas,mum_lista_p);		
  				if(aux->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					aux=aux->pi;
					a=fseek(fichero,140*(aux->fila)+2*(aux->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(en_vert_ant)+2*(en_hor_ant),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(aux->pi->fila)+2*(aux->pi->columna),SEEK_SET);
					fwrite("3", 1, 1, fichero);//imprime el símbolo del ratón
					en_vert_ant=aux->pi->fila;
					en_hor_ant=aux->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
 				
 				BFS(grafo,num_listas,(60-1)*weidth+(67));
				xa[0]='A';
 				for(int k=1;k<=8;k++){		
  				if(auxs[k]->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					auxs[k]=auxs[k]->pi;
					a=fseek(fichero,140*(auxs[k]->fila)+2*(auxs[k]->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(sub_vert_ant[k])+2*(sub_hor_ant[k]),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(auxs[k]->pi->fila)+2*(auxs[k]->pi->columna),SEEK_SET);
					fwrite(xa, 1, 1, fichero);//imprime el símbolo del subdito
					sub_vert_ant[k]=auxs[k]->pi->fila;
					sub_hor_ant[k]=auxs[k]->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
				xa[0]++;
 				}

 				BFS(grafo,num_listas,(8-1)*weidth+(63));
				xa[0]='I';
 				for(int k=9;k<=16;k++){		
  				if(auxs[k]->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					auxs[k]=auxs[k]->pi;
					a=fseek(fichero,140*(auxs[k]->fila)+2*(auxs[k]->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(sub_vert_ant[k])+2*(sub_hor_ant[k]),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(auxs[k]->pi->fila)+2*(auxs[k]->pi->columna),SEEK_SET);
					fwrite(xa, 1, 1, fichero);//imprime el símbolo del subdito
					sub_vert_ant[k]=auxs[k]->pi->fila;
					sub_hor_ant[k]=auxs[k]->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
				xa[0]++;
 				}
 				
 				BFS(grafo,num_listas,(8-1)*weidth+(5));
				xa[0]='a';
 				for(int k=1;k<=8;k++){		
  				if(auxe[k]->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					auxe[k]=auxe[k]->pi;
					a=fseek(fichero,140*(auxe[k]->fila)+2*(auxe[k]->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(ene_vert_ant[k])+2*(ene_hor_ant[k]),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(auxe[k]->pi->fila)+2*(auxe[k]->pi->columna),SEEK_SET);
					fwrite(xa, 1, 1, fichero);//imprime el símbolo del enemigo
					ene_vert_ant[k]=auxe[k]->pi->fila;
					ene_hor_ant[k]=auxe[k]->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
				xa[0]++;
 				}

				BFS(grafo,num_listas,(60-1)*weidth+(5));
				xa[0]='i';
 				for(int k=9;k<=16;k++){		
  				if(auxe[k]->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					auxe[k]=auxe[k]->pi;
					a=fseek(fichero,140*(auxe[k]->fila)+2*(auxe[k]->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(ene_vert_ant[k])+2*(ene_hor_ant[k]),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(auxe[k]->pi->fila)+2*(auxe[k]->pi->columna),SEEK_SET);
					fwrite(xa, 1, 1, fichero);//imprime el símbolo del enemigo
					ene_vert_ant[k]=auxe[k]->pi->fila;
					ene_hor_ant[k]=auxe[k]->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
				xa[0]++;
 				}
 				
 				BFS(grafo,num_listas,(ene_vert_ant[9]-1)*weidth+(ene_hor_ant[9]));
 				if(aux2->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					aux2=aux2->pi;
					a=fseek(fichero,140*(aux2->fila)+2*(aux2->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(bomba1_vert_ant)+2*(bomba1_hor_ant),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(aux2->pi->fila)+2*(aux2->pi->columna),SEEK_SET);
					fwrite("5", 1, 1, fichero);//imprime el símbolo del ratón
					bomba1_vert_ant=aux2->pi->fila;
					bomba1_hor_ant=aux2->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
 				
 			        BFS(grafo,num_listas,(ene_vert_ant[3]-1)*weidth+(ene_hor_ant[3]));
 				if(aux3->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					aux3=aux3->pi;
					a=fseek(fichero,140*(aux3->fila)+2*(aux3->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(bomba2_vert_ant)+2*(bomba2_hor_ant),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(aux3->pi->fila)+2*(aux3->pi->columna),SEEK_SET);
					fwrite("5", 1, 1, fichero);//imprime el símbolo del ratón
					bomba2_vert_ant=aux3->pi->fila;
					bomba2_hor_ant=aux3->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
 			
 			        BFS(grafo,num_listas,(sub_vert_ant[1]-1)*weidth+(sub_hor_ant[1]));
 				if(aux4->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					aux4=aux4->pi;
					a=fseek(fichero,140*(aux4->fila)+2*(aux4->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(bomba3_vert_ant)+2*(bomba3_hor_ant),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(aux4->pi->fila)+2*(aux4->pi->columna),SEEK_SET);
					fwrite("w", 1, 1, fichero);//imprime el símbolo del ratón
					bomba3_vert_ant=aux4->pi->fila;
					bomba3_hor_ant=aux4->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
				
 			        BFS(grafo,num_listas,(sub_vert_ant[9]-1)*weidth+(sub_hor_ant[9]));
 				if(aux5->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					aux5=aux5->pi;
					a=fseek(fichero,140*(aux5->fila)+2*(aux5->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(bomba4_vert_ant)+2*(bomba4_hor_ant),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(aux5->pi->fila)+2*(aux5->pi->columna),SEEK_SET);
					fwrite("w", 1, 1, fichero);//imprime el símbolo del ratón
					bomba4_vert_ant=aux5->pi->fila;
					bomba4_hor_ant=aux5->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				} 			 				
				/*if(vida_nuestra_torreAA>0)
 				vida_nuestra_torreAA--;
				if(vida_torre_enemigaCC>0)
				vida_torre_enemigaCC++;*/

		//vida_torre_enemigaCC=vida_torre_enemigaCC-100;	
		//vida_torre_enemigaDD=vida_torre_enemigaDD-100;
		
				actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
				imprimir(alto,ancho,mapa);
				if(vida_nuestra_torreAA<=0 && vida_nuestra_torreBB<=0)
				{
		 		 perdiste();
				}
				if(vida_torre_enemigaCC<=0 && vida_torre_enemigaDD<=0 )
				{
				  ganaste();
				}
				fichero = fopen("mapa_actual.txt","r+");
				a=fseek(fichero,140*(7)+2*(4),SEEK_SET);
				fscanf (fichero,"%c",&posicion1);
				a=fseek(fichero,140*(59)+2*(4),SEEK_SET);
				fscanf (fichero,"%c",&posicion2);
				a=fseek(fichero,140*(7)+2*(62),SEEK_SET);
				fscanf (fichero,"%c",&posicion3);
				a=fseek(fichero,140*(59)+2*(66),SEEK_SET);
				fscanf (fichero,"%c",&posicion4);
				fclose(fichero);
				if(posicion1>='a'&&posicion1<='p'){
					if(vida_nuestra_torreAA>0)
					vida_nuestra_torreAA=vida_nuestra_torreAA-vida_ene[posicion1-96]/4;
					if(vida_nuestra_torreAA<0)vida_nuestra_torreAA=0;
					}
				if(posicion2>='a'&&posicion2<='p'){
					if(vida_nuestra_torreBB>0)
					vida_nuestra_torreBB=vida_nuestra_torreBB-vida_ene[posicion2-96]/4;
					if(vida_nuestra_torreBB<0)vida_nuestra_torreBB=0;			
				}
				if(posicion3>='A'&&posicion3<='P'){
					if(vida_torre_enemigaCC>0)
					vida_torre_enemigaCC=vida_torre_enemigaCC-vida_sub[posicion3-64]/4;
					if(vida_torre_enemigaCC<0)vida_torre_enemigaCC=0;		
				}
				if(posicion4>='A'&&posicion4<='P'){
					if(vida_torre_enemigaDD>0)
					vida_torre_enemigaDD=vida_torre_enemigaDD-vida_sub[posicion4-64]/4;
					if(vida_torre_enemigaDD<0)vida_torre_enemigaDD=0;	
				}
		
			
		//-------------FINAL DE MUESTREO DE ENEMIGOS------------------------------------	
			
		}
	//---------------------------------------------------------------------------------

	//-----------------------MODO VISION PANORAMICA -----------------------------------
		if(c=='e'||c=='E'){
			while(1){
				//fclose(fichero);
				//fichero = fopen("mapa_actual.txt","r+");
  				char c = getch();
				
  				if(c=='w'||c=='W'){
					system("@cls||clear");
					if(vertical>0)vertical--;			
					actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					imprimir(alto,ancho,mapa);
						
				}
  				if(c=='s'||c=='S'){
					system("@cls||clear");
					if(vertical<(66-alto))vertical++;		
					actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					imprimir(alto,ancho,mapa);
				}
  				if(c=='a'||c=='A'){
					system("@cls||clear");
					if(horizontal>0)horizontal--;		
					actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					imprimir(alto,ancho,mapa);
				}
  				if(c=='d'||c=='D'){
					system("@cls||clear");
					if(horizontal<(70-28))horizontal++;			
					actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					imprimir(alto,ancho,mapa);
				}
				if(c=='t'||c=='T'){

		//-------------MUESTREO DE ENEMIGOS -------------------------------------------	
				BFS(grafo,num_listas,mum_lista_p);		
  				if(aux->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					aux=aux->pi;
					a=fseek(fichero,140*(aux->fila)+2*(aux->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(en_vert_ant)+2*(en_hor_ant),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(aux->pi->fila)+2*(aux->pi->columna),SEEK_SET);
					fwrite("3", 1, 1, fichero);//imprime el símbolo del ratón
					en_vert_ant=aux->pi->fila;
					en_hor_ant=aux->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
 				
 				BFS(grafo,num_listas,(60-1)*weidth+(67));
				xa[0]='A';
 				for(int k=1;k<=8;k++){		
  				if(auxs[k]->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					auxs[k]=auxs[k]->pi;
					a=fseek(fichero,140*(auxs[k]->fila)+2*(auxs[k]->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(sub_vert_ant[k])+2*(sub_hor_ant[k]),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(auxs[k]->pi->fila)+2*(auxs[k]->pi->columna),SEEK_SET);
					fwrite(xa, 1, 1, fichero);//imprime el símbolo del subdito
					sub_vert_ant[k]=auxs[k]->pi->fila;
					sub_hor_ant[k]=auxs[k]->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
				xa[0]++;
 				}

 				BFS(grafo,num_listas,(8-1)*weidth+(63));
				xa[0]='I';
 				for(int k=9;k<=16;k++){		
  				if(auxs[k]->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					auxs[k]=auxs[k]->pi;
					a=fseek(fichero,140*(auxs[k]->fila)+2*(auxs[k]->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(sub_vert_ant[k])+2*(sub_hor_ant[k]),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(auxs[k]->pi->fila)+2*(auxs[k]->pi->columna),SEEK_SET);
					fwrite(xa, 1, 1, fichero);//imprime el símbolo del subdito
					sub_vert_ant[k]=auxs[k]->pi->fila;
					sub_hor_ant[k]=auxs[k]->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
				xa[0]++;
 				}
 				
 				BFS(grafo,num_listas,(8-1)*weidth+(5));
				xa[0]='a';
 				for(int k=1;k<=8;k++){		
  				if(auxe[k]->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					auxe[k]=auxe[k]->pi;
					a=fseek(fichero,140*(auxe[k]->fila)+2*(auxe[k]->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(ene_vert_ant[k])+2*(ene_hor_ant[k]),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(auxe[k]->pi->fila)+2*(auxe[k]->pi->columna),SEEK_SET);
					fwrite(xa, 1, 1, fichero);//imprime el símbolo del enemigo
					ene_vert_ant[k]=auxe[k]->pi->fila;
					ene_hor_ant[k]=auxe[k]->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
				xa[0]++;
 				}

				BFS(grafo,num_listas,(60-1)*weidth+(5));
				xa[0]='i';
 				for(int k=9;k<=16;k++){		
  				if(auxe[k]->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					auxe[k]=auxe[k]->pi;
					a=fseek(fichero,140*(auxe[k]->fila)+2*(auxe[k]->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(ene_vert_ant[k])+2*(ene_hor_ant[k]),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(auxe[k]->pi->fila)+2*(auxe[k]->pi->columna),SEEK_SET);
					fwrite(xa, 1, 1, fichero);//imprime el símbolo del enemigo
					ene_vert_ant[k]=auxe[k]->pi->fila;
					ene_hor_ant[k]=auxe[k]->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
				xa[0]++;
 				}
 				
 				BFS(grafo,num_listas,(ene_vert_ant[9]-1)*weidth+(ene_hor_ant[9]));
 				if(aux2->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					aux2=aux2->pi;
					a=fseek(fichero,140*(aux2->fila)+2*(aux2->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(bomba1_vert_ant)+2*(bomba1_hor_ant),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(aux2->pi->fila)+2*(aux2->pi->columna),SEEK_SET);
					fwrite("5", 1, 1, fichero);//imprime el símbolo del ratón
					bomba1_vert_ant=aux2->pi->fila;
					bomba1_hor_ant=aux2->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
 				
 			        BFS(grafo,num_listas,(ene_vert_ant[3]-1)*weidth+(ene_hor_ant[3]));
 				if(aux3->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					aux3=aux3->pi;
					a=fseek(fichero,140*(aux3->fila)+2*(aux3->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(bomba2_vert_ant)+2*(bomba2_hor_ant),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(aux3->pi->fila)+2*(aux3->pi->columna),SEEK_SET);
					fwrite("5", 1, 1, fichero);//imprime el símbolo del ratón
					bomba2_vert_ant=aux3->pi->fila;
					bomba2_hor_ant=aux3->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
 			
 			        BFS(grafo,num_listas,(sub_vert_ant[1]-1)*weidth+(sub_hor_ant[1]));
 				if(aux4->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					aux4=aux4->pi;
					a=fseek(fichero,140*(aux4->fila)+2*(aux4->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(bomba3_vert_ant)+2*(bomba3_hor_ant),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(aux4->pi->fila)+2*(aux4->pi->columna),SEEK_SET);
					fwrite("w", 1, 1, fichero);//imprime el símbolo del ratón
					bomba3_vert_ant=aux4->pi->fila;
					bomba3_hor_ant=aux4->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				}
				
 			        BFS(grafo,num_listas,(sub_vert_ant[9]-1)*weidth+(sub_hor_ant[9]));
 				if(aux5->pi->pi!=NULL){
					fichero = fopen("mapa_actual.txt","r+");
  					aux5=aux5->pi;
					a=fseek(fichero,140*(aux5->fila)+2*(aux5->columna),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(bomba4_vert_ant)+2*(bomba4_hor_ant),SEEK_SET);
					fwrite("0", 1, 1, fichero);
					a=fseek(fichero,140*(aux5->pi->fila)+2*(aux5->pi->columna),SEEK_SET);
					fwrite("w", 1, 1, fichero);//imprime el símbolo del ratón
					bomba4_vert_ant=aux5->pi->fila;
					bomba4_hor_ant=aux5->pi->columna;
					fclose(fichero);
					//actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
					//imprimir(alto,ancho,mapa);
 				} 			 				
				/*if(vida_nuestra_torreAA>0)
 				vida_nuestra_torreAA--;
				if(vida_torre_enemigaCC>0)
				vida_torre_enemigaCC++;*/

		//vida_torre_enemigaCC=vida_torre_enemigaCC-100;	
		//vida_torre_enemigaDD=vida_torre_enemigaDD-100;
		
				actualizar(alto,ancho,mapa,horizontal,vertical,p_hor,p_vert);
				imprimir(alto,ancho,mapa);
				if(vida_nuestra_torreAA<=0 && vida_nuestra_torreBB<=0)
				{
		 		 perdiste();
				}
				if(vida_torre_enemigaCC<=0 && vida_torre_enemigaDD<=0 )
				{
				  ganaste();
				}
				fichero = fopen("mapa_actual.txt","r+");
				a=fseek(fichero,140*(7)+2*(4),SEEK_SET);
				fscanf (fichero,"%c",&posicion1);
				a=fseek(fichero,140*(59)+2*(4),SEEK_SET);
				fscanf (fichero,"%c",&posicion2);
				a=fseek(fichero,140*(7)+2*(62),SEEK_SET);
				fscanf (fichero,"%c",&posicion3);
				a=fseek(fichero,140*(59)+2*(66),SEEK_SET);
				fscanf (fichero,"%c",&posicion4);
				fclose(fichero);
				if(posicion1>='a'&&posicion1<='p'){
					if(vida_nuestra_torreAA>0)
					vida_nuestra_torreAA=vida_nuestra_torreAA-vida_ene[posicion1-96]/4;
					if(vida_nuestra_torreAA<0)vida_nuestra_torreAA=0;
					}
				if(posicion2>='a'&&posicion2<='p'){
					if(vida_nuestra_torreBB>0)
					vida_nuestra_torreBB=vida_nuestra_torreBB-vida_ene[posicion2-96]/4;
					if(vida_nuestra_torreBB<0)vida_nuestra_torreBB=0;			
				}
				if(posicion3>='A'&&posicion3<='P'){
					if(vida_torre_enemigaCC>0)
					vida_torre_enemigaCC=vida_torre_enemigaCC-vida_sub[posicion3-64]/4;
					if(vida_torre_enemigaCC<0)vida_torre_enemigaCC=0;		
				}
				if(posicion4>='A'&&posicion4<='P'){
					if(vida_torre_enemigaDD>0)
					vida_torre_enemigaDD=vida_torre_enemigaDD-vida_sub[posicion4-64]/4;
					if(vida_torre_enemigaDD<0)vida_torre_enemigaDD=0;	
				}
		
			
		//-------------FINAL DE MUESTREO DE ENEMIGOS------------------------------------	
			
				}
				//-------------FINAL DE MUESTREO DE ENEMIGOS------------------------------------		

				if(c=='e'||c=='E') break; //Rompe while de vision panoramica.
				//PAUSE:
				if(c=='z'||c=='Z'){
						 printf("\t\t\t\t\t\t\t\tEL JUEGO ESTA EN PAUSA\n");
						 while(1){
							
							c = getch(tiempo);
							if(c=='z'||c=='Z')
							break;
						   }
				}
			}
		}
		//---------------------------FIN DE VISION PANORAMICA-----------------------------------------
		if(c=='z'||c=='Z'){
				printf("\t\t\t\t\t\t\t\tEL JUEGO ESTA EN PAUSA\n");
				while(1){
							
					c = getch(tiempo);
					if(c=='z'||c=='Z')
					break;
				}
		}
		//---------------------------RECARGO EL MAPA ORIGINAL-----------------------------------------
		
		//-------------------------------------------------------------------------------------------
  	}
  	return 0;

} 	

//--------------------FINAL DE FUNCION PRINCIPAL--------------------------------------------


