#include "acciones.h"
#include <sstream>
#include <string>
//#include <cstring>

acciones::acciones(){}
acciones::~acciones(){}


// Insertar una accion con su ariedad.
void acciones::Insertar (string accion, unsigned char ariedad){
	//Accede a un elemento, pero tambien comprueba si está o no en el map; si no está, te lo inserta
	//En este caso hace lo mismo que el insert()
	datos[accion] = ariedad; 
}


// Borrar una accion.
void acciones::Borrar (string accion){
	map<string,unsigned char>::iterator it;
	
	it = datos.find(accion);
	
	if (it != datos.end()){
		datos.erase(it);
	}
}


// Devolver la ariedad de una acción.
unsigned char acciones::operator [] (string &nombre){
	map<string,unsigned char>::iterator it=datos.find(nombre);
	
	if (it!=datos.end())
		return it->second;
	else {
		return 0;    
	}
}


// Devolver la ariedad de una acción (metodo constante.).
const unsigned char acciones::operator [] (string &nombre) const{
	map<string,unsigned char>::const_iterator it=datos.find(nombre);
	if (it!=datos.cend())
		return it->second;
	else {
		return 0;    
	}
}

const unsigned int acciones::count(string &key)const {
	return datos.count(key);
}


//Operador de entrada.
istream & operator >> (istream & is, acciones & Ac){
	string aux;
	
	Ac.clear();
	
	while (getline(is, aux)){
		if(!is || aux.length() < 1){ //Si llega al final de fichero o lee una linea vacía, para.
			return is;
		}
		else{
			unsigned char ariedad_aux;
			string nombre_aux;

			//Aqui usamos un flujo de strings para extraer la accion y la ariedad del txt
			istringstream cadena (aux);
			//Leemos el nombre de la accion (y nos quedamos en el espacio), leemos el espacio (quedandonos delante del numero),
			//y leemos la ariedad
			cadena >> nombre_aux;
			cadena >> ariedad_aux;
			cadena >> ariedad_aux;
			
			Ac.Insertar(nombre_aux, ariedad_aux);
		}
	}
	
	return is;
}


// Operador de salida.
ostream & operator << (ostream & os, const acciones & A){
	acciones::const_iterator it;
	
	for (it = A.cbegin(); it != A.cend(); ++it){ 
		os << (*it).first << ' ' << (*it).second << endl;
	}
	
	return os;
}
