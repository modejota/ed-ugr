#include "ingredientes.h"
#include "ingrediente.h"
#include "VD.h"
#include "utilidades.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {

  //Comprobamos que el numero de argumentos (2) es el correcto.
  if (argc!=3){
	  MuestraParametros();
	  return 0;
	}
   	   
  string fichero = argv[1];   
  string tipo = argv[2];
  
   //Abrimos el archivo, o por lo menos lo intentamos.
   ifstream f(fichero);
   if (!f){
    cout <<" No se pudo abrir el fichero " << fichero <<endl;
    return 0;
   }
   
   //Quitamos la primera linea del fichero, donde viene el formato en el que estan los datos.
   string linea;
   getline(f,linea);
   
   //Creamos un conjunto de Ingredientes y cargamos en él los datos del fichero.
   Ingredientes introducidos;
   f >> introducidos;
 
   //Mostramos los tipos de alimentos que hay presentes en nuestro conjunto de ingredientes	
   muestraTipos(introducidos);
   cout<<"\n Pulsa una tecla para continuar...."<<endl;
   cin.get();
   	

   bool existe = introducidos.existeTipo(tipo);
   if(!existe) {
	cout << "El tipo de alimento introducido no se encuentra entre nuestros ingredientes, por tanto, no existen alimentos de dicho tipo ni estadisticas que mostrar " << endl;
	exit(1);
    }

   //Creamos un conjunto de ingredientes para almacenar todos los del tipo que se nos pide
   //Mostramos la informacion de todos los alimentos del tipo que se nos ha especificado.
   cout << "Los ingredientes de tipo " << tipo << " son: " << endl;
   Ingredientes tipo_introducido;
   tipo_introducido = introducidos.getIngredienteTipo(tipo);
   cout << tipo_introducido;
   cout << endl;
   //Mostramos las estadisticas de dicho tipo de alimentos
   mostrarEstadisticas(tipo_introducido, tipo);
   
return 0;
}


	
	
