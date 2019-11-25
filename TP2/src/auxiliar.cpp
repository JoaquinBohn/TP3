/*
 * auxiliar.cpp
 *
 *      Autor: Cristian Kiper
 *      Padron: 100031
 */

#include <string>

using namespace std;

double stringADouble(string cadena) {
	int posicionInicial = 0;
	int signo = 1;
	unsigned long posicionDecimal = 0;
	double numero = 0;
	char caracter;

	// si el string comienza con '-' es un numero negativo
	if (cadena.at(0) == '-') {
		signo = -1;
		posicionInicial++;
	}

	for (unsigned int i = posicionInicial; i < cadena.size(); i++) {
		caracter = cadena.at(i);

		if (caracter == '.') {
			// se encontro un punto decimal
			posicionDecimal = 1;
		} else {
			// se convierte el caracter actual a numero restando la posicion del '0' en la tabla ASCII
			numero = numero * 10 + (caracter - '0');

			// se incrementa la cantidad de posiciones decimales
			posicionDecimal *= 10;
		}
	}

	// se devuelve el numero real teniendo en cuenta el signo y los decimales encontrados
	return numero * signo / posicionDecimal;
}

