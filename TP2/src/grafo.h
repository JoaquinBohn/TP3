/*
 * grafo.h
 *
 *  Created on: 25 nov. 2019
 *      Author: joaquin
 */

#ifndef GRAFO_H_
#define GRAFO_H_

#include "Nodo.h"
#include "arista.h"

template <typename T>
class Grafo{
private:
	Nodo<Coordenadas>* origen;
	Nodo<Coordenadas>* destino;
	Nodo<Estacion>* actual;
public:
	/*
	 * Precondicion: -
	 * Postcondicion: grafo vacio.
	 */
	Grafo();

	/*
	 * Precondicion: -
	 * Postcondicion: libera los recursos utilizados por el grafo.
	 */
	~Grafo();

	/*
	 * Precondicion: recibe un nodo no insertado previamente al grafo.
	 * Postcondicion: inserta el nodo en el grafo.
	 */
	void insertarNodo(Nodo<Estacion>);

	/*
	 * Precondicion: recibe una arista.
	 * Postcondicion: agrega la arista al grafo.
	 */
	void insertarArista(Arista);

	/*
	 * Precondicion: nodo esta en el grafo.
	 * Postcondicion: elimina el nodo y actualiza el grafo.
	*/
	void eliminarNodo(Nodo<Estacion>);

	/*
	 * Precondicion: arista esta en el grafo.
	 * Postcondicion: elimina la arista y actualiza el grafo.
	 * 				  En el caso de que al eliminar una arista queden nodos
	 * 				  sueltos, se lo apunta con el puntero actual.
	 */
	void eliminarArista(Arista);

	/*
	 * Precondicion: -
	 * Postcondicion: indica si el nodo esta en el grafo.
	 */
	bool existeNodo(Nodo<Estacion>);

	/*
	 * Precondicion: -
	 * Postcondicion: indica si la arista esta en el grado.
	 */
	bool existeArista(Arista);
};

template <typename T> Grafo<T>::Grafo(){
	this->origen = NULL;
	this->destino = NULL;
	this->actual = NULL;
}

template <typename T> Grafo<T>::~Grafo(){

}

template <typename T> Grafo<T>::




#endif /* GRAFO_H_ */
