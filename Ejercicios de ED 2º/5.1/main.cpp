#include "ParqueDeAtracciones.h"

#include <iostream>
#include <string>
using namespace std;



void lista(const Lista<string>& l) {
   Lista<string>::ConstIterator i = l.cbegin();
   while (i != l.cend()) {
     cout << i.elem() << " ";
     i.next();
   }	
  cout << endl;
}

void an_atraccion(ParqueDeAtracciones& parque) {
   string atraccion;
   cin >> atraccion;
   try {
     parque.an_atraccion(atraccion);
    cout << "OK" << endl;
   }   
   catch(EAtraccionYaExiste) {
	   cout << "ATRACCION_YA_EXISTE" << endl;
   }
   
}

void an_ninio(ParqueDeAtracciones& parque) {
   string ninio;
   cin >> ninio;
   try {
     parque.an_ninio(ninio);
    cout << "OK" << endl;
   }   
   catch(ENinioYaRegistrado) {
	   cout << "NINIO_YA_REGISTRADO" << endl;
   }
   
}

void poner_en_fila(ParqueDeAtracciones& parque) {
   string ninio;
   cin >> ninio;
   string atraccion;
   cin >> atraccion;
   try {
     parque.poner_en_fila(ninio,atraccion);
    cout << "OK" << endl;
   }   
   catch(EAccesoAtraccion) {
	   cout << "ERROR_ACCESO_ATRACCION" << endl;
   }
   
}

void avanzar(ParqueDeAtracciones& parque) {
   string atraccion;
   cin >> atraccion;
   try {
     parque.avanzar(atraccion);
    cout << "OK" << endl;
   }   
   catch(EAtraccionNoExiste) {
	   cout << "ATRACCION_NO_EXISTE" << endl;
   }   
}

void atracciones_visitadas(ParqueDeAtracciones& parque) {
   string ninio;
   cin >> ninio;
   try {
    lista(parque.atracciones_visitadas(ninio));
   }   
   catch(ENinioNoRegistrado) {
	   cout << "NINIO_NO_REGISTRADO" << endl;
   }   
}


void numero_visitas(ParqueDeAtracciones& parque) {
	string ninio;
	cin >> ninio;
	string atraccion;
	cin >> atraccion;
	try {
		cout << parque.numero_visitas(ninio, atraccion) << endl;
	}
	catch (EConsultaNumViajes) {
		cout << "ERROR_CONSULTA_NUMERO_VIAJES" << endl;
	}
}



int main() {
   ParqueDeAtracciones parque;
   string comando;
   while(cin >> comando) {
       if (comando == "an_atraccion") an_atraccion(parque);
	   else if (comando == "an_ninio") an_ninio(parque);
	   else if (comando == "poner_en_fila") poner_en_fila(parque);
	   else if (comando == "avanzar") avanzar(parque);
	   else if (comando == "atracciones_visitadas") atracciones_visitadas(parque);
	   else if (comando == "numero_visitas") numero_visitas(parque);
	}
	return 0;
}
