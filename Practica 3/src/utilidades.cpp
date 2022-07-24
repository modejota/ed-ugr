#include "ingredientes.h"
#include "ingrediente.h"
#include "utilidades.h"
#include "recetas.h"
#include <iostream>
#include <fstream>
#include <map>
#include <utility>


void mostrarValoresNutricionales(recetas &Rs){
	recetas::iterator it;
	for(it=Rs.begin();it!=Rs.end();++it){
		cout << "Valores Nutricionales de la receta " << *it;
		cout << "Calorias " << (*it).getCalorias() << "\tHidratos de Carb. " << (*it).getHc() << "\tProteinas " << (*it).getProteinas()
		     << "\tGrasas " << (*it).getGrasas() << "\tFibra " << (*it).getFibra() << endl << endl << endl; 
	}
}

void ordenarPorRazon(recetas &Rs,map<float,receta> &recetas_por_razon){
	float razon, aux_proteinas, aux_hc;
	recetas::iterator it;
	for(it=Rs.begin();it!=Rs.end();++it){
		aux_proteinas=(*it).getProteinas();
		aux_hc=(*it).getHc();
		razon=aux_proteinas/aux_hc;

		//Como es un map, ordena automaticamente por la "key" que en este caso es la razon
		recetas_por_razon.insert(pair<float,receta>(razon,(*it)));
	}
}

void escogerRecetas(map<float,receta> &recetas_por_razon, recetas &sub_rec, float tope_cal,float &cal_totales, float &prot_totales,float &razon_suma){
	string aux_codigo;
	float cal_acumuladas=0.0;
	map<float,receta>::iterator it;
    // Vamos cogiendo el codigo de cada receta del map de "recetas_por_razon", para luego meterselo al sub_rec.
    // Esto lo haremos para todas las recetas: la que supere el tope de calorias si la metieramos, no la metemos; si no lo supera, la metemos
	// Empiezo desde el final, porq el map lo ordena automaticamente de menor a mayor, y queremos que la razon total acumulada de nuestras recetas
	// escogidas sea la mas grande posible (por tanto empezamos a escoger recetas por el final). El algoritmo es voraz, por lo que no es óptimo
	// (habría que usar programación dinámica para optimizarlo la cual se pospone al siguiente cuatrimestre)
	for(it=(--recetas_por_razon.end()); it!=(--recetas_por_razon.begin()); --it){
		aux_codigo=(it->second).getCode();
		cal_acumuladas+=(it->second).getCalorias();
		

		if(cal_acumuladas<tope_cal){
			razon_suma+=(it->first);
			cal_totales+=(it->second).getCalorias();
			prot_totales+=(it->second).getProteinas();
			pair<string,receta> pair_aux(aux_codigo,it->second);
			sub_rec.insertarElemento(pair_aux);
		}
		else{ //Si no he metido esa receta porq se pasa del tope, restauramos "cal_acumuladas"
			cal_acumuladas-=(it->second).getCalorias();
		}
	}
}
