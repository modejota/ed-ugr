/**
  * @file instrucciones.h
  * @brief Fichero cabecera del TDA Instrucciones
  *
  */


#ifndef _INSTRUCCIONES_H
#define _INSTRUCCIONES_H


#include "arbolbinario.h"
#include "acciones.h"
#include <iostream>
#include <string>

using namespace std;


/**
  * @brief TDA instrucciones
  *
  * Una instancia de la clase instrucciones recopila, de forma ordenada, todas las
  * acciones a realizar sobre un conjunto de ingredientes para cocinar una receta.
  * Además, aparte de almacenar esta secuencia de acciones, guarda también
  * un objeto de acciones que contiene todas las acciones y su ariedad.
  *
  * @author Jesús Navarro Merino
  * @author José Alberto Gómez García
  * @date Diciembre 2019
  */
class instrucciones{
	private:
/**
  * @page repInstrucciones Rep del TDA de Instrucciones.
  *
  * @section invInstrucciones Invariante de la representacion.
  *
  * Un objeto rep de Instrucciones contiene un arbol binario (no vacio) de acciones a
  * realizar sobre un conjunto de ingredientes (minimo 1) para cocinar una receta tal que:
  *  	- Los ingredientes son los nodos hoja.
  * 	- El resto de nodos son acciones a realizar:
  * 		* Sobre los ingredientes que se encuentran en el arbol binario como sus hijos.
  * 		* Sobre el resultado de alguna accion previa sobre dichos ingredientes.
  * 		* Sobre un ingrediente que se encuentra en el arbol binario como su hijo y el resultado de alguna accion previa sobre otros ingredientes.
  *
  */
		ArbolBinario<string> datos; /**<Arbol binario de strings con acciones e ingredientes>*/
		static acciones * acc; 		/**<Objeto de acciones estatico, que recoge todas las acciones junto con su ariedad>*/
	public:
		/**
		  * @brief Constructor por defecto sin parámetros de la clase instrucciones.
		  */
		instrucciones();

		/**
		  * @brief Constructor con parametros. Inicializa datos con el arbol binario que se pasa como parametro.
		  * @param AB Arbol binario de strings con acciones e ingredientes.
		  */
		instrucciones(ArbolBinario<string> &AB);
		
		
		/**
		  * @brief Constructor con parametros. Inicializa datos con el arbol binario cuya raiz pasamos como parametro
		  * @param raiz String con la etiqueta de la raiz.
		  */
		instrucciones (string raiz);
		
		
		/**
		  * @brief Constructor de copia de la clase instrucciones. Crea un arbol binario copia del pasado como parametro.
		  */
		instrucciones (const instrucciones & otro);
		
		
		/**
		  * @brief Consultor del objeto de clase acc (de tipo acciones).
		  * @return Devuelve el objeto de clase acc por referencia.
		  */
		static acciones * getAcciones ();
		
		
		/**
		  * @brief Modificador del objeto de clase acc (de tipo acciones).
		  * @param acciones Nuevo objeto de acciones.
		  */
		static void setAcciones(acciones * acciones);
		
		
		/**
		  * @brief Consultor del arbol binario de instrucciones.
		  */
		ArbolBinario<string> getDatos ();
		
		
		/**
		  * @brief Fusionar las instrucciones de dos recetas.
		  * @param otra Instrucciones de la segunda receta.
		  * @return Objeto instrucciones resultante de concatenar las instrucciones de ambas recetas y la accion "Acompañar".
		  */
		instrucciones fusionarInstrucciones(instrucciones & otra);
		
		
		/**
		  * @brief Operador de entrada. Dado un archivo, extrae todas las acciones e ingredientes hasta llegar al final de archivo y las introduce en orden en el arbol binario.
		  * @param is Flujo de entrada utilizado.
		  * @param Instr Objeto de la clase instrucciones donde se van a escribir los datos leidos del archivo.
		  * @return Devuelve el flujo de entrada utilizado, el que pasamos como parametro.
		  */
		friend istream & operator >> (istream & is, instrucciones & Instr);
		
		
		/**
		  * @brief Operador de salida. Carga la secuencia de instrucciones en el flujo de salida.
		  * @param os Flujo de salida utilizado
		  * @param Instr Objeto constante de la clase instrucciones que se desea cargar en el flujo.
		  * @return Devuelve el flujo de salida utilizado, el que pasamos como parametro.
		  */
		friend ostream & operator << (ostream & os, const instrucciones & Instr);
};

#endif
