#include "Lista.h"
#include "camino.h"
#include "transporte.h"
#include "menu.h"

using namespace std;

bool caminoEsNuevo(Lista<Camino*>& caminos, Camino*& camino) {
	bool caminoNuevo = true;
	caminos.iniciarCursor();
	while (caminoNuevo && caminos.avanzarCursor()) {
		Camino* caminoPrevio = caminos.obtenerCursor();
		if (caminoPrevio->esIgual(camino)) {
			caminoNuevo = false;
		}
	}

	return caminoNuevo;
}


void mostrarCaminos(Lista<Camino*>& caminos) {
	Camino* camino;
	caminos.iniciarCursor();
	while (caminos.avanzarCursor()) {
		camino = caminos.obtenerCursor();
		camino->imprimirCamino();
		delete camino;
	}
}

void armarCaminos(Transporte& transporte) {
	TipoEstacion tipos[] = {colectivo, subte, tren, metrobus, garaje};
	Lista<Camino*> caminos;
	Camino* camino;
	int unsigned cantidad;

	Coordenadas origen = Menu::pedirCoordenadas("origen", transporte.getMinimo(), transporte.getMaximo());
	Coordenadas destino = Menu::pedirCoordenadas("destino", transporte.getMinimo(), transporte.getMaximo());
	int distancia = Menu::pedirDistancia();
	bool conAuto = Menu::pedirAuto();
	if (conAuto) {
		cantidad = indefinido;
	} else {
		cantidad = garaje;
	}

	for (unsigned int i = 0; i < cantidad; i++) {
		for(unsigned int j=0; j<3; j++){
			camino = new Camino(transporte.getTransportes(), origen, destino, distancia, tipos[i], conAuto);

			if (caminoEsNuevo(caminos, camino)) {
				/*implementar caminoEsMasCorto*/
				if(caminoEsMasCorto(caminos, camino, tipos[i])){
					caminos.agregar(camino);
				}
			} else {
				delete camino;
			}
		}
	}

	mostrarCaminos(caminos);
}

int main() {
	Transporte transporte;
	try {
	transporte.cargarTransportes();
	} catch (std::string& mensaje) {
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

	cout << endl << "---- FIN ---" << endl;
	return 0;
}


