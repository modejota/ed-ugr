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

int recetas::size(){
    return datos.size();
}

void recetas::borrar(string c){
    datos.erase(c);
}

receta & recetas::operator [](string c){
    return datos[c];
}

void recetas::obtenerNutrientes(Ingredientes &I){
    //Aqui hacemos un for recorriendo todas las recetas, que simplemente llame a otro metodo de receta 
    //(dicho metodo "asignarValoresNutricionales" de receta debera asignar individualmente cada valor de los ingredientes de la "base de datos" a nuestros ingredientes usados para la receta) 
    recetas::iterator it;
    for(it=begin();it!=end();++it){
        (*it).asignarValoresNutricionales(I);
    }
}

void recetas::insertarElemento(pair<string,receta> &elemento){
    datos.insert(elemento);
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
