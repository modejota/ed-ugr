#include "ingrediente.h"
#include <iostream>
#include <string> 

using namespace std;

Ingrediente::Ingrediente() {
	setNombre("Undefined");
	setCalorias(0);
	setHc(0);
	setProteinas(0);
	setGrasas(0);
	setFibra(0);
	setTipo("Undefined");
}

Ingrediente::Ingrediente(string nombre, float calorias, float hidratos_carbono, float proteinas, float grasas, float fibra, string tipo_ingrediente) {
	setNombre(nombre);
	setCalorias(calorias);
	setHc(hidratos_carbono);
	setProteinas(proteinas);
	setGrasas(grasas);
	setFibra(fibra);
	setTipo(tipo_ingrediente);
}

void Ingrediente::Copiar(const Ingrediente & otro){
	setNombre(otro.getNombre());
	setCalorias(otro.getCalorias());
	setHc(otro.getHc());
	setProteinas(otro.getProteinas());
	setGrasas(otro.getGrasas());
	setFibra(otro.getFibra());
	setTipo(otro.getTipo());
}

void Ingrediente::setNombre(string nombre) {
	this->nombre = nombre;
}

string Ingrediente::getNombre() const {
	return nombre;
}

void Ingrediente::setCalorias(float calorias) {
	this->calorias = calorias;
}

float Ingrediente::getCalorias() const {
	return calorias;
}

void Ingrediente::setHc(float hidratos_carbono) {
	this->hidratos_carbono = hidratos_carbono;
}

float Ingrediente::getHc() const{
	return hidratos_carbono;
}

void Ingrediente::setProteinas(float proteinas) {
	this->proteinas = proteinas;
}

float Ingrediente::getProteinas() const{
	return proteinas;
}

void Ingrediente::setGrasas(float grasas) {
	this->grasas = grasas;
}

float Ingrediente::getGrasas() const{
	return grasas;
}

void Ingrediente::setFibra(float fibra) {
	this->fibra = fibra;
}

float Ingrediente::getFibra() const {
	return fibra;
}

void Ingrediente::setTipo(string tipo_ingrediente) {
	this->tipo_ingrediente = tipo_ingrediente;
}

string Ingrediente::getTipo() const {
	return tipo_ingrediente;
}

Ingrediente & Ingrediente::operator=(const Ingrediente &original){
	if(this != &original)
		Copiar(original);	
	return *this;	
}

bool Ingrediente::operator== (const Ingrediente &original) const {
	bool es_igual;
	if( (this->getNombre() == original.getNombre())  && (this->getTipo() == original.getTipo()) )
		es_igual = true;
	else
		es_igual = false;
	return es_igual;
}

bool Ingrediente::operator== (Ingrediente &original) const {
	bool es_igual;
	if( (this->getNombre() == original.getNombre())  && (this->getTipo() == original.getTipo()) )
		es_igual = true;
	else
		es_igual = false;
	return es_igual;
}

ostream & operator << (ostream & salida, const Ingrediente & original) {

	salida << original.getNombre() << ";" << original.getCalorias() << ";" << original.getHc() << ";" 
		   << original.getProteinas() << ";" << original.getGrasas() << ";" << original.getFibra() << ";" << original.getTipo();
	return salida;
}

istream & operator >> (istream & entrada, Ingrediente & obj){
    string alimento,tipo, aux;
	double calorias, hidratos,proteinas,grasas,fibra;
	
	//Extraemos el nombre
	getline(entrada,alimento,';'); //Va leyendo la linea hasta el delimitador (extrae el delimitador pero no lo mete en el string, y se queda justo después del delimitador)
        if(!entrada)
           return entrada;
	obj.setNombre(alimento);

	//Extraemos las calorias como string y lo pasamos a double
	getline(entrada,aux,';');
	calorias=stod(aux); //stod(string) convierte el string en double
	obj.setCalorias(calorias);

	//Extraemos los hidratos como string y lo pasamos a double
	getline(entrada,aux,';');
	hidratos=stod(aux); 
	obj.setHc(hidratos);

	//Extraemos las proteinas como string y lo pasamos a double
	getline(entrada,aux,';');
	proteinas=stod(aux); 
	obj.setProteinas(proteinas);

	//Extraemos las grasas como string y lo pasamos a double
	getline(entrada,aux,';');
	grasas=stod(aux); 
	obj.setGrasas(grasas);

	//Extraemos las fibras como string y lo pasamos a double
	getline(entrada,aux,';');
	fibra=stod(aux); 
	obj.setFibra(fibra);
	
	//Extraemos el tipo de ingrediente
	getline(entrada,tipo); //Este ultimo getline usa el delimitador por defecto '\n'.
        unsigned int pos=tipo.find('\r');
        if (pos!=string::npos)	//Encontramos el fin de archivo de Windows
           tipo=tipo.substr(0,pos);	//Quita de la cadena desde 0 pos caracteres
	obj.setTipo(tipo);
	
	return entrada;
}










