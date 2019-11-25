/*
 * pantalla.h
 *
 *      Autor: Cristian Kiper
 *      Padron: 100031
 */

#ifndef MENU_H_
#define MENU_H_

#include <string>
#include "coordenadas.h"

class Menu {
private:
	/**
	 * Muestra un menu para preguntas de tipo "Si/No"
	 */
	static void mostrarSiNo();

public:

	/* la opcion del menu que se utiliza para empezar un nuevo camino */
	static const unsigned int OPCION_CAMINO = 1;

	/* la opcion del menu que se utiliza para terminar el programa */
	static const unsigned int OPCION_SALIDA = 2;

	/**
	 * Muestra el menu principal de la aplicacion.
	 */
	static void mostrarMenuPrincipal();



	/**
	 * Pide por pantalla que se ingrese un numero de 1 a un maximo.
	 * Si el numero ingresado esta fuera de rango se lo vuelve a pedir.
	 *
	 * @param maximo el numero maximo que puede ser ingresado.
	 * @return devuelve un entero indicando la opcion ingresada.
	 */
	static bool pedirAuto();

	static int pedirOpcion(int maximo);

	static Coordenadas pedirCoordenadas(std::string texto, Coordenadas& minimo, Coordenadas& maximo);

	static int pedirDistancia();
};

#endif /* MENU_H_ */
