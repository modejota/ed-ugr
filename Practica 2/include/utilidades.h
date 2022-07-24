/**
  * @file utilidades.h
  * @brief Fichero cabecera de utilidades. Se definen funciones utiles para tratar con el TDA Ingredientes.
  *
  * @author Jose Alberto Gomez Garcia
  * @author Jesus Navarro Merino
  * @date Octubre 2019
  *
  */

#ifndef _UTILIDADES_H
#define _UTILIDADES_H

#include "ingredientes.h"
#include "ingrediente.h"
#include "VD.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;


/**
  * @brief Muestra un mensaje de adevertencia si no se ha introducido el numero correcto de parametros, tras lo cual cierra el programa.
  */  
		void MuestraParametros(); 	

/**
  * @brief Muestra las estadisicas de los nutrientes del conjunto de Ingredientes
  * @param conjunto Objeto de la clase Ingredientes del que se desean obtener las estadisticas
  * @param tipo Tipo de alimento del que se desean obtener las estadisticas
  */    
		void mostrarEstadisticas(Ingredientes conjunto, string tipo);		
		
/**
  * @brief Muestra los tipos de alimentos que hay en el conjunto dado
  * @param conjunto Objeto de la clase Ingredientes del cual queremos saber los tipos de alimentos que contiene
  */ 	
		void muestraTipos(Ingredientes conjunto);							

/**
  * @brief Halla las medias y desviaciones tipicas de los nutrientes de un conjunto de alimentos
  * @param *media Vector donde guardaremos las medias de los nutrientes del conjunto de ingredientes
  * @param *desviacion_tipica Vector donde guardaremos las desviaciones tipicas de los nutrientes del conjunto de ingredientes
  */ 	
		void MediaDesviacion(Ingredientes conjunto, float * media, float * desviacion_tipica);

/**
  * @brief Halla los alimentos con mas nutrientes de cada tipo y el valor de los mismos
  * @param *mayor Vector donde guardaremos el mayor valor de cada tipo de nutriente del conjunto de ingredientes
  * @param *nombre_mayor Vector donde guardaremos el nombre de los elementos con mas nutrientes de cada tipo del conjunto de ingredientes
  * @pre conjunto ha de estar compuesto por ingredientes de un unico tipo. Dada la especificacion del problema y los calculos que se nos piden
  */ 
		void CalcularMayor(Ingredientes conjunto, float * mayor, string * nombre_mayor);
		
/**
  * @brief Halla los alimentos con menos nutrientes de cada tipo y el valor de los mismos
  * @param *menor Vector donde guardaremos el menor valor de cada tipo de nutriente del conjunto de ingredientes
  * @param *nombre_menor Vector donde guardaremos el nombre de los elementos con menos nutrientes de cada tipo del conjunto de ingredientes
  * @pre conjunto ha de estar compuesto por ingredientes de un unico tipo. Dada la especificacion del problema y los calculos que se nos piden
  */ 
		void CalcularMenor(Ingredientes conjunto, float * menor, string * nombre_menor);

#endif
