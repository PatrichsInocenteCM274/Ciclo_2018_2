#include<iostream>
using namespace std;
const int N=8;

//Imprime la cadena
void imprimir(int a[N]){

	int i;
	
	for (i=0; i<N; i++)
		
		cout<<a[i]<<" ";
		
	cout<<endl; 

}

//Algortimo que busca la poscicion
int ordenamientoporSeleccion (int a[N]){

	int i, j, aux, posmen;
	
	for (i=0; i<N-1; i++){
	
		posmen=i;
		
		for (j=i+1; j<N; j++){
		
			if (a[j]<a[posmen]){
			
				posmen=j;
				
			}
			
			if (i!=posmen){
			
				aux=a[posmen];
				a[posmen]=a[i];
				a[i]=aux;
			
				imprimir(a);
			
			}
		
		}
		
	}

}


//Funcion Principal
int main(){

	int a[N]={8,3,6,4,2,5,7,1};
	
	ordenamientoporSeleccion (a);
	
	imprimir(a);
	
	cout<<"\nAhora si esta ordanado papu"<<endl;
	
}
