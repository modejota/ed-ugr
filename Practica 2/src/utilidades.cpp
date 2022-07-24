#include "ingredientes.h"
#include "ingrediente.h"
#include "VD.h"
#include "utilidades.h"
#include <iostream>
#include <fstream>


void MuestraParametros(){
	
	cout << "1.- Dime el nombre del fichero con los ingredientes." <<endl;
	cout << "2.- Dime el nombre del tipo de alimento que quieres." << endl;
	exit(-1);
}

void mostrarEstadisticas(Ingredientes conjunto, string tipo) {
	cout << "ESTADISTICAS___________________" << endl;
	cout << "Tipo de alimento: " << tipo << endl;
	cout << "Promedio +- Desviacion " << endl << endl;
	
	//Creamos dos vectores donde almacenar los resultados de los calculos
	float media[5],desviacion[5];
	
	MediaDesviacion(conjunto, media, desviacion);
	
	cout << "Calorias " << "\t" << "Hidratos de Carbono " << "\t" << "Proteinas " << "\t" << "Grasas " << "\t" << "Fibra " << endl;
	cout << media[0] << " +- " << desviacion[0] << "\t" << media[1] << " +- " << desviacion[1] << "\t" 
	     << media[2] << " +- " << desviacion[2] << "\t" << media[3] << " +- " << desviacion[3] << "\t" 
	     << media[4] << " +- " << desviacion[4] << endl << endl; 
	
	//Creamos otras dos vectores para almacenar los resultados de los calculos
	float mayor[5];
	string nombre_mayor[5];
	
	CalcularMayor(conjunto, mayor, nombre_mayor);
	
	cout << "MAXIMOS VALORES " << endl << endl;

	cout << "Calorias (Alimento) " << "\t" << "Hidratos de Carbono (Alimento) " << "\t" 
	     << "Proteinas (Alimento) " << "\t" << "Grasas (Alimento) " << "\t" << "Fibra (Alimento)" << endl;

	cout << mayor[0] << "  " << nombre_mayor[0] << "\t" << mayor[1] << "  " << nombre_mayor[1] << "\t" 
	     << mayor[2] << "  " << nombre_mayor[2] << "\t" << mayor[3] << "  " << nombre_mayor[3] << "\t" 
	     << mayor[4] << "  " << nombre_mayor[4] << endl << endl;
	
	//Creamos otras dos vectores para almacenar los resultados de los calculos
	float menor[5];
	string nombre_menor[5];
	
	CalcularMenor(conjunto, menor, nombre_menor);
		
	cout << "MINIMOS VALORES " << endl << endl;

	cout << "Calorias (Alimento) " << "\t" << "Hidratos de Carbono (Alimento) " << "\t" 
	     << "Proteinas (Alimento) " << "\t" << "Grasas (Alimento) " << "\t" << "Fibra (Alimento)" << endl;

	cout << menor[0] << "  " << nombre_menor[0] << "\t" << menor[1] << "  " << nombre_menor[1] << "\t" 
	     << menor[2] << "  " << nombre_menor[2] << "\t" << menor[3] << "  " << nombre_menor[3] << "\t" 
	     << menor[4] << "  " << nombre_menor[4] << endl << endl;
	
}

void muestraTipos(Ingredientes conjunto) {
	//Creamos un vector dinamico donde guardar todos los nombres de los tipos.
	//Llamamos al metodo getTipos de la clase Ingredientes.
	VD<string> tipos=conjunto.getTipos();
	
	cout << "Los tipos de alimentos son: "<< endl;

	//Mostramos el contenido del vector, es decir, todos los tipos de alimentos
	for (int i=0; i<tipos.size(); ++i){
		cout << tipos[i] << endl;
	}	
}

//Se calculan la media y desviacion tipica para cada tipo de nutriente, se guardan en vectores ordenados por el orden en el que posteriormente se mostraran
void MediaDesviacion(Ingredientes conjunto, float *media, float *desviacion){
	int tamanio = conjunto.size();
	float media_calorias=0, media_hidratos=0, media_proteinas=0, media_grasas=0, media_fibra=0;
	float desviacion_calorias=0, desviacion_hidratos=0, desviacion_proteinas=0, desviacion_grasas=0, desviacion_fibras=0;
	for (int i=0;i<tamanio;i++){
		media_calorias += conjunto[i].getCalorias();
		media_hidratos += conjunto[i].getHc();
		media_proteinas += conjunto[i].getProteinas();
		media_grasas += conjunto[i].getGrasas();
		media_fibra += conjunto[i].getFibra();
	}
	
	media[0]=media_calorias/tamanio;
	media[1]=media_hidratos/tamanio;
	media[2]=media_proteinas/tamanio;
	media[3]=media_grasas/tamanio;
	media[4]=media_fibra/tamanio;
	
	for(int i=0;i<tamanio;i++){
		desviacion_calorias += ((conjunto[i].getCalorias() - media[0])*(conjunto[i].getCalorias() - media[0]));
		desviacion_hidratos += ((conjunto[i].getHc() - media[1])*(conjunto[i].getHc() - media[1]));
		desviacion_proteinas += ((conjunto[i].getProteinas() - media[2])*(conjunto[i].getProteinas() - media[2]));
		desviacion_grasas += ((conjunto[i].getGrasas() - media[3])*(conjunto[i].getGrasas() - media[3]));
		desviacion_fibras += ((conjunto[i].getFibra() - media[4])*(conjunto[i].getFibra() - media[4]));
	}
	
	desviacion[0] = sqrt((1.0/tamanio)*desviacion_calorias);
	desviacion[1] = sqrt((1.0/tamanio)*desviacion_hidratos);
	desviacion[2] = sqrt((1.0/tamanio)*desviacion_proteinas);
	desviacion[3] = sqrt((1.0/tamanio)*desviacion_grasas);
	desviacion[4] = sqrt((1.0/tamanio)*desviacion_fibras);
}

void CalcularMayor(Ingredientes conjunto, float *valor, string *nombre){
	
	for (int i=0;i<conjunto.size();i++){
		if (valor[0] < conjunto[i].getCalorias() || i == 0){
			valor[0] = conjunto[i].getCalorias();
			nombre[0] = conjunto[i].getNombre();
		}
		if (valor[1] < conjunto[i].getHc() || i == 0){
			valor[1] = conjunto[i].getHc();
			nombre[1] = conjunto[i].getNombre();
		}
		if (valor[2] < conjunto[i].getProteinas() || i == 0){
			valor[2] = conjunto[i].getProteinas();
			nombre[2] = conjunto[i].getNombre();
		}
		if (valor[3] < conjunto[i].getGrasas() || i == 0){
			valor[3] = conjunto[i].getGrasas();
			nombre[3] = conjunto[i].getNombre();
		}
		if (valor[4] < conjunto[i].getFibra() || i == 0){
			valor[4] = conjunto[i].getFibra();
			nombre[4] = conjunto[i].getNombre();
		}
	}
}

void CalcularMenor(Ingredientes conjunto, float *valor, string *nombre){
	
	for (int i=0; i<conjunto.size();i++){
		if (valor[0] > conjunto[i].getCalorias() || i == 0){
			valor[0] = conjunto[i].getCalorias();
			nombre[0] = conjunto[i].getNombre();
		}

		if (valor[1] > conjunto[i].getHc() || i == 0){
			valor[1] = conjunto[i].getHc();
			nombre[1] = conjunto[i].getNombre();
		}

		if (valor[2] > conjunto[i].getProteinas() ||i == 0){
			valor[2] = conjunto[i].getProteinas();
			nombre[2] = conjunto[i].getNombre();
		}
				
		if (valor[3] > conjunto[i].getGrasas() || i == 0){
			valor[3] = conjunto[i].getGrasas();
			nombre[3] = conjunto[i].getNombre();
		}
	
		if (valor[4] > conjunto[i].getFibra() || i == 0){
			valor[4] = conjunto[i].getFibra();
			nombre[4] = conjunto[i].getNombre();
		}			
	}
}
