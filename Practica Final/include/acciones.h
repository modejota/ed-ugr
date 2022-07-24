/**
  * @file acciones.h
  * @brief Fichero cabecera del TDA Acciones
  *
  */


#ifndef _ACCIONES_H
#define _ACCIONES_H

#include <map>
#include <string>
#include <iostream>

using namespace std;


/**
  * @brief TDA acciones
  *
  * Una instancia del TDA acciones recoge un conjunto de acciones y su ariedad,
  * es decir, el numero de ingredientes que se necesitan para llevar a 
  * cabo dicha accion.
  *
  * @author Jesús Navarro Merino
  * @author José Alberto Gómez García
  * @date Diciembre 2019
  */
class acciones{
	private:

/**
  * @page repAcciones Rep del TDA Acciones
  *
  * @section invAcciones Invariante de la representacion
  *
  * El invariente es:
  * 	- rep.first es un string no vacio que representa la accion, pueden ser: 
  *   		 * Cortar, Mezclar, Pelar, Add, Calentar, Reservar,  Triturar, Cocer, Hornear, Enharinar, Freir, Formar, Emplatar y Acompañar (en caso de fusionar recetas).
  * 
  * 	- rep.second es la ariedad de la accion.
  * 		* Para el ejercicio propuesto puede ser 1 ó 2.
  * 
  * @section funcAcciones Funcion de abstraccion
  *
  * Un objeto valido rep del TDA acciones representa un conjunto de acciones para cocinar, cada una de ellas con el numero
  * de ingredientes necesarios para realizarla.
  *
  * {(rep[0].first, rep[0].second), (rep[1].first, rep[1].second), ..., (rep[size-1].first, rep[size-1].second)}
  * 
  * Nota: el uso del operador corchete es meramente para ilustrar las distintas posiciones y tamaño del map.
  */
		map<string,unsigned char> datos; /**<Map de strings y unsigned chars>*/
	
	public:
		/**
		  * @brief Constructor por defecto sin parametros de un objeto acciones.
		  */
		acciones ();
		
		
		/**
		  * @brief Desctructor por defecto de un objeto acciones.
		  */
		~acciones();
		
		
		/**
		  * @brief Inserta una nueva acción con su ariedad en nuestro conjunto de acciones.
		  * @param accion string con el nombre de la acción.
		  * @param ariedad unsigned char con el nº de ingredientes que involucra. 
		  */
		void Insertar (string accion, unsigned char ariedad);
		
		
		/**
		  * @brief Borra una accion (y su aridad) de nuestro conjunto de acciones.
		  * @param accion string con el nombre de la accion a borrar.
		  */
		void Borrar (string accion);
		
		
		/**
		  * @brief Sobrecarga del operador corchete (indexacion). Retorna la ariedad de la acción, permitiendo su modificación.
		  * @param nombre string con el nombre de la acción.
		  * @return devuelve un unsigned char con la ariedad de la acción.
		  */
		unsigned char operator [] (string &nombre);
		
		
		/**
		  * @brief Sobrecarga del operador corchete (indexacion). Retorna la ariedad de la acción, no permite su modificación.
		  * @param nombre string con el nombre de la acción.
		  * @return devuelve un unsigned char con la ariedad de la acción.
		  */
		const unsigned char operator [] (string &nombre) const;


		/**
		  * @brief Obtenemos la cantidad de veces que aparece la "key" en nuestro conjunto de acciones.
		  * @param key key de la que queremos saber el numero de apariciones en nuestro conjunto de acciones.
		  * @return devuelve un unsigned int con las veces que aparece la key. Puede ser 1 ó 0 al no poder tener acciones repetidas.
		  */
		const unsigned int count (string &key) const;
		
		
		/**
		  * @brief Obtenemos el número de acciones.
		  * @return devuelve un entero con el número de acciones.
		  */
		int size () { return datos.size(); }
		
		
		/**
		  * @brief Vacia nuestro conjunto de acciones.
		  */
		void clear () { datos.clear(); }
		
		
		/**
		  * @brief Operador de entrada. Dado un archivo, extrae todas las acciones hasta llegar al final del mismo.
		  * @param is flujo de entrada que utilizaremos.
		  * @param Ac objeto de la clase acciones donde se van a escribir los acciones leidas del archivo.
		  * @return Devuelve el flujo de entrada (is) pasado como parametro.
		  */
		friend istream & operator >> (istream &is, acciones &Ac);
		
		
		/**
		  * @brief Operador de salida. Copia los datos de un objeto de acciones en un flujo de salida.
		  * @param os flujo de salida donde se enviaran los datos del objeto de la clase acciones
		  * @param Ac objeto de la clase Acciones cuyos dato se van a cargan en el flujo. No se puede modificar.
		  * @return Devuelve el flujo de salida (os) pasado como parametro.
		  */
		friend ostream & operator << (ostream & os, const acciones & Ac);
		
		
/**
  * @section Iterator_acciones Iterador no constante de la clase Acciones.
  * Nos permite desplazarnos comodamente a traves del conjunto de acciones que tenemos en el TDA Acciones.
  */

/**
  * @brief Iterador no constante de acciones.
  */  
		class iterator{
			private:
				map<string,unsigned char>::iterator it; /**<iterator del mapa de acciones>*/
				
			public:
				/**
				  * @brief Constructor del iterator.
				  */
				iterator(){}
				
				/**
				  * @brief Sobrecarga del operador de igualdad.
				  * @param i Iterador constante por referencia.
				  * @return True si son iguales, false en otro caso.
				  */
				bool operator == (const iterator &i) const{
					return it == i.it;
				}
				
				/**
				  * @brief Sobrecarga del operador de desigualdad.
				  * @param i Iterador constante por referencia.
				  * @return True si no son iguales, false en otro caso.
				  */
				bool operator != (const iterator &i) const{
					return it != i.it;
				}
				
				/**
				  * @brief Sobrecarga del operador estrellita/asterisco.
				  * @return Devuelve la accion a la que apunta el iterador, un pair<string,unsigned char>.
				  */
				pair<const string,unsigned char> &operator*(){
					return *it;
				}
				
				/**
				  * @brief Sobrecarga del operador ++. Hace avanzar el iterador en una posicion.
				  * @return Devuelve el propio iterador tras ser incrementado.
				  */
				iterator &operator ++(){
					++it;
					return *this;
				}
				
				/**
				  * @brief Sobrecarga del operador --. Hace retroceder el iterador en una posicion.
				  * @return Devuelve el propio iterador tras ser decrementado.
				  */
				iterator &operator --(){
					--it;
					return *this;
				}
				
				friend class acciones;
		};
		
		
		
/**
  * @section Const_iterator_acciones Iterador constante de la clase Acciones.
  * Nos permite desplazarnos comodamente a traves del conjunto de acciones que tenemos en el TDA Acciones, sin poder modificarlas.
  */

/**
  * @brief Iterador constante de acciones.
  */ 
		class const_iterator{
			private:
				map<string,unsigned char>::const_iterator it; /**<const_iterator del mapa de acciones>*/
				
			public:
				/**
				  * @brief Constructor del const_iterator.
				  */
				const_iterator(){}
				
				/**
				  * @brief Sobrecarga del operador de igualdad.
				  * @param i Const_iterator constante por referencia.
				  * @return True si son iguales, false en otro caso.
				  */
				bool operator == (const const_iterator &i) const{
					return it == i.it;
				}
				
				/**
				  * @brief Sobrecarga del operador de desigualdad.
				  * @param i Const_iterator constante por referencia.
				  * @return True si no son iguales, false en otro caso.
				  */
				bool operator != (const const_iterator &i) const{
					return it != i.it;
				}
				
				/**
				  * @brief Sobrecarga del operador estrellita/asterisco.
				  * @return Devuelve la accion (constante) a la que apunta el iterador, un pair<string,unsigned char>. 
				  */
				const pair<const string,unsigned char> &operator*(){
					return *it;
				}
				
				/**
				  * @brief Sobrecarga del operador ++. Hace avanzar el const_iterator en una posicion.
				  * @return Devuelve el propio const_iterator tras ser incrementado.
				  */
				const_iterator &operator ++(){
					++it;
					return *this;
				}
				
				/**
				  * @brief Sobrecarga del operador --. Hace retroceder el const_iterator en una posicion.
				  * @return Devuelve el propio const_iterator tras ser decrementado.
				  */
				const_iterator &operator --(){
					--it;
					return *this;
				}
				
				friend class acciones;
		};
		
		/**
		  * @brief Obtener el inicio del conjunto de acciones.
		  * @return Devuelve un iterator apuntando al incio del map.
		  */
		iterator begin(){
			iterator i;
			i.it = datos.begin();
			return i;
		}
		
		/**
		  * @brief Obtener el final del conjunto de acciones.
		  * @return Devuelve un iterator apuntando al final del map.
		  */
		iterator end(){
			iterator i;
			i.it = datos.end();
			return i;
		}
		
		/**
		  * @brief Obtener el inicio del conjunto de acciones.
		  * @return Devuelve un const_iterator apuntando al incio del map.
		  */
		const_iterator cbegin() const{
			const_iterator i;
			i.it = datos.cbegin();
			return i;
		}
		
		/**
		  * @brief Obtener el final del conjunto de acciones.
		  * @return Devuelve un const_iterator apuntando al final del map.
		  */
		const_iterator cend() const{
			const_iterator i;
			i.it = datos.cend();
			return i;
		}
};




#endif
