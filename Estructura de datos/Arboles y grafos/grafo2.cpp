#include<iostream>
#include<conio.h>

using namespace std;

struct nodo{
	char nombre;
	struct nodo *sgte;
	struct arista *ady;
};


struct arista{
	struct nodo *destino;
	struct arista *sgte;
};

typedef struct nodo *Tnodo;
typedef struct arista *Tarista;
Tnodo p;

void menu(){
	cout<<"\n Grafo \n";
	cout<<"1 . Insertar nodo "<<endl;
	cout<<"2 . Insertar arista "<<endl;
	cout<<"3 . Mostrar grafo "<<endl;
	cout<<"4 . Salir "<<endl;
	cout<<"\n Ingrese opcion: ";
}


void insertar_nodo(){
	Tnodo t,nuevo = new struct nodo;
	cout<<"Ingrese nodo:";
	cin>>nuevo->nombre;
	nuevo->sgte = NULL;
	nuevo->ady = NULL;
	
	if (p == NULL){
		p = nuevo;
	}
	else
	{
		t = p;
		while (t->sgte != NULL)
		{
			t = t->sgte;
		}
		t->sgte = nuevo;
	}

}

void agrega_arista(Tnodo &aux,Tnodo &aux2, Tarista &nuevo){
	
	Tarista q;
	if(aux->ady == NULL)
	{
		aux->ady = nuevo;
		nuevo->destino = aux2;
	}
	else{
		q=aux->ady;
		while(q->sgte != NULL)
			q = q->sgte;
		q->sgte = nuevo;
		nuevo->destino = aux2;
	}
}

void insertar_arista(){

	char ini,fin;
	Tarista nuevo = new struct arista;
	Tnodo aux, aux2;
	if(p==NULL){
		cout<<"vacio";
		return;
	}
	nuevo->sgte = NULL;
	cout<<"primer nodo:";
	cin>>ini;
	cout<<"segundo nodo:";
	cin>>fin;
	aux = p;
	aux2 = p;
	while(aux2 != NULL)
	{
		if(aux2->nombre == fin) break;
		aux2=aux2->sgte;
	} 
	while(aux != NULL)
	{
		if(aux->nombre == ini){
			agrega_arista(aux,aux2,nuevo);
			return;
		}
		aux = aux->sgte;
	}

}

void mostrar_grafo(){
	Tnodo ptr;
	Tarista ar;
	ptr = p ;
	cout<<"Nodo |  Nodos incidentes \n";
	
	while(ptr != NULL)
	{
		cout<<"   "<<ptr->nombre<<"|";
		if(ptr->ady != NULL)
		{
			ar = ptr->ady;
			while(ar != NULL){
				cout<<" "<<ar->destino->nombre;
				ar = ar->sgte;
			}
		}
		ptr = ptr->sgte;
		cout<<endl;
		
	}


}

int main(){
	p=NULL;
	int op;
	
	do
	{
		menu();
		cin>>op;
		
		switch(op){
		
		case 1: insertar_nodo();
			break;
		
		case 2: insertar_arista();
			break;
		
		case 3: mostrar_grafo();
			break;
		default: cout<<"Elige otro";
			break;
		}
		cout<<endl;
		
	}
	while(op!=4);
	//getch();
	return 0;
}

