/**
  * @file receta.h
  * @brief Fichero cabecera del TDA Receta
  *
  */


#ifndef _RECETA_H
#define _RECETA_H

#include "ingredientes.h"
#include "instrucciones.h"
#include "color.h"
#include <string>
#include <list>
#include <iostream>
using namespace std;

/**
  *  @brief TDA receta
  *
  * Una instancia c del tipo de datos abstracto Receta recopila la informacion relativa a una receta de cocina:
  * el codigo de la misma, numero de plato y nombre de la receta que se prepara. Asi como una lista de los
  * ingredientes y la cantidad de los mismos, necesarios para preparar la receta.
  *
  * @author Jose Alberto Gomez Garcia
  * @author Jesus Navarro Merino
  * @date Noviembre 2019
  */

class receta {
	private:

/**
  * @page repReceta Rep del TDA receta
  *
  * @section invReceta Invariante de la representacion
  *
  * El invariante es:
  *	- rep.code = R*, donde * puede ser cualquier numero natural		
  *     - rep.plato = 1, 2 o 3. Debe ser un primer plato, un segundo plato, o un postre (tercer plato)
  * 	- rep.nombre != " ". Debe tener un nombre valido
  *     - rep.ings.first y rep.ings.second han de tener un espacio entre ambos
  *     - rep.calorias, rep.hc, rep.grasas, rep.proteinas y rep.fibra >= 0
  *     - rep.inst no puede estar vacio. La receta requerir� minimo de una instruccion
  *
  * @section faReceta Funcion de abstraccion
  *
  * Un objeto valido rep del TDA Receta representa una receta, formada por un codigo, numero de plato, nombre
  * y una lista de ingredientes y cantidades de cada uno de estos
  *
  * { rep.code, rep.plato, rep.nombre, rep.ings, rep.calorias, rep.hc, rep.grasas, rep.proteinas, rep.fibra, rep.inst }
  *
  */
		string code;				/**< Codigo de la receta */
		unsigned int plato;			/**< Numero de plato */
		string nombre;				/**< Nombre del plato a preparar */
		list<pair<string,unsigned int>> ings; 	/**< Lista STL con los ingredientes a utilizar y la cantidad de cada uno */
		float calorias;				/**< Calorias que aporta la receta */
		float hc;					/**< Hidratos de carbono que aporta la receta */
		float grasas;				/**< Grasas que aporta la receta */
		float proteinas;			/**< Proteinas que aporta la receta */
		float fibra; 				/**< Fibra que aporta la receta */
		instrucciones inst;			/**< Instrucciones necesarias para realizar la receta */
	public:

/**
  * @brief Constructor por defecto de un objeto de la clase Receta
  */
		receta();

/**
  * @brief Constructor con parametros para un objeto de la clase Receta
  * @param code Codigo de la receta
  * @param plato Numero de plato
  * @param nombre Nombre del plato
  * @param lista Lista de ingredientes y cantidades necesarios para preparar la receta
  */
		receta(string code,unsigned int plato,string nombre,list<pair<string,unsigned int>> lista);

/**
  * @brief Consultor del atributo code
  * @return Devuelve el codigo de la receta
  */
		string getCode();

/**
  * @brief Consultor del atributo plato
  * @return Devuelve el numero de plato
  */
		unsigned int getPlato();

/**
  * @brief Consultor del atributo nombre
  * @return Devuelve el nombre de la receta
  */
		string getNombre();

/**
  * @brief Consultor del atributo calorias
  * @return Devuelve el valor de las calorias totales de la receta
  */
		float getCalorias();

/**
  * @brief Consultor del atributo hidratos de carbono
  * @return Devuelve el valor de los hidratos de carbono totales de la receta
  */
		float getHc();

/**
  * @brief Consultor del atributo grasas
  * @return Devuelve el valor de las grasas totales de la receta
  */
		float getGrasas();

/**
  * @brief Consultor del atributo proteinas
  * @return Devuelve el valor de las proteinas totales de la receta
  */
		float getProteinas();

/**
  * @brief Consultor del atributo fibra
  * @return Devuelve el valor de la fibra total de la receta
  */
		float getFibra();

/**
  * @brief Modificador del atributo calorias
  * @param code Codigo que va a pasar a tener la receta
  */

		void setCode(string code);

/**
  * @brief Modificadr del atributo plato
  * @param plato Numero de plato de la receta
  */
		void setPlato(unsigned int plato);

/**
  * @brief Modificador del atributo nombre
  * @param nombre Nombre que va a tener la receta
  */
		void setNombre(string nombre);

/**
  * @brief Modifcador del atributo calorias
  * @param calorias Calorias totales que va a tener la receta
  */
		void setCalorias(float calorias);

/**
  * @brief Modificador del atributo hidratos de carbono
  * @param hc Hidratos de carbono que va a tener la receta
  */
		void setHc(float hc);

/**
  * @brief Modificador del atributo grasas
  * @param grasas Grasas que va a tener la receta
  */
		void setGrasas(float grasas);

/**
  * @brief Modificador del atributo proteinas
  * @param proteinas Proteinas que va a pasar a tener la receta
  */
		void setProteinas(float proteinas);

/**
  * @brief Modificador del atributo fibra
  * @param fibra Fibra que va a tener la receta en total
  */
		void setFibra(float fibra);

/**
	 * @brief Modificador del atributo inst
	 * @param inst Las instrucciones que tendra esta receta
	 */
		void setInstrucciones (instrucciones inst);

/**
  * @brief Numero de ingredientes necesarios la receta
  * @return Devuelve el tamaño de la lista de alimentos/cantidades
  */
		int ningredientes();

/**
  * @brief Reset de la lista de ingredientes y cantidades
  */
		void clear();

/**
  * @brief Tomamos el conjunto de Ingredientes para saber los valores nutricionales de cada uno de ellos y, en funcion de estos y la cantidad que requiere cada receta calcular los nutrientes que aporta cada receta
  * @param I Conjunto de Ingredientes del que debemos obtener los valores nutricionales.
  * @pre El conjunto de Ingredientes I no debe estar vacio.
  */
		void asignarValoresNutricionales(Ingredientes &I);

/**
  * @brief Saca por el flujo con un determinado formato, solamente el codigo, el nombre y el plato de la receta
  * @param os Flujo de salida donde queremos cargar la informacion mencionada.
  * @return Devuelve el flujo de salida.
  */
    ostream & informacionResumidaReceta(ostream & os);

/**
  * @brief Fusiona 2 recetas, creando una nueva receta que contiene todos los valores nutricionales, ingredientes e
  * instrucciones de ambas sumados
  * @param R Una de las recetas a fusionar (la otra es la que llama al metodo)
  */
    receta fusionarReceta(const receta &R);

/**
  * @brief Operador de salida, para poder volcar una Receta en un flujo
  * @param os Flujo de salida que usaremos para cargar la receta en el
  * @param R Objeto de la clase Receta que queremos volcar en el flujo
  * @return Devuelve el flujo de salida
  */
		friend ostream & operator << (ostream &os, const receta &R);

/**
  * @brief Operador de entrada, para poder volcar en una receta el contenido del flujo
  * @param is Flujo de entrada que usaremos para cargar datos en una receta
  * @param R Objeto de la clase Receta donde queremos guardar los datos
  * @return Devuelve el flujo de entrada
  */
		friend istream & operator >> (istream &is, receta &R);

/**
  * @section Iterator_receta Iterador no constante de la clase Receta.
  * Nos permite desplazarnos comodamente a traves de la lista de ingredientes y cantidades que tenemos en el TDA Receta
  */

/**
  * @brief Iterador no constante de receta.
  */ 
		class iterator {
			private:
				list<pair<string,unsigned int>>::iterator it;	/**< Iterator para la lista de ingredientes y cantidades */
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
  * @return Devuelve un pair de string y enteros de la lista de la receta (first es el nombre del ingrediente, y second la cantidad del mismo).
  */
			pair<string,unsigned int> & operator * () { return *it; }

/**
  * @brief Sobrecarga del operador ++, avanza la posicion del iterador en la lista de pares
  * @return Devuelve el iterador
  */
			iterator & operator ++ () { ++it; return *this; }

/**
  * @brief Sobrecarga del operador --, retrocede una posicion el iterador en la lista de pares
  * @return Devuelve el iterador
  */
			iterator & operator -- () { --it; return *this; }

/**
  * @brief Declaramos la clase receta como clase amiga
  */
			friend class receta;
		};
		
/**
  * @section Const_iterator_receta Iterador constante de la clase Receta.
  * Nos permite desplazarnos comodamente a traves de la lista de ingredientes y cantidades que tenemos en el TDA Receta
  */

/**
  * @brief Iterador constante de receta.
  */ 
		class const_iterator {
			private:			
				list<pair<string,unsigned int>>::const_iterator it;	/**< Const_iterator para la lista de ingredientes y cantidades */
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
  * @return Devuelve un pair de string y enteros de la lista de la receta (first es el nombre del ingrediente, y second la cantidad del mismo).
  */
			const pair<string,unsigned int> & operator * () { return *it; }

/**
  * @brief Sobrecarga del operador ++, avanza la posicion del iterador en la lista de pares
  * @return Devuelve el const_iterador
  */
			const_iterator & operator ++ () { ++it; return *this; }

/**
  * @brief Sobrecarga del operador --, retrocede una posicion el iterador en la lista de pares
  * @return Devuelve el const_iterador
  */
			const_iterator & operator -- () { --it; return *this; }

/**
  * @brief Declaramos la clase receta como clase amiga
  */
			friend class receta;
		};

/**
  * @brief Crea un iterador y lo coloca al principio de la lista de ingredientes y cantidades
  * @return Devuelve el iterador creado
  */
		iterator begin() { iterator i; i.it = ings.begin(); return i; }

/**
  * @brief Crea un iterador y lo coloca en la primera posicion fuera de la lista de ingredientes y cantidades
  * @return Devuelve el iterador creado
  */
		iterator end() { iterator i; i.it = ings.end(); return i; }

/**
  * @brief Crea un const_iterador y lo coloca al principio de la lista de ingredientes y cantidades
  * @return Devuelve el const_iterator creado
  */
		const_iterator begin() const { const_iterator i; i.it = ings.begin(); return i; }

/**
  * @brief Crea un const_iterador y lo coloca en la primera posicion fuera de la lista de ingredientes y cantidades
  * @return Devuelve el const_iterator creado
  */
		const_iterator end() const { const_iterator i; i.it = ings.end(); return i; }
};


#endif
