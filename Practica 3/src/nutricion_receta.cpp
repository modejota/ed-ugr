#include "receta.h"
#include "recetas.h"
#include "ingrediente.h"
#include "ingredientes.h"
#include "utilidades.h"
#include <fstream>
#include <cstdlib> //Para usar el strtof
#include <map>

using namespace std;
int main(int argc,char *argv[]){
    if (argc!=4){
        cout<<"Prueba con el formato: <Archivo de las recetas> <Archivo de los ingredientes> <Tope calorias>"<<endl;
        return 0;
    }

    string rec=argv[1];
    string ing=argv[2];
    float tope_cal=strtof(argv[3],NULL); //Convierte un string en float

    ifstream f_recetas(rec);
    if (!f_recetas){
	    cout << "No existe el fichero " << rec<< endl;
    }

    ifstream f_ingredientes(ing);
    if(!f_ingredientes){
        cout << "No existe el fichero " << ing << endl;
    }

    Ingredientes all_ingre;
    recetas rall;
    //Metemos todas las recetas y todos los ingredientes en cada objeto con los operadores
    f_recetas>>rall;
    f_ingredientes>>all_ingre;

    //En este metodo de recetas: vamos buscando los ingredientes de cada receta, comparandolos en nuestra "base de datos" de ingredientes, y vamos cogiendo sus valores nutricionales
    rall.obtenerNutrientes(all_ingre);

    //Mostramos por pantalla los valores nutricionales de las recetas con un determinado formato
    mostrarValoresNutricionales(rall);

	cout << endl << endl;

    map<float,receta> recetas_por_razon;

    //Ordenamos por razon las recetas y se quedan guardadas en el map "recetas_por_razon" cuya key sera la razon, y el valor asociado la receta
    ordenarPorRazon(rall,recetas_por_razon);

    //Aqui nos declaramos otra recetas, que sera nuestro subconjunto escogido
    recetas sub_rec;
    float cal_totales=0.0, prot_totales=0.0, razon_suma=0.0;
    //escogerRecetas me rellena "sub_rec" con las recetas escogidas en funcion de tope_cal. Me modifica tb "cal_totales" y "prot_totales"
    escogerRecetas(recetas_por_razon,sub_rec,tope_cal,cal_totales,prot_totales,razon_suma);

    cout << "EJEMPLO con " << tope_cal << " calorias que maximiza la razon proteina/hidratos" << endl;
    cout << "Las recetas escogidas son:" << endl;
    cout << sub_rec << endl;
    cout << "Calorias totales: " << cal_totales << "   Proteinas totales: " << prot_totales << "   Razon acumulada: " << razon_suma << endl;

}




