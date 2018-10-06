    #include <iostream>
    #include <stdlib.h>
    #include "listas.h"
    using namespace std;
     
    int main(){
    	lista L;
    	pnodo b;
    	int i,valor;
    	cout << "Insertando datos al comienzo" << endl;
    	for(i = 1;i<=5;i++){
    		cout << "Ingrese valor: ";
    		cin >> valor;
    		L.insertar_comienzo(valor);
    		L.imprimir();
    	}
    	cout << "Insertando datos al final" << endl;{
    		cout << "Ingrese valor: ";
    		cin >> valor;
    		L.insertar_final(valor);
    		L.imprimir();
    	}
    	for(i = 1;i <= 5;i++){
    		cout << "Ingrese valor a buscar: ";
    		cin >> valor;
    		if(b == NULL)
    			cout << "El elemento no está en la lista." << endl;
    		else{
    			cout << "El elemento sí está en la lista." << endl;
    			b = L.buscar_anterior(valor);
    			if(b == NULL)
    				cout << "No hay anterior." << endl;
    			else
    				cout << "El anterior es " << (*b).dato << endl;
    			b = L.buscar_posterior(valor);
    			if(b == NULL)
    				cout << "No hay posterior." << endl;
    			else
    				cout << "El posterior es " << (*b).dato << endl;
    		}
    	}
    	for(i = 5;i <= 5;i++){
    		cout << "Ingrese valor a eliminar: ";
    		cin >> valor;
    		b = L.buscar(valor);
    		if(b == NULL)
    			cout << "El elemento no está en la lista" << endl;
    		else{
    			L.eliminar(valor);
    			cout << "El valor " << valor << " ha sido eliminado" << endl;
    		}
    	}
    	L.imprimir();
    	cout << endl;
    	system("PAUSE");
    }


// CODIGO DE IDENTIFICACION:  y56dgq
