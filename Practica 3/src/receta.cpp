#include "receta.h"
#include "ingredientes.h"
#include "ingrediente.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <utility> //Para poder usar el pair
using namespace std;

receta::receta(){
    setCode("R0");
    setPlato(0);
    setNombre("Undefined");
}

receta::receta(string code,unsigned int plato,string nombre,list<pair<string,unsigned int>> lista){
    setCode(code);
    setPlato(plato);
    setNombre(nombre);
    ings=lista;
}


string receta::getCode(){
    return code;
}

void receta::setCode(string code){
    this->code=code;
}

unsigned int receta::getPlato(){
    return plato;
}

void receta::setPlato(unsigned int plato){
    this->plato=plato;
}

string receta::getNombre(){
    return nombre;
}

void receta::setNombre(string nombre){
    this->nombre=nombre;
}

float receta::getCalorias(){
    return calorias;
}

void receta::setCalorias(float calorias){
    this->calorias=calorias;
}

float receta::getHc(){
    return hc;
}

void receta::setHc(float hc){
    this->hc=hc;
}

float receta::getGrasas(){
    return grasas;
}

void receta::setGrasas(float grasas){
    this->grasas=grasas;
}

float receta::getProteinas(){
    return proteinas;
}

void receta::setProteinas(float proteinas){
    this->proteinas=proteinas;
}

float receta::getFibra(){
    return fibra;
}

void receta::setFibra(float fibra){
    this->fibra=fibra;
}




int receta::ningredientes(){
    return ings.size();
}

void receta::clear(){
    ings.clear();
}

void receta::asignarValoresNutricionales(Ingredientes &I){
    Ingrediente ing;
    string nombre_aux;
    unsigned int cantidad_aux;
    float suma_cal=0.0, suma_hc=0.0, suma_prot=0.0, suma_gra=0.0, suma_fib=0.0;
    receta::iterator it;

    for(it=begin();it!=end();++it){
        nombre_aux=(*it).first;
        cantidad_aux=(*it).second;

        ing=I.get(nombre_aux);

        //Añadimos los nutrientes del ingrediente actual de la lista
        suma_cal+=(ing.getCalorias()*cantidad_aux)/100.0;
        suma_hc+=(ing.getHc()*cantidad_aux)/100.0;
        suma_gra+=(ing.getGrasas()*cantidad_aux)/100.0;
        suma_prot+=(ing.getProteinas()*cantidad_aux)/100.0;
        suma_fib+=(ing.getFibra()*cantidad_aux)/100.0;
    }
    //Asignamos el total de nutrientes de la receta finalmente
    setCalorias(suma_cal);
    setHc(suma_hc);
    setGrasas(suma_gra);
    setProteinas(suma_prot);
    setFibra(suma_fib);
}

ostream & operator << (ostream &os, receta &R){
    receta::iterator it;
    os << R.getCode() << ";" << R.getPlato() << ";" << R.getNombre() << ";";

    //El --R.end() lo pongo porq el ultimo pair va sin ';'
    for(it=R.begin(); it!=(--R.end()); ++it)
        os << (*it).first << " " << (*it).second << ";";

    //El ultimo lo pongo fuera del bucle
    os << (*it).first << " " << (*it).second;
    
    cout << endl;

    return os;
}

istream & operator >> (istream &is, receta &R){
    string code, nombre, aux, aux_nombre_ing, aux2;
    //float calorias, hc, grasas, proteinas, fibra;
    unsigned int plato, cantidad, contador=0;
    pair<string,unsigned int> ingrediente;

    //Extraemos el code
	getline(is,code,';'); //Va leyendo la linea hasta el delimitador (extrae el delimitador pero no lo mete en el string, y se queda justo después del delimitador)
        if(!is)
           return is;
    R.setCode(code);
    //cout << "Codigo: " << getCode() << endl;

    //Extraemos el numero de plato
    getline(is,aux,';');
    plato=stoi(aux);
    R.setPlato(plato);
    //cout << "Plato: " << getPlato() << endl;

    //Extraemos el nombre de la receta
    getline(is,nombre,';');
    R.setNombre(nombre);
    //cout << "Nombre: " << getNombre() << endl;

    //Extraemos los pair de nombre de ingredientes y cantidad
    getline(is,aux);
    
    for(unsigned int i=0; i<aux.size(); i++){ //Para saber cuantas veces aparece el ';' paraluego en el while saber cuantas iteraciones hacer (es decir, cuantos "trozos" hay)
        if(aux[i]==';')
            contador++;
    }

    unsigned int i=0, pos=0, pos2;
    while(i<contador){
        //Estas 3 lineas son para dividir el string grande en trozos cada uno entre ;.....;
        //Funciona de la siguiente manera: 
        //      1. El find me encuentra la posicion en el string de la primera ocurrencia del ';' y la mete en pos (los caracteres del string los empieza a contar en cero)
        //      2. En aux2 meto un substring del aux (que es donde esta la linea entera) que va desde el inicio de aux hasta una distancia de "pos"
        //         (en el metodo substr empieza a contar en 1, luego el ';' no lo incluye)
        //      3. Actualizo el aux, quitandole ese trozo (desde pos+1 para que empiece desde el siguiente del ';' hasta el final del string (esto es hasta el final porq solo lleva 1 argumento))
        pos=aux.find(';');
        aux2=aux.substr(0,pos);
        aux=aux.substr(pos+1);

        //Ahora, con ese trozo (que tendrá un string y un int) saco el nombre del ingrediente y la cantidad del mismo
        //Funciona de la siguiente manera:
        //      1. El rfind(' ') me encuentra la posicion en el string de la primera ocurrencia desde el final (es decir, la ultima ocurrencia desde el principio) del espacio en blanco
        //         Esto lo hago asi para que cuando lo haga con nombres con espacios en blanco por mitad, no de problemas
        //      2. Ahora mismo, pos2 está en el espacio entre el numero y lo ultimo del nombre del ingrediente. Luego metemos en cantidad
        //         el substring que empieza desde el siguiente del espacio en blanco (que sera ya el primer digito del numero) hasta el final del trozo
        //      3. Metemos en "aux_nombre_ing" el subsrting que va desde el inicio del trozo hasta una distancia de "pos2" (que era donde estaba el espacio en blanco)
        //         De nuevo, como el substr() empieza a contar en 1 (en orden usual), el ';' no lo pilla
        pos2=aux2.rfind(' ');
        cantidad=stoi(aux2.substr(pos2+1));
        aux_nombre_ing=aux2.substr(0,pos2);

        //Inserto en el pair auxiliar cada cosa
        ingrediente.first=aux_nombre_ing;
        ingrediente.second=cantidad;

        //Meto al final de la lista de R el pair auxiliar
        R.ings.push_back(ingrediente);

        i++;
    }

    //Extraemos el ultimo pair y lo metemos a nuestra lista
    pos2=aux.rfind(' '); //A estas alturas, en aux solo me queda el ultimo ingrediente (en la mayoria de los casos Sal 1)
    cantidad=stoi(aux.substr(pos2+1));
    aux_nombre_ing=aux.substr(0,pos2);

    ingrediente.first=aux_nombre_ing;
    ingrediente.second=cantidad;

    R.ings.push_back(ingrediente);  

    return is;
}