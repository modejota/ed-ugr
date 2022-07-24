#include "recetas.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <utility> //Para poder usar el pair
using namespace std;


recetas::recetas() {}
recetas::~recetas() {}

void recetas::clear(){
    if(datos.size()!=0)
        datos.clear();
}

int recetas::size()const{
    return datos.size();
}

void recetas::borrar(string c){
    datos.erase(c);
}

receta recetas::operator[](const string &cod){
    map<string,receta>::iterator it=datos.find(cod);
	if (it!=datos.end())
        return it->second;
    else {
		receta aux;
		aux.setNombre("Undefined");
		return aux;    
	}        
}

receta recetas::operator[](const string &cod)const{
	map<string,receta>::const_iterator it=datos.find(cod);
	if (it!=datos.end())
        return it->second;
    else {
		receta aux;
		aux.setNombre("Undefined");
		return aux;    
	}                     
}


void recetas::setNutricion(Ingredientes &I){
    //Aqui hacemos un for recorriendo todas las recetas, que simplemente llame a otro metodo de receta 
    //(dicho metodo "asignarValoresNutricionales" de receta debera asignar individualmente cada valor de los ingredientes de la "base de datos" a nuestros ingredientes usados para la receta) 
    recetas::iterator it;
    for(it=begin();it!=end();++it){
        (*it).asignarValoresNutricionales(I);
    }
}

void recetas::insertar(pair<string,receta> &elemento){
    datos.insert(elemento);
}

ostream & recetas::informacionResumidaRecetas(ostream & os){
    recetas::iterator it;

    for(it=begin();it!=end();++it){
        (*it).informacionResumidaReceta(os);
    }

    return os;
}

bool recetas::comprobarCodigo(string codigo){
    recetas::iterator it;
    bool esta=false;
    for(it=begin();it!=end() && !esta;++it){
        if((*it).getCode()==codigo)
            esta=true;
    }
    return esta;
}

ostream & operator <<(ostream &os, recetas &Rs){
    recetas::iterator it;
    for(it=Rs.begin();it!=Rs.end();++it){
        os << *it;
    }

    return os;
}


istream & operator >> (istream &is, recetas &Rs){
    Rs.clear();

    receta rec;

    //Mientras que no se acabe el fichero: metemos con el operator de entrada cada receta en rec, y luego la insertamos en el map
    //con el metodo insert (de la propia clase map) pairs<string,receta> (donde el string sera la clave, que sera el code 
    //de la receta; y la receta sera el valor asociado, que sera el "rec" que leimos con el operator)
    while(is>>rec){
        Rs.datos.insert(pair<string,receta>(rec.getCode(),rec));
        rec.clear(); //Vacia en cada bucle lo que le han metido con "is>>rec", para que no se vaya concatenando con las siguinetes lecturas
    }

    return is;

}

bool recetas::CargarRecetas(const string &nombre, const string &path_ins){
    ifstream flujo;

    //Abrimos el flujo para el fichero de las recetas
    flujo.open(nombre);
    //Comprobamos que se haya abierto el fichero.
	if (!flujo){
		cerr << "Error abriendo el fichero " << nombre << endl;
		return false;
	}

    flujo >> *(this);
    flujo.close();

    recetas::iterator it;
    string path_aux;

    //Cargamos las instrucciones de cada receta
    for(it=begin(); it!=end(); ++it){
        instrucciones nuevas;
        path_aux= path_ins + (*it).getCode() + "m.txt";

        //Abrimos el flujo para el fichero de instrucciones de una determinada receta
        flujo.open(path_aux);

        //Comprobamos que se haya abierto el fichero.
		if (!flujo){
			cerr << "Error abriendo el fichero " << path_aux << endl;
			return false;
		}

        flujo >> nuevas;
        flujo.close();

        (*it).setInstrucciones(nuevas);
    }
    return true;
}
