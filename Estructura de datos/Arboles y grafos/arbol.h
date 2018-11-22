#include <iostream>
#ifndef ARBOL_H
#define ARBOL_H

using namespace std;

struct nodoABB{
	nodoABB *hizq;
	int dato;
	nodoABB *hder;
};

typedef nodoABB *pnodoABB;

class abb{
	private:
		pnodoABB praiz;
	public:
		abb();
		~abb();
		bool estavacio();
		pnodoABB getraiz();
		pnodoABB buscar(int x);
		void insertar(int x);
		void imprimeenorden( pnodoABB p);
		void eliminaarbol( pnodoABB p);
};

abb::abb(){
	praiz = NULL;
}

abb::~abb(){
	eliminaarbol(praiz);
	praiz = NULL;
}

pnodoABB abb::getraiz()
{
	return praiz;
}

bool abb::estavacio(){
	if( praiz == NULL) return true;
	else return false;
}

void abb::insertar(int x){
	
	pnodoABB p,q,r;
	char h;
	p = new nodoABB;
	(*p).dato = x;
	(*p).hizq = NULL;
	(*p).hder=NULL;
	if( praiz == NULL ) praiz = p;
	else {
		q=praiz;
		while(q != NULL){
			r = q;
			if(x < (*q).dato){
				q = (*q).hizq; h = 'i';
			}
			else{
				q = (*q).hder;
				h = 'd';
			}
		}
		
	if( h == 'i')
		(*r).hizq = p;
	else 
		(*r).hder = p;
	}	
}

pnodoABB abb::buscar(int x){
	
	pnodoABB p;
	int ok;
	if( praiz ==NULL){
		return NULL;
	}
	else{
		ok = 0;
		p = praiz;
		while( p != NULL && ok == 0){
			if( (*p).dato == x)
				ok = 1;
			else
			if(x < (*p).dato) p = (*p).hizq;
			else p = (*p).hder;
			
		}
		return p;
	}
}

void abb::imprimeenorden (pnodoABB p)
{
	pnodoABB Ai,Ad;
	if (p != NULL){
		Ai = (*p).hizq;
		Ad = (*p).hder;
		imprimeenorden(Ai);
		cout<<(*p).dato<<" ";
		imprimeenorden(Ad);
	}
}

void abb::eliminaarbol(pnodoABB p){
	pnodoABB Ai,Ad;
	if( p != NULL)
	{
		Ai = (*p).hizq;
		Ad = (*p).hder;
		eliminaarbol(Ai);
		eliminaarbol(Ad);
		delete p;
	}
}



#endif














