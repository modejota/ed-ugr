/**
  * @file ingredientes.h
  * @brief Fichero cabecera del TDA Ingredientes
  *
  */


#ifndef _INGREDIENTES_H
#define _INGREDIENTES_H

#include "ingrediente.h"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/**
  *  @brief TDA Ingredientes
  *
  * Una instancia c del tipo de datos abstracto Ingredientes recopila la informacion 
  * nutricional de un determinado conjunto de alimentos, ordenado por nombre y tipo.
  *
  * @author Jose Alberto Gomez Garcia
  * @author Jesus Navarro Merino
  * @date Noviembre 2019
  */

class Ingredientes {
	private:

/**
  * @page repIngredientes Rep del TDA Ingredientes
  *
  * @section invIngredientes Invariante de la representacion
  *
  * El invariante es:
  *	- rep.datos.size y rep.indice.size >= 0			Al tratar con numeros naturales
  *
  * @section faIngredientes Funcion de abstraccion
  *
  * Un objeto valido rep del TDA Ingredientes representa un conjunto de ingredientes ordenado por nombre y tipo
  *
  * { rep.datos[0] rep.indice[0], rep.datos[1] rep.indice[1] ... rep.datos[size-1] rep.indice[size-1]  }
  *
  */
  
		vector<Ingrediente> datos; 	/**< Vector STL con los alimentos ordenados por nombre */
		vector<int> indice;	 		/**< Vector STL con los indices que ordenan los alimentos por tipo, y a igualdad de tipo por nombre */
		
/**
  * @brief Metodo para resetear los vectores STL, de tener tamaños mayores a 0 se llama al metodo clear de la STL
  */		
		void clear();
	 
		
	public:
		
/**
  * @brief Constructor por defecto de un conjunto de Ingredientes
  */
		Ingredientes();
		
/**
  * @brief Destructor por defecto de un conjunto de Ingredientes, elimina los vectores.
  */
		~Ingredientes();
		
/**
  * @brief Metodo para insertar un ingrediente ordenado segun su nombre y tipo en un conjunto de ingredientes
  * @param nuevo Ingrediente que deseamos insertar
  */
    	void Insertar(const Ingrediente & nuevo);
		
/**
  * @brief Metodo para borrar un elemento del conjunto de ingredientes
  * @param di Nombre del ingrediente que deseamos eliminar
  */						
		void borrar (const string &di);
		
/**
  * @brief Metodo para obtener un ingrediente a partir de su nombre
  * @param nombre Nombre del ingrediente que queremos obtener
  * @return Obtenemos un objeto de la clase Ingrediente. Si no se encuentra el ingrediente con el nombre especificado se devuelve uno generico
  */		
		Ingrediente get(string nombre);
		
/**
  * @brief Sobrecarga del operador corchete para obtener un Ingrediente dada la ordenacion por nombre
  * @param i Indice del elemento al que queremos acceder segun el orden por nombre
  * @return Obtenemos un objeto de la clase Ingrediente
  */	
		Ingrediente & operator[](int i);
		
/**
  * @brief Metodo para obtener una lista con los nombres de todos los tipos de ingredientes que tenemos
  * @return Obtenemos un vector dinamico de strings con todos los nombres de los tipos de ingredientes que tenemos.
  */	
		vector<string> getTipos();
		
/**
  * @brief Metodo para obtener un conjunto de ingredientes del tipo de alimento que se especifique
  * @param tipo Nombre del tipo de alimento por el que queremos filtrar. Si no existe se obtiene una coleccion Ingredientes vacia
  * @return Obtenemos un objeto de la clase Ingredientes con los elementos filtrados por tipo
  */		
		Ingredientes getIngredienteTipo(string tipo);
		
/**
  * @brief Metodo para imprimir los elementos ordenados mediante el tipo, y a igualdad de tipo por nombre
  * @param os Flujo de salida donde estan cargados los ingredientes
  */	
  
  		void ImprimirPorTipo(ostream &os);

/**
  * @brief Metodo para saber si un determinado tipo de alimento existe en nuestro conjunto de ingredientes o no
  * @param tipo Nombre del tipo del que queremos comprobar la existencia
  * @return Devuelve un booleano true si el tipo existe o uno falso si no existe el tipo en cuestion en nuestro conjunto de ingredientes.
  */	
  
  		bool existeTipo(string tipo);
  		
/**
  * @brief Metodo para obtener el tamaÃ±o de un objeto Ingredientes
  * @return El tamaï¿½o del objeto, es decir, es de sus vectores dinamicos
  */ 
		int size();
		 
/**
  * @brief Sobrecarga del operador de entrada
  * @param is Flujo de entrada donde se encuentran los ingredientes a cargar
  * @param I Objeto de la clase Ingredientes donde guardaremos los datos del flujo
  * @return Devuelve el flujo de entrada.
  */ 	
		friend istream & operator >> (istream &is, Ingredientes &I);
		
/**
  * @brief Sobrecarga del operador de salida
  * @param os Flujo de salida donde cargaremos los ingredientes a mostrar/guardar.
  * @param I Objeto de la clase Ingredientes que queremos mostrar
  * @return Devuelve el flujo de salida
  */ 			
		friend ostream & operator << (ostream &os, Ingredientes &I);
		
		
/**
  * @section Iterador no constante de la clase Ingredientes.
  * Nos permite desplazarnos facilmente a traves de la lista de ingredientes.
  */
	class iterator {
		private:
			vector<Ingrediente>::iterator it;			/**< Iterator para el vector de Ingredientes */
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
  * @return Devuelve un determinado Ingrediente
  */
			Ingrediente & operator * () { return *it; }
			
/**
  * @brief Sobrecarga del operador ++, avanza la posicion del iterador en el vector de Ingredientes
  * @return Devuelve el propio iterator
  */
			iterator & operator ++ () { ++it; return *this; }
			
/**
  * @brief Sobrecarga del operador --, retrocede una posicion el iterador en el vector de Ingredientes
  * @return Devuelve el propio iterator
  */
			iterator & operator -- () { --it; return *this; }
			
/*
 * @brief Declaramos la clase Ingredientes como clase amiga
 */
			friend class Ingredientes;
			
	};

/**
  * @section Iterador constante de la clase Ingredientes.
  * Nos permite desplazarnos facilmente a traves de la lista de ingredientes, sin posibilidad de modificarla.
  */	
	class const_iterator {
		private:
			vector<Ingrediente>::const_iterator it;		/**< Const_iterator para el vector de Ingredientes */
		public:
/**
  * @brief Constructor por defecto
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
  * @return Devuelve el Ingrediente al que apunte el iterador. No admite modificación al ser constante
  */
			const Ingrediente & operator * () { return *it; }
			
/**
  * @brief Sobrecarga del operador ++, avanza la posicion del iterador en el vector de Ingredientes
  * @return Devuelve el propio const_iterador
  */
			const_iterator & operator ++ () { ++it; return *this; }
			
/**
  * @brief Sobrecarga del operador --, retrocede una posicion el iterador en el vector de Ingredientes
  * @return Devuelve el propio const_iterator
  */
			const_iterator & operator -- () { --it; return *this; }
			
/**
  * @brief Declaramos la clase Ingredientes como clase amiga
  */
			friend class Ingredientes;
	};

/**
  * @brief Crea un iterator y lo coloca al principio del vector de Ingredientes
  * @return Devuelve el iterador creado
  */	
	iterator begin() { iterator i; i.it = datos.begin(); return i; }
	
/**
  * @brief Crea un iterator y lo coloca en la primera posicion fuera del vector de Ingredientes
  * @return Devuelve el iterator creado
  */
	iterator end() { iterator i; i.it = datos.end(); return i; }
	
/**
  * @brief Crea un const_iterator y lo coloca al principio del vector de Ingredientes
  * @return Devuelve el const_iterator creado
  */
	const_iterator begin() const { const_iterator i; i.it = datos.begin(); return i; }
	
/**
  * @brief Crea un const_iterator y lo coloca en la primera posicion fuera de la lista del vector de Ingredientes
  * @return Devuelve el const_iterator creado
  */
	const_iterator end() const { const_iterator i; i.it = datos.end(); return i; }
	
	
	
};
#endif
