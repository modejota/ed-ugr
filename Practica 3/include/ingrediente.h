/**
  * @file ingrediente.h
  * @brief Fichero cabecera del TDA Ingrediente
  *
  */

#ifndef _INGREDIENTE_H
#define _INGREDIENTE_H

#include <iostream>
#include <string>
using namespace std;

/**
  *  @brief TDA Ingrediente
  *
  * Una instancia c del tipo de datos abstracto Ingrediente recopila la informacion 
  * nutricional de un determinado alimento, en concreto, el nombre del alimento,
  * calorias/100g, porcentaje de hidratos de carbono, proteinas, grasas, fibra y 
  * tipo de ingrediente.
  *
  * @author Jose Alberto Gomez Garcia
  * @author Jesus Navarro Merino
  * @date Noviembre 2019
  */
 
class Ingrediente {
	private:
		
/**
  * @page repIngrediente Rep del TDA Ingrediente
  *
  * @section invIngrediente Invariante de la representacion
  *
  * El invariante es:
  *		- rep.calorias, rep.hidratos_carbono, rep.proteinas, rep.grasas, rep.fibra >= 0		Al tratar con numeros naturales
  *		- rep.calorias, rep.hidratos_carbono, rep.proteinas, rep.grasas, rep.fibra <= 100	Al tratar con porcentajes
  *		- rep.calorias + rep.hidratos_carbono + rep.proteinas + rep.grasas + rep.fibra = 100	Se ha de sumar una unidad, 100%
  *		- rep.nombre, rep.tipo_ingrediente != "".			Los nombres y tipos no pueden estar vacios
  *
  * @section faIngrediente Funcion de abstraccion
  *
  * Un objeto valido rep del TDA Ingrediente representa el nombre, tipo e informacion nutricional de un alimento
  *
  * { rep.nombre, rep.calorias, rep.hidratos_carbono, rep.proteinas, rep.grasas, rep.fibra, rep.tipo_ingrediente  }
  *
  */		
		string nombre;				/**< String con el nombre del alimento */
		float calorias;				/**< Calorias por cada 100gr de alimento */
		float hidratos_carbono;		/**< Porcentaje de hidratos de carbono */
		float proteinas;			/**< Porcentaje de proteinas */
		float grasas;				/**< Porcentaje de grasas */
		float fibra;				/**< Porcentaje de fibra */
		string tipo_ingrediente;	/**< String con el tipo de ingrediente */
		
/**
  * @brief Metodo para copiar los datos de un ingrediente en otro
  * @param otro Ingrediente a copiar. No se modifica
  */  
		void Copiar(const Ingrediente & otro);

	public:
	  
/**
  * @brief Constructor sin parametros. Crea un objeto con unos valores por defecto
  */  
		Ingrediente();	

/**
  * @brief Constructor con parametros. Crea un objeto con los valores de los argumentos
  * @param nombre Nombre que recibe el alimento
  * @param calorias Numero de calorias por cada 100gr de alimento
  * @param hidratos_carbono Porcentaje de hidratos de carbono que tiene el alimento
  * @param proteinas Porcentaje de proteinas que tiene el alimento
  * @param grasas Porcentaje de grasas que tiene el alimento
  * @param fibra Porcentaje de fibra que tiene el alimento
  * @param tipo_ingrediente Nombre del tipo de ingrediente al que pertenece el alimento
  */   
		Ingrediente(string nombre, float calorias, float hidratos_carbono, float proteinas, float grasas, float fibra, string tipo_ingrediente);
			
/**
  * @brief Modificador del atributo nombre del ingrediente
  * @param nombre Nombre del alimento
  */  
		void setNombre(string nombre);

/**
  * @brief Modificador del atributo calorias del ingrediente
  * @param calorias Numero de calorias por cada 100gr de alimento
  */  
		void setCalorias(float calorias);
			
/**
  * @brief Modificador del atributo hidratos de carbono del ingrediente
  * @param hidratos_carbono Porcentaje de hidratos de carbono
  */  
		void setHc(float hidratos_carbono);
			
/**
  * @brief Modificador del atributo proteinas del ingrediente
  * @param proteinas Porcentaje de proteinas
  */  
		void setProteinas(float proteinas);

/**
  * @brief Modificador del atributo grasas del ingrediente
  * @param grasas Porcentaje de grasas
  */  
		void setGrasas(float grasas);
			
/**
  * @brief Modificador del atributo fibra del ingrediente
  * @param fibra Porcentaje de hidratos de carbono
  */  
		void setFibra(float fibra);

/**
  * @brief Modificador del atributo tipo de ingrediente al que pertenece el alimento
  * @param tipo_ingrediente Tipo de ingrediente del alimento
  */  
		void setTipo(string tipo_ingrediente);
			
/**
  * @brief Consultor del atributo nombre del ingrediente
  * @return Devuelve el nombre del alimento
  */  
		string getNombre()const;

/**
  * @brief Consultor del atributo calorias del ingrediente
  * @return Devuelve el numero de calorias por cada 100gr de alimento
  */  
        float getCalorias()const;
			
/**
  * @brief Consultor del atributo hidratos de carbono del ingrediente
  * @return Devuelve el porcentaje de hidratos de carbono del alimento
  */  
		float getHc()const;
			
/**
  * @brief Consultor del atributo proteinas del ingrediente
  * @return Devuelve el porcentaje de proteinas del alimento
  */  
		float getProteinas()const;

/**
  * @brief Consultor del atributo grasas del ingrediente
  * @return Devuelve el porcentaje de grasas del alimento
  */  
		float getGrasas()const;
			
/**
  * @brief Consultor del atributo fibra del ingrediente
  * @return Devuelve el porcentaje de fibra del alimento
  */  
		float getFibra()const;

/**
  * @brief Consultor del atributo tipo de ingrediente al que pertenece el alimento
  * @return Devuelve el nombre del tipo de alimento al que pertenece el ingrediente
  */  
		string getTipo()const;
		
/**
  * @brief Sobrecarga del operador de asignaci�n. Para poder igualar dos ingredientes
  * @param original Objeto de la clase ingrediente del que queremos copiar los datos. No se modifica
  * @return Devuelve una copia del alimento pasado como parametro.
  */  
		Ingrediente & operator= (const Ingrediente &original);

/**
  * @brief Sobrecarga del operador de salida, para mostrar los datos de un ingrediente de una tacada
  * @param salida Flujo de salida que utilizaremos. 
  * @param original Ingrediente del que deseamos imprimir los datos. No se modifica
  * @return salida Devuelve el flujo de salida
  */ 
		friend ostream & operator<< ( ostream &salida , const Ingrediente & original); 		
	
/**
  * @brief Sobrecarga del operador de entrada, para guardar los datos de un ingrediente de una tacada
  * @param entrada Flujo de entrada que utilizaremos. 
  * @param original Ingrediente en el que deseamos guardar los datos
  * @return entrada Devuelve el flujo de entrada
  */ 
		friend istream & operator>> ( istream &entrada , Ingrediente & original); 	
/**
  * @brief Sobrecarga del operador de igualdad. Para poder comprobar si dos ingredientes son iguales
  * @param original Objeto de la clase ingrediente con el que queremos comprobar la igualdad. No se modifica al ser constante
  * @return Devuelve si el ingrediente pasado como argumento es igual o no al que llama al metodo	
  */ 
		bool operator== (const Ingrediente &original) const;
		
/**
  * @brief Sobrecarga del operador de igualdad. Para poder comprobar si dos ingredientes son iguales
  * @param original Objeto de la clase ingrediente con el que queremos comprobar la igualdad. No se modifica, pero no se pasa constante
  * @return Devuelve si el ingrediente pasado como argumento es igual o no al que llama al metodo	
  */ 
		bool operator== (Ingrediente &original) const;
};
#endif
			
			
  
