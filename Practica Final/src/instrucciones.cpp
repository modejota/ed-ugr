#include "instrucciones.h"
#include "color.h"
#include <sstream>
#include <string>
#include <stack>

//Para inicializar el puntero del objeto de clase
acciones * instrucciones::acc = NULL;

//Constructor sin parámetros.
instrucciones::instrucciones()
	:datos(){}


//Constructor pasandole un arbol
instrucciones::instrucciones(ArbolBinario<string> &AB) 
	:datos(AB){}


//Constructor con solo la raiz.
instrucciones::instrucciones(string raiz)
	:datos(raiz){}


//Constructor de copia.
instrucciones::instrucciones(const instrucciones & otro)
	:datos(otro.datos){}


//Get Acciones.
acciones * instrucciones::getAcciones(){
	return acc;
}


//Set Acciones.
void instrucciones::setAcciones(acciones * acciones){
	instrucciones::acc = acciones;
}


//Consultor de datos.
ArbolBinario<string> instrucciones::getDatos(){
	return datos;
}


//Fusionar dos instrucciones.
instrucciones instrucciones::fusionarInstrucciones(instrucciones & otra){
	ArbolBinario<string> nuevo_arbol("Acompañar");

	nuevo_arbol.Insertar_Hi(nuevo_arbol.getRaiz(), datos);
	nuevo_arbol.Insertar_Hd(nuevo_arbol.getRaiz(), otra.datos);
	
	instrucciones nuevas_inst(nuevo_arbol);

	return nuevas_inst;
}	


//Operador de entrada.
istream & operator >>(istream & is, instrucciones & Instr){
	stack<ArbolBinario<string>> pila;
	string aux;

	while (getline(is,aux)){
		//Si ha leido una linea que tenga algo (es decir, que no sea vacia), hacemos todo el algoritmo
		//Si es vacia, simplemente no hacemos nada, y al final, montará el arbol resultado con las lineas que sí tenian algo
		if (aux.length() > 1){

			//Con esto quitamos los posibles espacios en blanco que pudiera tener cada linea del txt 
			//(si hubiera: Cortar Lechuga' ' me meteria como nombre de ingrediente: "Lechuga' '" y no queremos eso)
			while (aux[aux.size()-1]==' ')
        		aux.pop_back();

			aux += ";";

			//Usamos flujos de string
			istringstream cadena (aux);

			string accion, ing1, ing2;
			unsigned char ariedad;
		
			cadena >> accion;
			//Esto es principalmente para las acciones de "Mezclar" y "Add" que estén solas. Si no pusieramos esto, se quedarian
			//como "Mezclar;" y "Add;" y no queremos eso
			if(accion[accion.size()-1] == ';')
				accion.pop_back();

			//Comprobar si hay un primer ingrediente.
			if (!getline(cadena, ing1, ';'))
				ing1 = "null";

			//Quitamos el espacio que se mete al principio junto al ing1 si lo hubiese.

			//Luego simplemente lo leemos con el espacio y luego lo quitamos 
			if(ing1[0] == ' ')
				ing1.erase(ing1.begin());	

			// Comprobar si hay un segundo ingrediente.
			if (!getline(cadena, ing2, ';'))
				ing2 = "null";

			ariedad = (*(Instr.getAcciones()))[accion];
		
			ArbolBinario<string> nuevo(accion);
		
			if(ariedad == '1'){
				
				if (ing1 != "null"){
					//Insertamos el ingrediente como hijo a la izquierda.
					nuevo.Insertar_Hi (nuevo.getRaiz(), ing1);
				}
				else{
					//Extraemos (y eliminamos) el ultimo arbol introducido en la pila, lo insertarmos como hijo a la izquierda
					ArbolBinario<string> aux_accion = pila.top();
					pila.pop();
			
					nuevo.Insertar_Hi (nuevo.getRaiz(), aux_accion);
				}

				pila.push(nuevo);
			}

			if(ariedad == '2'){
				/* Este switch lo hacemos porque la accion Add tiene un tratamiento distinto:
				//		Opcion 1. -Si Add aparece (en el txt) con 1 solo ingrediente, en vez de ponerlo a la izquierda y 
				//		           coger el hijo derecha de la pila; tenemos que ponerlo a la derecha, y coger como hijo izq
				//				   el que este en la pila.
				//		 		   Esto es necesario (o al menos no vemos otra alternativa), porque cuando estemos usando el
				//				   operator de salida de instrucciones (usando el postorden), no saldrán bien los ingredientes.
				//      
				//		Opcion 2. -Si Add aparece (en el txt) sin ningun ingrediente, se cogeran ambos de la pila: el top
				//				   será el Hd, y el top siguiente será el Hi.
				//				   En este caso no se da el problema de la Opcion 1
				//      
				//		Opcion 3. -Y si Add saliera con 2 ingredientes, tampoco habria problema, se mete el primero a la 
				//				   izq, el segundo a la derecha y ya (de todas formas, en los txt proporcionados 
				//				   como material no se da este caso)
				*/
				if(accion=="Add"){
					//Opcion 3
					if(ing1 != "null" && ing2 != "null"){
						nuevo.Insertar_Hi(nuevo.getRaiz(),ing1);
						nuevo.Insertar_Hd(nuevo.getRaiz(),ing2);
					}
					//Opcion 1 u Opcion 2
					else{

						//Opcion 1
						if(ing1 != "null"){
							nuevo.Insertar_Hd(nuevo.getRaiz(),ing1);

							ArbolBinario<string> aux_arbol=pila.top();
							pila.pop();
							nuevo.Insertar_Hi(nuevo.getRaiz(),aux_arbol);
						}
						//Opcion 2
						//Si el ing1 no está, el ing2 tampoco. Por tanto aunque este else engloba la posibilidad de que
						//ing1=="null" && ing2!="null", eso no va a ocurrir nunca. Nos curamos en salud.
						else{
							ArbolBinario<string> aux_arbol=pila.top();
							pila.pop();
							nuevo.Insertar_Hd(nuevo.getRaiz(),aux_arbol);

							aux_arbol=pila.top();
							pila.pop();
							nuevo.Insertar_Hi(nuevo.getRaiz(),aux_arbol);
						}
					}
					pila.push(nuevo);
				}

					/* Explicamos ahora las opciones de mezclar:
					//	Opcion 1. -Si Mezclar aparece solo (en el txt), cogemos el top como el Hd, y el siguiente top como Hi
					//
					//  Opcion 2. -Si Mezclar tiene ambos ingredientes, ponemos el ing1 como Hi, y el ing2 como Hd
					//			   (aunque este caso no se da en los txt)
					//
					*/

				//Si no es "Add" será "Mezclar" (porque "Acompañar" no nos lo vamos a encontrar en un txt)
				else{
					//Opcion 2
					if (ing1 != "null" && ing2 != "null"){
						nuevo.Insertar_Hi(nuevo.getRaiz(),ing1);
						nuevo.Insertar_Hd(nuevo.getRaiz(),ing2);
					}

					//Opcion 1
					//Basandonos en los ficheros que tenemos y la explicacion, suponemos que si no están ambos ingredientes no está ninguno
					else{
						ArbolBinario<string> aux_arbol = pila.top();
						pila.pop();
						nuevo.Insertar_Hd(nuevo.getRaiz(), aux_arbol);

						aux_arbol=pila.top();
						pila.pop();
						nuevo.Insertar_Hi(nuevo.getRaiz(),aux_arbol);
					}

					pila.push(nuevo);
				}
			}
		}
	}

	//Una vez tenemos montado el arbol final, sera el unico almacenado en la pila.
	//Lo asignamos al atributo y acabamos la carga del arbol.
	Instr.datos=pila.top();
	return is;
}


ostream & operator <<(ostream &os, const instrucciones &Instr){
	os << UNDL("Pasos a seguir:") << endl << endl;

	ArbolBinario<string>::postorden_iterador it=Instr.datos.beginpostorden();

	string ing1="null",ing2="null", accion, aux;

	for(it=Instr.datos.beginpostorden(); it!=Instr.datos.endpostorden(); ++it){
		aux=(*it);

		//Si es 1, es porque en donde está ahora mismo el iterador es una accion. La mostramos por el flujo y mostramos lo que
		//tuvieramos guardado en las variables ing1 o ing2
		if(  ((*(Instr.getAcciones())).count(aux)) == 1){
			os << "\t" << aux << "\t";
			if(ing1 != "null"){
				os << ing1;
				ing1="null";
			}
			if(ing2 != "null"){
				os << ing2;
				ing2="null";
			}
			os << endl;
		}

		else{
			if(ing1 == "null"){
				ing1=aux;
			}
			else{
				ing2=aux;
			}
		}
	}

	return os;
}