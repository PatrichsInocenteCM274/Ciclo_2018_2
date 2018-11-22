#include<iostream>
using namespace std;
const int N=15;


//Algortimo que busca la poscicion
int busquedaSecuencial (int a[N], int x){

	cout<<endl;
	
	int i=0;
	
	do{
	
		if(a[i]==x)
			
			return i;
		
		i++;
		
	}while(i<N);
	
	return -1;

}

//Imprime la cadena
void imprimir(int a[N]){

	int i;
	
	for (i=0; i<N; i++)
		
		cout<<a[i]<<" ";
		
	cout<<endl; 

}

//Funcion Principal
int main(){

	int x, pos, i;
	int a[N]={2,4,6,8,10,12,14,16,18,20,22,24,26,28,30};
	
	cout<<"Ingrese el numero que se desea buscar su posicion: "; cin>>x;

	imprimir(a);
	
	pos=busquedaSecuencial(a,x);
	
	if(pos==-1){
	
		cout<<"\nNo se encuentra el numero"<<endl;
		
	}else{
	
		cout<<"\nEl numero "<<x<<" esta en la posicion: "<<pos+1<<endl; 
	
	}
	
}
