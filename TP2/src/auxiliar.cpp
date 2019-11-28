/*
 * auxiliar.cpp
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
 */

#include <string>

using namespace std;

double stringADouble(string cadena) {
	int posicionInicial = 0;
	int signo = 1;
	unsigned long posicionDecimal = 0;
	double numero = 0;
	char caracter;
	bool valido = true;

	/* si el string comienza con '-' es un numero negativo */
	if (cadena.at(0) == '-') {
		signo = -1;
		posicionInicial++;
	}

	for (unsigned int i = posicionInicial; i < cadena.size() && valido; i++) {
		caracter = cadena.at(i);

		if (caracter == '.') {
			/* se encontro un punto decimal */
			posicionDecimal = 1;
		} else if (caracter < '0' || caracter > '9') {
			valido = false;
		} else {
			// se convierte el caracter actual a numero restando la posicion del '0' en la tabla ASCII
			numero = numero * 10 + (caracter - '0');

			// se incrementa la cantidad de posiciones decimales
			posicionDecimal *= 10;
		}
	}

	// se devuelve el numero real teniendo en cuenta el signo y los decimales encontrados,
	// o 0 si hay un caracter invalido
	return (valido) ? numero * signo / ((posicionDecimal != 0) ? posicionDecimal : 1) : 0;
}

