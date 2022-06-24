/*
 * pantalla.cpp
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
 */

#include <iostream>
#include "menu.h"
#include "coordenadas.h"
#include "auxiliar.h"

using namespace std;

void Menu::mostrarMenuPrincipal() {
	cout << "1 - Nuevo camino" << endl;
	cout << "2 - Salir" << endl;
	cout << "Cambio" << endl;
}

int Menu::pedirOpcion(int maximo) {
	int opcion = 0;
	while (opcion < 1 || opcion > maximo) {
		cout << "Seleccione una opcion (1 - " << maximo << "): ";
		while (!(cin >> opcion)) {
			// si se ingreso un tipo de dato invalido se vuelve a pedir
			cin.clear();
			cin.ignore();
		}
	}
	return opcion;
}

Coordenadas Menu::pedirCoordenadas(string texto, Coordenadas& minimo, Coordenadas& maximo) {
	string latitud, longitud;
	double doubleLatitud, doubleLongitud;

	cout << endl << "Ingrese coordenadas del " << texto << endl;
	do {
		cout << "Latitud (de " << minimo.getLatitud() << " a " << maximo.getLatitud() << "): ";
		cin >> latitud;
		doubleLatitud = stringADouble(latitud);
		if (doubleLatitud < minimo.getLatitud() || doubleLatitud > maximo.getLatitud()) {
			cout << "Fuera de rango, intente de nuevo." << endl;
		}
	} while (doubleLatitud < minimo.getLatitud() || doubleLatitud > maximo.getLatitud());
	do {
		cout << "Longitud (de " << minimo.getLongitud() << " a " << maximo.getLongitud() << "): ";
		cin >> longitud;
		doubleLongitud = stringADouble(longitud);
	} while (doubleLongitud < minimo.getLongitud() || doubleLongitud > maximo.getLongitud());

	return Coordenadas(doubleLongitud, doubleLatitud);
}

int Menu::pedirDistancia() {
	int metros = 0;
	while (metros <= 0) {
		cout << "Ingrese los metros que esta dispuesto a caminar entre cada conexion: ";
		while (!(cin >> metros)) {
			// si se ingreso un tipo de dato invalido se vuelve a pedir
			cin.clear();
			cin.ignore();
		}
		if (metros <= 0) {
			cout << "Por favor ingrese un numero mayor a 0." << endl;
		}
	}

	return metros;
}

bool Menu::pedirAuto() {
	bool respuesta = false;
	cout << "Desea usar su auto?" << endl;
	mostrarSiNo();
	int opcionMenu = pedirOpcion(2);
	if (opcionMenu == 1) {
		respuesta = true;
	}

	return respuesta;
}

void Menu::mostrarSiNo() {
	cout << "1 - Si" << endl;
	cout << "2 - No" << endl;
}




