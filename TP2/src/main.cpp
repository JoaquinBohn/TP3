/*
 * main.cpp
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
 */

#include "Lista.h"
#include "camino.h"
#include "transporte.h"
#include "menu.h"

using namespace std;

void armarCaminos(Transporte& transporte) {
	bool caminoGenerado;
	Coordenadas origen = Menu::pedirCoordenadas("origen", transporte.getMinimo(), transporte.getMaximo());
	Coordenadas destino = Menu::pedirCoordenadas("destino", transporte.getMinimo(), transporte.getMaximo());
	int distancia = Menu::pedirDistancia();
	bool conAuto = Menu::pedirAuto();
	Camino camino = Camino(transporte.getTransportes());
	cout << endl << "Armando caminos..." << endl << endl;
	caminoGenerado = camino.generarCaminos(origen, destino, distancia, conAuto);
	if (caminoGenerado) {
		camino.obtenerPrecio();
		camino.imprimirCamino();
	} else {
		cout << "No se pudo armar un camino." << endl << endl;
	}
}

int main() {
	Transporte transporte;
	try {
		transporte.cargarTransportes();
	} catch (string& mensaje) {
		cout << mensaje;
		exit(0);
	}

	Menu::mostrarMenuPrincipal();
	int opcionMenu = Menu::pedirOpcion(Menu::OPCION_SALIDA);
	while (opcionMenu != Menu::OPCION_SALIDA) {
		switch(opcionMenu) {
			case Menu::OPCION_CAMINO:
				armarCaminos(transporte);
				break;
		}

		Menu::mostrarMenuPrincipal();
		opcionMenu = Menu::pedirOpcion(Menu::OPCION_SALIDA);
	}

	return 0;
}


