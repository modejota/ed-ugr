#include "ingrediente.h"
#include "ingredientes.h"
#include "VD.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <utility> //Para poder usar el pair
using namespace std;



//Creamos ambos, son vectores dinamicos, cada uno de un tipo
Ingredientes::Ingredientes() {
	datos = VD<Ingrediente>(); //Llamamos al constructor de VD
	indice = VD<int>();
}

Ingredientes :: Ingredientes (const Ingredientes &otro) :
	datos(otro.datos), indice(otro.indice)
{
}

//Destructor, si hay algo, que se borre
Ingredientes::~Ingredientes() {
	if( datos.size() != 0){ //si tiene algun elemento dentro, llamamos al destrucutor de VD
		datos.~VD();
	}
	if ( indice.size() != 0){
		indice.~VD();
	}
}


void Ingredientes::clear(){
//Hacemos un clear a ambos vectores dinamicos
	if(datos.size()!=0)
		datos.clear();
	if(indice.size()!=0)
        	indice.clear();
}

void Ingredientes::Insertar(const Ingrediente &nuevo) {
	//Me declaro dos pair. El primer campo del pair para la posicion, el segundo bool para ver si esta
	pair<int, bool> posd; 
	pair<int, bool> posi;
	
	//Tenemos que buscar el ingrediente lo primero, a ver si esta o no, primero en datos
	bool encontrado = false;
	int izquierda = 0, derecha = datos.size(), medio;
	
	while(izquierda < derecha && !encontrado) {
		medio = (izquierda+derecha)/2;
		
		//Tienen que ser iguales en nombre y tipo para ser el mismo alimento, si es solo por nombre pues quitamos el segundo reglon
		if(datos[medio].getNombre() == nuevo.getNombre()
		   && datos[medio].getTipo() == nuevo.getTipo()) {
		   	
		   	encontrado = true;
		   
		} else {
			if(datos[medio].getNombre() < nuevo.getNombre()) 
				izquierda = medio+1;
			else 
			 	derecha = medio;
			
		}
	}
	
	//Terminamos la busqueda, vemos a ver si lo tenemos o no
		if(!encontrado){
			posd.first = izquierda;
			posd.second = false;
		}
		else {
			posd.first = medio;
			posd.second = true;
		}
	
		
	//Si el elemento no estaba, habra que buscar en que indice del vector de indices lo metemos
	if(!posd.second) {
		
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
	
	posi.first = izquierda2;	//Posicion donde lo metemos
	posi.second = true;			//Ahora si que lo vamos a tener en el vector
	
	for(int i = 0; i < indice.size(); i++) {	//Movemos todos los indices a partir de donde vamos a insertar
		if (indice[i] >= posd.first)
			indice[i]++;
	}
	
	//Insertamos en ambos vectores de manera normal, suponiendo que el insertar del VD no esta mal, que ya me joderia
	datos.Insertar(nuevo,posd.first);
	indice.Insertar(posd.first, posi.first);
	}
}

void Ingredientes::borrar(const string &nombre){

	//Me declaro dos pair. El primer campo del pair para la posicion, el segundo bool para ver si esta
	pair<int, bool> posd; 
	pair<int, bool> posi;
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
	
	if(!encontrado) {
		posd.first = izquierda;
		posd.second = false;
	}
	else {
		posd.first = medio;
		posd.second = true;
	}
	
	if(posd.second) {
		
		int izquierda2 = 0, derecha2 = indice.size(), mitad;
		while(izquierda2 < derecha2) {
			mitad = (izquierda2+derecha2)/2;
			int aux = indice[mitad];
			
			if(datos[aux].getTipo() == datos[posd.first].getTipo()) {
				if(datos[aux].getNombre() < datos[posd.first].getNombre())
					izquierda2 = mitad+1;
				else
					derecha2 = mitad;
			} else if (datos[aux].getTipo() < datos[posd.first].getTipo()) 
					izquierda2 = mitad+1;
			  else
			  		derecha2 = mitad;
		}
		
		posi.first = izquierda2;
		posi.second = false; 	//Va a dejar de estar
		
		for(int i = 0; i < indice.size(); i++) {
			if(indice[i] >= posd.first)
				indice[i]--;
		}
		
		datos.Borrar(posd.first);
		indice.Borrar(posi.first);
	
	}
}
//Vemos todos los datos del ingrediente que buscamos, recorremos el vector, miramos si el nombre es igual
//Mostramos el ingrediente de la posicion i, que es donde se ha encontrado la igualdad.
Ingrediente Ingredientes::get(string nombre){
	for(int i = 0; i < datos.size(); i++) {
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
VD<string> Ingredientes::getTipos() {
	VD<string> coincidencias;
	bool encontrado;
	int pos = 0;

	for(int i = 0; i < indice.size(); i++) {
		encontrado = false;
		string tipo = datos[indice[i]].getTipo();
		
		for(int j = 0; j < coincidencias.size() && !encontrado; j++) {
			if(tipo == coincidencias[j])
				encontrado = true;
		}
		
		if(!encontrado) {
			coincidencias.Insertar(tipo, pos);
			pos++;
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
	for(int i = 0; i < (this->size()); i++) {
		if((datos[i]).getTipo() == tipo) {
			clasificados.Insertar(this->datos[i]);
		}
	}
	
	return clasificados;
}
	

//Sirve para ver si un tipo existe o no
    
bool Ingredientes::existeTipo(string tipo) {    
    
    bool encontrado = false;
    VD<string> tipos = getTipos();
    for(int i = 0; i < tipos.size() && !encontrado; i++) {
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
	for(int i = 0; i < I.datos.size(); i++){
		os << I[i] << endl;	//Usamos sobrecarga operador [], aunque me gusta mas hacer I.datos[i]
	}

	return os;

}


