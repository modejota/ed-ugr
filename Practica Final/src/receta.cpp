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

void receta::setInstrucciones (instrucciones inst){
    this->inst=inst;
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

ostream & receta::informacionResumidaReceta(ostream & os){
    os << FBLU(BOLD("CODE: ")) << code << FBLU(BOLD("\tNOMBRE: ")) << nombre 
       << FBLU(BOLD("\tPLATO: ")) << plato << endl;

    return os;
}

receta receta::fusionarReceta(const receta &R){
    receta r_aux,fusion;
    string code_fusion, nombre_fusion;
    float cal_fus, Hc_fus, prot_fus, gras_fus, fib_fus;

    //Calculamos codigo y nombre tras la fusion
    code_fusion="F_" + code + "_" + R.code;
    nombre_fusion="Fusion " + nombre + " y " + R.nombre;

    r_aux.setCode(code_fusion);
    r_aux.setNombre(nombre_fusion);
    r_aux.setPlato(plato);  //Se nos dijo que el numero de plato fuese el del primer plato que fusionamos.

    //Copiamos la lista de ingredientes de la receta "this", en r_aux
    r_aux.ings.assign(ings.begin(),ings.end());

    //Vamos a recorrer la lista de ingredientes de la receta R, y vamos viendo cual está ya en r_aux o no, y en funcion de eso
    //simplemente sumamos las cantidades, o metemos un nuevo ingrediente
    receta::iterator itA; //Este iterador es el que recorre la receta r_aux
    receta::const_iterator itR; //Este iterador es el que recorre la receta R
    bool esta;

    for(itR=R.begin(); itR!=R.end();++itR){
        esta=false;
        itA=r_aux.begin();
        while(itA!=r_aux.end() && !esta){
            if((*itR).first == (*itA).first){
                esta=true;
            }
            else{
                ++itA;
            }
        }

        //Si el ingrediente *itR.first, está en "this" sumamos las cantidades
        if(esta){
            //Sumo la cantidad de ingrediente repetido a lo que ya tenia la otra receta 
            (*itA).second+=(*itR).second;
        }

        //Si no está, tenemos que añadir un nuevo elemento al list de ingredientes
        else{
            r_aux.ings.push_back(pair<string,unsigned int>((*itR).first,(*itR).second));
        }
    }

    //Sumo los valores nutricionales de ambas recetas
    cal_fus=calorias+R.calorias;
    Hc_fus=hc+R.hc;
    prot_fus=proteinas+R.proteinas;
    gras_fus=grasas+R.grasas;
    fib_fus=fibra+R.fibra;

    r_aux.setCalorias(cal_fus);
    r_aux.setHc(Hc_fus);
    r_aux.setProteinas(prot_fus);
    r_aux.setGrasas(gras_fus);
    r_aux.setFibra(fib_fus);

    instrucciones inst_aux=R.inst;
    //Combinamos las instrucciones directamente en las de r_aux
    r_aux.inst=inst.fusionarInstrucciones(inst_aux);

    fusion=r_aux;
    return fusion;
}



ostream & operator << (ostream &os, const receta &R){
    receta::const_iterator it;
    os << FBLU(BOLD("CODE: ")) << R.code << " " << FBLU(BOLD("RECETA: ")) << R.nombre << " " 
       << FBLU(BOLD("PLATO: ")) << R.plato << endl;

    //Ingredientes
    os << UNDL("Ingredientes:") << endl << endl;
    for(it=R.begin(); it!=R.end(); ++it){
        os << "\t" << (*it).first << " " << (*it).second << endl;
    }
    cout << endl;
    //Informacion nutricional
    os << UNDL("Informacion Nutricional:") << endl << endl;
    os << "\tCalorias: " << R.calorias << endl
       << "\tHidratos de Carbono: " << R.hc << endl
       << "\tGrasas: " << R.grasas << endl
       << "\tProteinas: " << R.proteinas << endl
       << "\tFibra: " << R.fibra << endl;
    cout << endl;

    //Pasos a seguir
    os << R.inst << endl;

    return os;
}

istream & operator >> (istream &is, receta &R){
    string code, nombre, aux, aux_nombre_ing, aux2;
    //float calorias, hc, grasas, proteinas, fibra;
    unsigned int plato, cantidad, contador=0;
    pair<string,unsigned int> ingrediente;

    //Extraemos el code
	getline(is,code,';'); //Va leyendo la linea hasta el delimitador(extrae el delimitador pero no lo mete en el string, y se queda justo después del delimitador)
        if(!is || code=="\n") //Si acaba el fichero o se encuentra una linea vacia, returnea el flujo y para de extraer
           return is;
    R.setCode(code);
    //cout << "Codigo: " << R.getCode() << endl;

    //Extraemos el numero de plato
    getline(is,aux,';');
    plato=stoi(aux);
    R.setPlato(plato);
    //cout << "Plato: " << R.getPlato() << endl;

    //Extraemos el nombre de la receta
    getline(is,nombre,';');
    R.setNombre(nombre);
    //cout << "Nombre: " << R.getNombre() << endl;

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


        //Con este while me quito posibles espacios indeseados que pudiera haber en el txt (y que harian que este 
        //algoritmo de extraccion no funcionase)
        while (aux2[aux2.size()-1]==' ')
           aux2.pop_back();

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
     
     //De nuevo quitamos los posibles espacios que pudieran haber
     while (aux[aux.size()-1]==' ')
        aux.pop_back();

    //Extraemos el ultimo pair y lo metemos a nuestra lista
    pos2=aux.rfind(' '); //A estas alturas, en aux solo me queda el ultimo ingrediente (en la mayoria de los casos Sal 1)
    cantidad=stoi(aux.substr(pos2+1));
    aux_nombre_ing=aux.substr(0,pos2);

    ingrediente.first=aux_nombre_ing;
    ingrediente.second=cantidad;

    R.ings.push_back(ingrediente);  

    return is;
}
