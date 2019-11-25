/*
 * pantalla.cpp
 *
 *      Autor: Cristian Kiper
 *      Padron: 100031
 */

#include <iostream>
#include "menu.h"
#include "coordenadas.h"

void Menu::mostrarMenuPrincipal() {
	std::cout << "1 - Nuevo camino" << std::endl;
	std::cout << "2 - Salir" << std::endl;
}

int Menu::pedirOpcion(int maximo) {
	int opcion = 0;
	while (opcion < 1 || opcion > maximo) {
		std::cout << "Seleccione una opcion (1 - " << maximo << "): ";
		while (!(std::cin >> opcion)) {
			// si se ingreso un tipo de dato invalido se vuelve a pedir
			std::cin.clear();
			std::cin.ignore();
		}
	}
	return opcion;
}

Coordenadas Menu::pedirCoordenadas(std::string texto, Coordenadas& minimo, Coordenadas& maximo) {
	double latitud, longitud;

	std::cout << std::endl << "Ingrese coordenadas del " << texto << std::endl;
	do {
		std::cout << "Latitud (de " << minimo.getLatitud() << " a " << maximo.getLatitud() << "): ";
		std::cin >> latitud;
	} while (latitud < minimo.getLatitud() || latitud > maximo.getLatitud());
	do {
		std::cout << "Longitud (de " << minimo.getLongitud() << " a " << maximo.getLongitud() << "): ";
		std::cin >> longitud;
	} while (longitud < minimo.getLongitud() || longitud > maximo.getLongitud());

	return Coordenadas(longitud, latitud);
}

int Menu::pedirDistancia() {
	int metros = 0;
	while (metros <= 0) {
		std::cout << "Ingrese los metros que esta dispuesto a caminar entre cada conexion: ";
		while (!(std::cin >> metros)) {
			// si se ingreso un tipo de dato invalido se vuelve a pedir
			std::cin.clear();
			std::cin.ignore();
		}
		if (metros <= 0) {
			std::cout << "Por favor ingrese un numero mayor a 0." << std::endl;
		}
	}

	return metros;
}

bool Menu::pedirAuto() {
	bool respuesta = false;
	std::cout << "Desea usar su auto?" << std::endl;
	mostrarSiNo();
	int opcionMenu = pedirOpcion(2);
	if (opcionMenu == 1) {
		respuesta = true;
	}

	return respuesta;
}

void Menu::mostrarSiNo() {
	std::cout << "1 - Si" << std::endl;
	std::cout << "2 - No" << std::endl;
}




