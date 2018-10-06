#include <iostream>
#include <stdlib.h>
#ifndef LISTAS_H
#define LISTAS_H
 
using namespace std;
struct nodo
{	int dato;
	nodo *sig;
	nodo *ant;
};
 
typedef nodo *pnodo;
 
class lista{
	private:
	pnodo pL;//dir del 1er nodo
	public:
	lista();
	~lista();
	void insertar_comienzo(int x);
	void insertar_final(int x);
	void eliminar(int x);
	pnodo buscar(int x);
	pnodo buscar_anterior(int x);
	pnodo buscar_posterior(int x);
	void imprimir();
};
 
lista::lista()
{
	pL=NULL;
}
 
lista::~lista()
{
	pnodo p,q;
	if( pL != NULL)
	{
		p = pL;
		while( p != NULL)
		{
			q = (*p).sig;
			delete p;
			p=q;
		} 
	}	
 
}
 
void lista::insertar_comienzo(int x)
{
	pnodo p;
	p = new nodo;
	(*p).dato=x;
	(*p).sig=pL; //pL 
	(*p).ant=NULL;
	if(pL != NULL)
		//pL->ant=p; //otra forma
		(*pL).ant=p;	
	pL=p; //pL apunta a todo el nodo , el cual tiene una dir de memoria
 
}
 
void lista::insertar_final(int x)
{
	pnodo p,q;
	p = new nodo;
	q = new nodo; 
	(*p).dato=x;
	(*p).sig=NULL;
	(*p).ant=NULL;
 
	if( pL == NULL)
		pL = p;
	else
	{
		q=pL;
		while( (*q).sig != NULL)
			q = (*q).sig;
		(*q).sig = p;
		(*p).ant = q;
	}	
}
 
pnodo lista::buscar(int x)
{
	pnodo p;
	if( pL == NULL)
		return NULL;
	else
	{
		p = pL;
		while ( p != NULL && (*p).dato !=x )
			p = (*p).sig;
		return p;	
	}
}
 
pnodo lista::buscar_anterior(int x)
{
	pnodo a,p;
	a=NULL;
	p=pL;
 
	while ( (*p).dato !=x )
	{
		a = p ;
		p = (*p).sig;
	}
	return a;
}
 
pnodo lista::buscar_posterior(int x)
{
	pnodo a,p;
	a=NULL;
	p=pL;
 
	while ( (*p).dato !=x )
	{
		p = (*p).sig;
	}
	a=(*p).sig;
	return a;
}
 
void lista::eliminar(int x)
{
	pnodo a,p,b;
	p=buscar(x);
 
	if(  p == NULL)
	cout<<"El elemento no esta en la lista"<<endl;
	else	
	{
		a=buscar_anterior(x);
		b=buscar_posterior(x);
 
		if( a == NULL)
			pL = (*p).sig;
		else
			(*a).sig = (*p).ant;
		if (b != NULL)
			(*b).ant = (*p).ant;
		delete p;
	}
}
 
void lista::imprimir()
{
	pnodo p;
	if (pL == NULL)
		cout<<"Lista vacia"<<endl;
	else
	{
		p = pL;
		while( p!= NULL)
		{
			cout<<(*p).dato<<" -> ";
			p = (*p).sig;
		}
		cout<<"NULO"<<endl;
	}
}
 
#endif



// CODIGO DE IDENTIFICACION:  lrY80Z
