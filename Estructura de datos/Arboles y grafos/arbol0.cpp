#include <iostream>
#include <stdlib.h>
#include "arbol.h"

using namespace std;

int main()
{
	abb A;
	pnodoABB b,r;
	int i,x,sn,n,cn;
	cout<<"Cuantos nodos desea ingresar ";
	cin>>n;
	for(i=1;i<=n;i++){
		cout<<"Ingrese un dato : ";
		cin>>x;
		A.insertar(x);
	}
		
	cout<<"Imprimiendo en orden: "<<endl;
	r = A.getraiz();
	A.imprimeenorden(r);
	cout<<endl;
	for(i=1;i<=5;i++){
		cout<<"Ingrese dato a buscar: ";
		cin>>x;
		b = A.buscar(x);
		if ( b==NULL ) cout<<"El dato "<<x<<" no esta en el arbol"<<endl;
		else cout<<"El dato "<<x<<" si esta en el arbol"<<endl; 
	}
	return 0;
}
