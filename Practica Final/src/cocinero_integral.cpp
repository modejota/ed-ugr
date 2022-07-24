#include "recetas.h"
#include "ingredientes.h"
#include "acciones.h"
#include <iostream>
#include <fstream>

using namespace std;


/*
	El programa recibe 4 argumentos: 
		-El fichero de acciones.
		-El fichero de recetas. 
		-El fichero de ingredientes.
		-Un directorio con los ficheros de instrucciones para cada receta.
	
	La llamada sería:
		bin/cocinero_integral datos/Acciones.txt datos/recetas.txt datos/ingredientes.txt datos/instrucciones/
*/
int main (int argc, char ** argv){
	if (argc != 5){
		cerr << "Numero de argumentos erroneos." << endl;
		cerr << "Prueba con esta sintaxis:" << endl;
		cerr << argv[0] << " <fichero acciones> <fichero recetas> <fichero ingredientes> <directorio de ficheros instrucciones>" << endl;
		
		exit (-1);
	}
	
	ifstream f_acc, f_ing;
	
	f_acc.open(argv[1]); f_ing.open(argv[3]);
	
	//Comprobamos que se hayan abierto los ficheros.
	if (!f_acc){
		cerr << "Error abriendo el fichero " << argv[1] << endl;
		exit(-2);
	}
	if (!f_ing){
		cerr << "Error abriendo el fichero " << argv[3] << endl;
		exit(-3);
	}
	
	
	//Leemos las acciones, los ingredientes y las recetas.
	acciones acciones; Ingredientes ingredientes; recetas recetas;

	f_acc >> acciones;
	f_acc.close();
	
	f_ing >> ingredientes;
	f_ing.close();

	//Seteamos las acciones 
	instrucciones::setAcciones(&acciones);

	//Cargamos las recetas y las instrucciones de cada receta
	if(!recetas.CargarRecetas(argv[2],argv[4])){
		cerr << "Error al cargar las recetas";
		exit(-4);
	}

	//Calculamos los valores nutricionales de cada una de las recetas.
	recetas.setNutricion(ingredientes);
	

	cout << endl << FCYN(BOLD("Cocinero Integral")) << endl;

	//Mostramos la información resumida de todas las recetas (codigo, nombre y plato).
	cout << "Se mostraran ahora todas las recetas" << endl << endl;
	cout<<"Pulse una tecla para continuar"<<endl;
	cin.get();
	
	recetas.informacionResumidaRecetas(cout);
	
	//Mostramos la información completa de una receta.
	cout<< endl << "Pulse una tecla para continuar"<<endl;
	cin.get();
	
	string codigo;
	
	cout << endl << FGRN(BOLD("Introduce el codigo de la receta que quieres ver:")) << endl;
	cin >> codigo;
	
	//Si lo que introducen no es un codigo de alguna receta que tengamos, lo pedimos de nuevo
	while (!recetas.comprobarCodigo(codigo)){
		cout << endl << "No existe ninguna receta con el codigo " << codigo << endl;
		cout << endl << "Introduce el codigo de la receta que quieres ver" << endl;
		cin >> codigo;
	}
	
	cout << endl << endl;
	//Mostramos la receta con el codigo introducido
	cout << recetas[codigo];
	
	
	//Vamos a comenzar el proceso de fusion	
	string codigo1, codigo2;
	
	cout << endl << FCYN(BOLD("Procedemos ahora a fusionar 2 recetas.")) << endl << endl;
	
	//Pedimos al usuario el codigo de las recetas
	cout << FGRN(BOLD("Introduce la primera receta a fusionar:")) << endl;
	cin >> codigo1;
	while (!recetas.comprobarCodigo(codigo1)){
		cout << endl << "No existe ninguna receta con el codigo " << codigo1 << endl;
		cout << endl << "Introduce la primera receta a fusionar:" << endl;
		cin >> codigo1;
	}
	
	cout << endl << FGRN(BOLD("Introduce la segunda receta a fusionar:")) << endl;
	cin >> codigo2;
	while (!recetas.comprobarCodigo(codigo2)){
		cout << endl << "No existe ninguna receta con el codigo " << codigo2 << endl;
		cout << endl << "Introduce la segunda receta a fusionar:" << endl;
		cin >> codigo2;
	}
	
	//Mostramos ambas receras antes de la fusion
	cout << FCYN(BOLD("\nLas 2 recetas a fusionar son: \n")); 
	recetas[codigo1].informacionResumidaReceta(cout); 
	recetas[codigo2].informacionResumidaReceta(cout); 
	cout << endl;
	
	receta fusion;

	//Fusionamos las recetas y lo asignamos a fusion
	fusion = recetas[codigo1].fusionarReceta(recetas[codigo2]);
	//Mostramos la receta fusion
	cout << FCYN(BOLD("La fusion de ambas recetas es:")) << endl;
	cout << fusion;
}
	
	
