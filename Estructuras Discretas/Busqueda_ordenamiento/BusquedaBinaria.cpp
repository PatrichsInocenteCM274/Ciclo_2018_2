#include<iostream>
using namespace std;
const int N=14;

//Busca la posicion
int busquedaBinaria(int a[N], int x){

	int inf=0, sup=N-1, med;
	int i=0;
	
	while(inf<=sup){
	
		med=(inf+sup)/2;
		
		i++;
		
		if(a[med]==x){
		
			cout<<"\nSe encontro el numero despues de "<<i<<" comparaciones"<<endl;
			return med;
		
		}else if(x<a[med]){
		
				sup=med-1;
			
			}else{
			
				inf=med+1;
			
			}	
		
				
	}

}

//Imprime la cadena
void imprimir(int a[N]){

	int i;
	
	for (i=0; i<N; i++)
		
		cout<<a[i]<<" ";
		
	cout<<endl; 

}

//Funcion principal
int main(){

int x, i, pos;
int a[N]={4,6,8,10,12,14,16,18,20,22,34,38,40,42};

	cout<<"Ingrese el numero que se desea buscar su posicion: "; cin>>x;

	imprimir(a);
	
	pos=busquedaBinaria(a, x);
	
		if(pos==-1){
	
		cout<<"\nNo se encuentra el numero"<<endl;
		
	}else{
	
		cout<<"\nEl numero "<<x<<" esta en la posicion: "<<pos+1<<endl; 
	
	}
	
	
}
