/*
 * pantalla.h
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
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

	/* pregunta al usuario si desea usar su auto, la respuesta
	 * se utiliza para determinar si se tienen en cuenta los garajes
	 */
	static bool pedirAuto();

	/**
	 * Pide por pantalla que se ingrese un numero de 1 a un maximo.
	 * Si el numero ingresado esta fuera de rango se lo vuelve a pedir.
	 *
	 * pre: maximo debe ser mayor a 1
	 * post: devuelve la opcion ingresada
	 */
	static int pedirOpcion(int maximo);

	/* pide por pantalla que se ingresen coordenades de latitud y longitud
	 *
	 * post: devuelve las coordenadas ingresada, validando que no esten
	 * por afuera de los limites de minimo y maximo
	 */
	static Coordenadas pedirCoordenadas(std::string texto, Coordenadas& minimo, Coordenadas& maximo);

	/* le pide al usuario que ingrese la cantidad de metros que esta dispuesto a caminar
	 *
	 * pre: el numero ingresado deber ser mayor que 0
	 * post: devuelve el numero ingresado
	 */
	static int pedirDistancia();
};

#endif /* MENU_H_ */
