  #include<iostream>
  #include<stdlib.h>
  #include "pila1.h"
  using namespace std;
  int main()
  {
  	pila stack;
  	int x,i;
  	cout<<"Apilando datos:"<<endl;
  	for(i=1;i<=5;i++)
  	{
  		cout<<"Ingrese un dato: ";
  		cin>>x;
  		stack.apilar(x);
  		stack.imprimir();
  	}
  	cout<<endl<<"Desapilando datos"<<endl;
  	while(!stack.estavacia())
  	{
  		x=stack.desapilar();
  		cout<<"Dato desapilado: "<<x<<endl;
  		stack.imprimir();
  	}
  	system("PAUSE");
  	return 0;
 }
  
