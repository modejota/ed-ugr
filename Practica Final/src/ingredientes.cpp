#include "ingrediente.h"
#include "ingredientes.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <utility> //Para poder usar el pair
using namespace std;



//Creamos ambos, son vectores dinamicos, cada uno de un tipo
Ingredientes::Ingredientes() {}

//Destructor, si hay algo, que se borre
Ingredientes::~Ingredientes() {}


void Ingredientes::clear(){
//Hacemos un clear a ambos vectores dinamicos
	if(datos.size()!=0)
		datos.clear();
	if(indice.size()!=0)
        	indice.clear();
}

void Ingredientes::Insertar(const Ingrediente &nuevo) {

	typename vector<Ingrediente>::iterator it_datos;
	
	//Tenemos que buscar el ingrediente lo primero, a ver si esta o no, primero en datos
	bool encontrado = false;
	int izquierda = 0, derecha = datos.size(), medio;
	
	while(izquierda < derecha && !encontrado) {
		medio = (izquierda+derecha)/2;
		
		//Tienen que ser iguales en nombre y tipo para ser el mismo alimento, si es solo por nombre pues quitamos el segundo reglon
		if( datos[medio].getNombre() == nuevo.getNombre()
		   && datos[medio].getTipo() == nuevo.getTipo()) {
		   	
		   	encontrado = true;
		   
		} else {
			if( datos[medio].getNombre() > nuevo.getNombre()) 
				derecha = medio;
			else 
			 	izquierda = medio+1;
			
		}
	}
	it_datos = datos.begin();
	if(!encontrado)
		advance(it_datos, izquierda);
	else
		advance(it_datos, medio);

	typename vector<int>::iterator it_indice;
	//Si el elemento no estaba, habra que buscar en que indice del vector de indices lo metemos
	if(!encontrado) {
		
	int izquierda2 = 0, derecha2 = indice.size(), mitad = (izquierda2+derecha2)/2;
	bool encontrado2 = false;
	
	while(izquierda2 < derecha2 && !encontrado2) {
		mitad = (izquierda2+derecha2)/2;
		int aux = indice[mitad];	

		//Habra que ver si el tipo es igual, y ya si es igual, por nombre donde lo colocamos
		if(datos[aux].getTipo() == nuevo.getTipo()) {
			
			if(datos[aux].getNombre() < nuevo.getNombre())
				izquierda2= mitad+1;
			else
				derecha2 = mitad;
				
		} else if (datos[aux].getTipo() < nuevo.getTipo())	//Si el tipo es menor me tengo que ir a la parte derecha del vector
				izquierda2 = mitad+1;
		else
				derecha2 = mitad; //Si no, a la izquierda
	}

	it_indice = indice.begin();
	advance(it_indice, izquierda2);

	for(unsigned int i = 0; i < indice.size(); i++) {	//Movemos todos los indices a partir de donde vamos a insertar
		if (indice[i] >= izquierda)
			indice[i]++;
	}
	
	datos.insert(it_datos, nuevo);
	indice.insert(it_indice,izquierda);

	}
}

void Ingredientes::borrar(const string &nombre){

	typename vector<Ingrediente>::iterator it_datos;

	bool encontrado = false;
	int izquierda = 0, derecha = datos.size(), medio;
	
	while(izquierda<derecha && !encontrado) {
		medio = (izquierda+derecha)/2;
		if(datos[medio].getNombre() == nombre)
			encontrado = true;
		
		else {
			if(datos[medio].getNombre() < nombre)
				izquierda = medio+1;
			else
				derecha=medio;
		}
	}
	
	it_datos = datos.begin();
	advance(it_datos, medio);
	
	typename vector<int>::iterator it_indice;
	if(encontrado) {
		
		int izquierda2 = 0, derecha2 = indice.size(), mitad;
		while(izquierda2 < derecha2) {
			mitad = (izquierda2+derecha2)/2;
			int aux = indice[mitad];
			
			if(datos[aux].getTipo() == datos[izquierda].getTipo()) {
				if(datos[aux].getNombre() < datos[izquierda].getNombre())
					izquierda2 = mitad+1;
				else
					derecha2 = mitad;
			} else if (datos[aux].getTipo() < datos[izquierda].getTipo()) 
					izquierda2 = mitad+1;
			  else
			  		derecha2 = mitad;
		}
		
		it_indice = indice.begin();
		advance(it_indice, izquierda2);
		
		for(unsigned int i = 0; i < indice.size(); i++) {
			if(indice[i] >= izquierda)
				indice[i]--;
		}
		
		datos.erase(it_datos);
		indice.erase(it_indice);
	
	}
}


//Vemos todos los datos del ingrediente que buscamos, recorremos el vector, miramos si el nombre es igual
//Mostramos el ingrediente de la posicion i, que es donde se ha encontrado la igualdad.
Ingrediente Ingredientes::get(string nombre){
	for(unsigned int i = 0; i < datos.size(); i++) {
		if((datos[i]).getNombre() == nombre) {
			return datos[i];
		}
	}
	
	// Si no se encuentra devolvemos un ingrediente nulo.
	Ingrediente ingrediente;
	
	return ingrediente;
}

//Pide que lo devolvamos segun el nombre, o sea, segun lo almacenado en el vector datos
Ingrediente & Ingredientes::operator[](int i) {
	return datos[i];
}

//Cargamos en un vector dinamico de strings el nombre de todos los tipos de alimentos. 
vector<string> Ingredientes::getTipos() {
	vector<string> coincidencias;
	bool encontrado;

	for(unsigned int i = 0; i < indice.size(); i++) {
		encontrado = false;
		string tipo = datos[indice[i]].getTipo();
		
		for(unsigned int j = 0; j < coincidencias.size() && !encontrado; j++) {
			if(tipo == coincidencias[j])
				encontrado = true;
		}
		
		if(!encontrado) {
			coincidencias.push_back(tipo);
		}
	}
	
	return coincidencias;
}

//Mostrar todos los ingredientes ordenados por tipo. 
void Ingredientes::ImprimirPorTipo(ostream &os) {

	for(int i = 0; i < this->size(); i++) {
		os << datos[indice[i]] << endl;
	}
}

//Devuelve todos los ingredientes de un determinado tipo en un nuevo elemento.
Ingredientes Ingredientes::getIngredienteTipo(string tipo) {
	
	Ingredientes clasificados;
	typename vector<Ingrediente>::iterator it_datos;

	for(it_datos = datos.begin(); it_datos != datos.end(); ++it_datos) {
		if((*it_datos).getTipo() == tipo) {
			clasificados.Insertar(*(it_datos));
		}
	}
	
	return clasificados;
}
	

//Sirve para ver si un tipo existe o no

bool Ingredientes::existeTipo(string tipo) {    
    
    bool encontrado = false;
    vector<string> tipos = getTipos();
    for(unsigned int i = 0; i < tipos.size() && !encontrado; i++) {
	if(tipos[i] == tipo)
		encontrado = true;
    }

    return encontrado;
}

	
istream & operator >>(istream &is,Ingredientes &I){	

	I.clear();
	Ingrediente ing;
	string quitar;
	
	getline(is,quitar);
	while(is>>ing){ //mientras no se acabe el fichero (es decir,que no llegue al EOF), insertamos. 
		I.Insertar(ing);
		
	}
	
	return is;
}

int Ingredientes::size(){
	return datos.size();
}

ostream & operator << (ostream &os, Ingredientes &I){
	
	os << "Alimento (100 gramos);Calorias (Kcal.);Hidratos de Carb.;Proteinas;Grasas;Fibra;Tipo" << endl;
	for(unsigned int i = 0; i < I.datos.size(); i++){
		os << I[i] << endl;	//Usamos sobrecarga operador [], aunque me gusta mas hacer I.datos[i]
	}

	return os;

}


