/**
  * @file recetas.h
  * @brief Fichero cabecera del TDA Recetas
  *
  */

#ifndef _RECETAS_H
#define _RECETAS_H

#include "receta.h"
#include <string>
#include <list>
#include <map>
#include <iostream>
using namespace std;

/**
  *  @brief TDA Recetas
  *
  * Una instancia c del tipo de datos abstracto Recetas recopila la informacion relativa 
  * a un conjunto de recetas no repetidas, identificadas por el codigo de cada una de ellas
  *
  * @author Jose Alberto Gomez Garcia
  * @author Jesus Navarro Merino
  * @date Noviembre 2019
  */


class recetas{
    private:

/**
  * @page repRecetas Rep del TDA Recetas
  *
  * @section invRecetas Invariante de la representacion
  *
  * El invariante es:
  *	- rep.first = R* donde * puede ser cualquier numero naturales y coincide con el codigo de la receta		
  * - rep.second ha de ser un objeto valido del TDA Receta descrito anteriormente
  *
  * @section faRecetas Funcion de abstraccion
  *
  * Un objeto valido rep del TDA Recetas representa un conjunto de recetas, identificadas por su codigo 
  * y ordenado por dicho codigo, inherente al map
  *
  * { rep[0].first rep[0].second, rep[1].first rep[1].second, ... , rep[size-1].first rep[size-1].second }
  * Nota: el uso del operador corchete es meramente para ilustrar las distintas posiciones y tama�o del map
  *
  */
        map<string,receta> datos;	/**< Map con las recetas, identificadas por sus codigos */

    public:

/**
  * @brief Constructor por defecto de un objeto de la clase Recetas
  */
        recetas();

/**
  * @brief Destructor por defecto de un objeto de la clase Recetas
  */
        ~recetas();

/**
  * @brief Resetea el map
  */
        void clear();

/**
  * @brief Nos indica el tamaño del map
  * @return Devuelve el tamaño del map
  */
        int size();

/**
  * @brief Borra una determinada receta 
  * @param c Codigo de la receta que deseamos borrar
  */
        void borrar(string c);

/**
  * @brief Sobrecarga del operador [] para poder acceder a una receta directamente dado su codigo
  * @param c Codigo de la receta a la que queremos acceder
  * @return Devuelve la receta asociada al codigo pasado como parametro
  */
        receta & operator [](string c);

/**
  * @brief Metodo para obtener los nutrientes que aporta cada receta, para todo el conjunto de recetas. Delega en el metodo de receta "asignarValoresNutricionales"    
  * @param I Conjunto de ingredientes de los que obtener los valores nutricionales
  * @pre El conjunto de Ingredientes I no puede estar vacio
  */

		void obtenerNutrientes(Ingredientes &I);

/**
  * @brief Inserta un elemento en el map de Recetas
  * @param elemento Receta que vamos a insertar en el map
  */
        void insertarElemento(pair<string,receta> &elemento);

/**
  * @brief Operador de salida, para poder volcar un objeto de tipo Recetas en un flujo
  * @param os Flujo de salida que usaremos para cargar el objeto Recetas en el
  * @param Rs Objeto de la clase Recetas que queremos volcar en el flujo
  * @return Devuelve el flujo de salida
  */
        friend ostream & operator << (ostream &os, recetas &Rs);

/**
  * @brief Operador de entrada, para poder volcar en una receta el contenido del flujo
  * @param is Flujo de entrada que usaremos para cargar los datos en un objeto Recetas
  * @param Rs Objeto de la clase Receta en el que guardaremos la informacion del flujo
  * @return Devuelve el flujo de entrada
  */
        friend istream & operator >> (istream &is, recetas &Rs);


/**
  * @section Iterador no constante de la clase Recetas.
  * Nos permite desplazarnos comodamente a traves del map con el conjunto de recetas
  */
        class iterator{
            private:
                map<string,receta>::iterator it;	/**< Iterator para el map de Recetas */
            public:

/**
  * @brief Constructor por defecto 
  */
            iterator() {}

/**
  * @brief Sobrecarga del operador de igualdad
  * @param i Iterador con el que se desea comprobar la igualdad
  * @return Devuelve true si ambos iteradores aputan al mismo elemento, false en otro caso
  */
            bool operator == (const iterator &i) const { return it == i.it; }

/**
  * @brief Sobrecarga del operador de desigualdad
  * @param i Iterador con el que se desea comprobar la desigualdad
  * @return Devuelve true si ambos iteradores aputan a distinto elemento, false en otro caso
  */
  	   		bool operator != (const iterator &i) const { return it != i.it; }

/**
  * @brief Sobrecarga del operador estrellita/asterisco
  * @return Devuelve la receta del elemento apuntado en ese momento por el iterador (internamente, cada elemento del map es un pair de los tipos que se hayan especificado)
  */
            receta & operator * () { return (*it).second; }

/**
  * @brief Sobrecarga del operador ++, avanza la posicion del iterador en el conjunto de elementos del map
  * @return Devuelve el iterador
  */
	    	iterator & operator ++ () { ++it; return *this; }

/**
  * @brief Sobrecarga del operador --, retrocede una posicion el iterador en el conjunto de elemnetos del map
  * @return Devuelve el iterador
  */
	    	iterator & operator -- () { --it; return *this; }

/**
  * @brief Hacemos la clase recetas amiga
  */
	    	friend class recetas;
        };

/**
  * @section Iterador constante de la clase Recetas.
  * Nos permite desplazarnos comodamente a traves del map con el conjunto de recetas
  */
        class const_iterator{
            private:
                map<string,receta>::const_iterator it;	/**< Const_iterator para el map de Recetas */
            public:

/**
  * @brief Consultor por defecto 
  */
            const_iterator() {}

/**
  * @brief Sobrecarga del operador de igualdad
  * @param i Iterador con el que se desea comprobar la igualdad
  * @return Devuelve true si ambos iteradores aputan al mismo elemento, false en otro caso
  */
	    	bool operator == (const const_iterator &i) const { return it == i.it; }

/**
  * @brief Sobrecarga del operador de desigualdad
  * @param i Iterador con el que se desea comprobar la desigualdad
  * @return Devuelve true si ambos iteradores aputan a distinto elemento, false en otro caso
  */
  	
	    	bool operator != (const const_iterator &i) const { return it != i.it; }

/**
  * @brief Sobrecarga del operador estrellita/asterisco
  * @return Devuelve la receta del elemento apuntado en ese momento por el iterador (internamente, cada elemento del map es un pair de los tipos que se hayan especificado)
  */
	    	const receta & operator * () { return (*it).second; }

/**
  * @brief Sobrecarga del operador ++, avanza la posicion del iterador en el conjunto de elementos del map
  * @return Devuelve el const_iterador
  */
	    	const_iterator & operator ++ () { ++it; return *this; }

/**
  * @brief Sobrecarga del operador --, retrocede una posicion el iterador en el conjunto de elementos del map
  * @return Devuelve el iterador
  */
	    	const_iterator & operator -- () { --it; return *this; }

/**
  * @brief Hacemos la clase recetas amiga
  */
	    	friend class recetas;
        };

/**
  * @brief Crea un iterador y lo coloca al principio del map de recetas
  * @return Devuelve el iterator creado
  */
        iterator begin() { iterator i; i.it = datos.begin(); return i; }

/**
  * @brief Crea un iterador y lo coloca en la primera posicion fuera del map de recetas
  * @return Devuelve el iterador creado
  */
	    iterator end() { iterator i; i.it = datos.end(); return i; }

/**
  * @brief Crea un const_iterador y lo coloca al principio del map de recetas
  * @return Devuelve el const_iterator creado
  */
	    const_iterator begin() const { const_iterator i; i.it = datos.begin(); return i; }

/**
  * @brief Crea un const_iterator y lo coloca en la primera posicion fuera del map de recetas
  * @return Devuelve el const_iterator creado
  */
	    const_iterator end() const { const_iterator i; i.it = datos.end(); return i; }


};

#endif
