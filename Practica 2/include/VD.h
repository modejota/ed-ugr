/**
  * @file VD.h
  * @brief Fichero cabecera del TDA Vector Dinamico
  *
  */

#ifndef _VD_H
#define _VD_H

using namespace std;

/**
  *  @brief TDA Vector Dinamico
  *
  * Una instancia c del tipo de datos abstracto Vector Dinamico es un vector
  * unidimensional con capacidad para crecer y decrecer, que almacena un datos
  * de un determino tipo y tiene un determinado tamaño.
  *
  * @author Jose Alberto Gomez Garcia
  * @author Jesus Navarro Merino
  * @date Octubre 2019
  */


template <class T>		
	class VD{			
		private:
			
/**
  * @page repVD Rep del TDA Vector Dinamico
  *
  * @section invVD Invariante de la representacion
  *
  * El invariante es:
  *				- rep.n >= 0
  *				- rep.n < rep.reservados
  *				- rep.datos apunta a una zona de memoria con capacidad para albergar n elementos
  *
  * @section faVD Funcion de abstraccion
  *
  * Un objeto valido rep del TDA Vector Dinamico representa al vector de tamaño n.
  *
  * { rep.datos[0], rep.datos[1], ... , rep.datos[n-1] }
  *
  */
			T * datos;		/**< Vector dinamico de tipo T */
			int n;			/**< Numero de elementos en el vector dinamico */
			int reservados;	/**< Numero de elementos para los que se ha reservado memoria */
			
			
/**
  * @brief Redimensiona el vector dinamico, aumentandolo o disminuyendolo.
  * @param nuevo_tam Tamaño que va a pasar a tener el vector.
  * @pre d Debe ser mayor estricto de cero.
  */  
			void resize(int nuevo_tam);	
			
/**
  * @brief Copia los datos de un vector dinamico a otro.
  * @param original Vector dinamico desde el que se copian los datos. No se modifica.
  */   										
			void Copiar(const VD<T> & original);					
			
		public:
			
/**
  * @brief Constructor del vector diamico.
  * @param tam Tamaño del vector que se va a crear.
  * @pre tam ha de ser mayor estricto de cero.
  */   
			VD(int tam=5);
			
/**
  * @brief Copia los datos de un vector dinamico en otro
  * @param original Vector dinamico desde el que se copian los datos. No se modifica.
  */   
														
			VD(const VD<T> & original);	
			
/**
  * @brief Destructor del vector dinamico. Libera la memoria reservada
  */   								
			~VD();	
	
/**
  * @brief Sobrecarga del operador de asignacion
  * @param original Vector dinamico desde el que se copian los datos. No se modifica
  * @return Devuelve una copia del vector dinamico pasado como parametro
  */   												
			VD<T> & operator= (const VD<T> &original);		
			
/**
  * @brief Devuelve el numero de elementos del vector dinamico
  * @return Devuelve un valor entero con el numero de elementos del vector dinamico
  */   				
			int size() const {return n;}	
			
/**
  * @brief Sobrecarga del operador corchete
  * @param i Indice del elemento al que se desea acceder del vector datos
  * @return Devuelve el elemento en la posicion i del vector datos
  * @pre i Ha de ser mayor o igual a cero.
  */   								
			T & operator[] (int i) {return datos[i];}	
			
/**
  * @brief Sobrecarga del operador corchete
  * @param i Indice del elemento al que se desea acceder del vector datos
  * @return Devuelve el elemento en la posicion i del vector datos
  * @pre i Ha de ser mayor o igual a cero.
  */      					
			const T & operator[] (int i) const {return datos[i];}	
			
/**
  * @brief Insertamos un nuevo elemento en el vector dinamico
  * @param dato Dato que deseamos añadir al vector dinamico
  * @param pos Posicion a la que deseamos añadir el elemento
  * @pre pos La posicion de insercion ha de encontrarse entre cero y n
  */   		
			void Insertar(const T & dato, int pos);				
			
/**
  * @brief Borra elelemento de una posicion del vector dinamico
  * @param pos Posicion en la que deseamos borrar un elemento
  * @pre pos La posicion de borrado ha de encontrarse entre cero y n
  */   			
			void Borrar(int pos);		
			
/**
  * @brief Resetea los valores del vector dinamico que lo llama
  */
			void clear();							
			
        }; 				

#include "VD.cpp"
#endif 
