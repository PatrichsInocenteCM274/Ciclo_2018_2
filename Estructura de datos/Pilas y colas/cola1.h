  #ifndef COLA1_H
  #define COLA1_H
  #include<iostream>
  using namespace std;
  struct nodocola
  {
  	int dato;
  	nodocola *sig;
  };

typedef nodocola *pnodocola;

class cola
{
	private:
	pnodocola pfrente;
	pnodocola pfinal;
	public:
	cola();
	~cola();
	bool estavacia();
	void encolar(int x);
	int desencolar();
	void imprimir();
};

cola::cola()
{
	pfrente=NULL;
	pfinal=NULL;
}


cola::~cola()
    {
    	 pnodocola p,q;
    	 if(pfrente!=NULL)
    	 {
    	 	p=pfrente;
    	 	while(p!=NULL)
    	 	{
    	 		q=(*p).sig;
    	 		delete p;
    	 		p=q;
    	 	}
    	 }
    }
  
bool cola::estavacia()
{
	if(pfinal==NULL)
		return true;
      else 
      	return false;
}


void cola::encolar(int x)
{
	pnodocola p;
	p=new nodocola;
	(*p).dato=x;
	(*p).sig=NULL;
	if(pfrente==NULL)
		pfrente=p;
	else
		(*pfinal).sig=p;
	pfinal=p;
}

int cola::desencolar(){
	pnodocola p;
	int x;
	p=pfrente;
	if((*p).sig==NULL){
		pfrente=NULL;
		pfinal=NULL;
	}
	else
	   pfrente=(*p).sig;
	x=(*p).dato;
	delete p;
	return x;

}

void cola::imprimir()
{
	pnodocola p;
	if(pfrente==NULL)
		cout <<"Pila vacia"<<endl;
	else
	{
		p=pfrente;
		while(p!=NULL)
		{
			cout<<(*p).dato<<"->";
			p=(*p).sig;
		}
		cout<<"NULO"<<endl;
	}
}

#endif
