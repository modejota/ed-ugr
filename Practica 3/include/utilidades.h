/**
  * @file utilidades.h
  * @brief Fichero cabecera de utilidades. Se definen funciones utiles para tratar con el TDA Recetas.
  *
  * @author Jose Alberto Gomez Garcia
  * @author Jesus Navarro Merino
  * @date Noviembre 2019
  *
  */

#ifndef _UTILIDADES_H
#define _UTILIDADES_H

#include "ingredientes.h"
#include "ingrediente.h"
#include "recetas.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
using namespace std;

/**
  * @brief Muestra los valores nutricionales de todas las recetas del map de Recetas 
  * @param Rs conjunto de Recetas del que se quieren mostrar los valores nutricionales
  * @pre El conjunto de recetas no debe estar vacio
  */
    void mostrarValoresNutricionales(recetas &Rs);
    
/**
  * @brief Carga en un nuevo map las Recetas ordenadas de mayor a menor en funci�n de la razon proteinas/(hidratos de carbono)
  * @param Rs conjunto de recetas con el que debemos tratar.
  * @param recetas_por_razon Map con las recetas del conjunto Rs ordendas de mayor a menor por la razon proteinas/(hidratos de carbono)
  * @pre Rs debe estar cargado con un conjunto de Recetas no nulo, mientras que el recetas_por_razon debe estar vacio
  */
    void ordenarPorRazon(recetas &Rs, map<float,receta> &recetas_por_razon);
    
/** @brief Escoge las recetas que maximizan la razon (hidratos de carbono)/proteinas sin superar un determinado numero de calorias
  * @param recetas_por_razon Map con un conjunto de recetas ordenadas de mayor a menor por la razon proteinas/(hidratos de carbono)
  * @param sub_rec Conjunto de recetas donde cargaremos las recetas elegidas en el proceso de seleccion descrito anteriormente
  * @param tope_cal Valor maximo de calorias para el que deberemos maximizar la razon proteinas/(hidratos de carbono)
  * @param cal_totales Calorias totales que aportan el conjunto de recetas elegido
  * @param prot_totales Proteinas totales que aporta el conjunto de recetas elegido
  * @param razon_suma Razon total obtenida en el proceso de seleccion
  * @pre recetas_por_razon debe estar vacio, al igual que sub_rec
  * @pre tope_cal debe tener un valor mayor a 0, cal_totales, prot_totales y razon_suma deben ser pasadas a la funcion tras ser inicializadas a 0
  */    
    void escogerRecetas(map<float,receta> &recetas_por_razon, recetas &sub_rec, float tope_cal,float &cal_totales,float &prot_totales,float &razon_suma);

#endif
