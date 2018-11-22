  #include<iostream>
  #include<stdlib.h>
  #include "cola1.h"
  using namespace std;
  int main()
  {
  	cola stack;
  	int x,i;
  	cout<<"Encolando datos:"<<endl;
  	for(i=1;i<=5;i++)
  	{
  		cout<<"Ingrese un dato: ";
  		cin>>x;
  		stack.encolar(x);
  		stack.imprimir();
  	}
  	cout<<endl<<"Desencolando datos"<<endl;
  	while(!stack.estavacia())
  	{
  		x=stack.desencolar();
  		cout<<"Dato desapilado: "<<x<<endl;
  		stack.imprimir();
  	}
  	system("PAUSE");
  	return 0;
 }
  
