/*
 * ruta.h
 *
 *  Created on: Oct 30, 2019
 *      Author: cristian
 */

#ifndef CAMINO_H_
#define CAMINO_H_

#include "Lista.h"
#include "recorrido.h"
#include "EasyBMP.h"

class Camino {
private:

	/* lista de recorridos para un mismo camino */
	Lista<Recorrido*>* camino;

	/* lista de medios de transporte a utilizar para armar un camino */
	Lista<Estacion*>* transportes;

	/* coordenadas del punto de partida del camino */
	Coordenadas origen;

	/* coordenadas del punto de llegada del camino */
	Coordenadas destino;

	/* que medio de transporte se prefiera utilizar.
	 * si no se encuentra un recorrido se utiliza otro medio de transporte */
	TipoEstacion preferencia;

	/* indica si se desea usar un auto en el camino.
	 * en caso contrario los garajes no se utilizan. */
	bool conAuto;

	/* busca si la linea a la que pertenece una estacion en particular
	 * figura en una lista de estaciones.
	 *
	 * pre : lista y buscada no deben ser NULL
	 * post : devuelve la posicion de la estacion encontrada en la lista, 0 si no se encontro.
	 * 		  El cursor de la lista queda en la posicion de la estacion encontrada.
	 */
	unsigned int lineaEsta(Lista<Estacion*>& lista, Estacion*& buscada);

	/* trata de armar un recorrido entre el origen indicado y mi destino final,
	 * utilizando un tipo de transporte en particular y una lista de
	 * lineas candidatas (son lineas que pasan cerca del origen)
	 *
	 * pre : paradasOrigen no debe ser NULL
	 * post : devuelve un recorrido entre dos estaciones, o NULL si no pudo encontrar un recorrido
	 */
	Recorrido* buscarRecorrido(Lista<Estacion*>& paradasOrigen, Coordenadas& origen, TipoEstacion tipo);

	/* busca dentro de paradasOrigen la estacion mas cercana al destino final del camino
	 * y que pertenezca al tipo indicado.
	 *
	 * pre : paradasOrigen y lineasRechazadas no deben ser NULL
	 * post : devuelve las estaciones mas cercana al origen y al destino en cercanaOrigen y cercanaDestino
	 */
	void conseguirEstaciones(Estacion*& cercanaOrigen, Estacion*& cercanaDestino, Lista<Estacion*>& paradasOrigen, Lista<Estacion*>& lineasRechazadas, TipoEstacion tipo);

	/* arma una lista de posibles lineas a utilizar teniendo en cuento los metros que deseo caminar
	 * y llama a buscarRecorrido para ver si existe un recorrido posible dentro de esas lineas
	 *
	 * post : devuelve un recorrido entre dos estaciones, o NULL si no pudo encontrar un recorrido
	 */
	Recorrido* generarRecorrido(Coordenadas& origen, int metros, TipoEstacion tipo);

	/* verifica que hay una lista de medios de transporte con la que se pueda trabajar
	 *
	 * post : devuelve false si no hay una lista de medios de transporte
	 */
	bool verificarPrecondiciones();

	/* elimina los recorridos encontrados para podes empezar un nuevo camino*/
	void limpiarCamino();

	/* inicializa la lista de recorridos */
	void inicializarCamino();

	/* verifica si el recorrido proporcianado se acerca lo suficiente al destino final
	 *
	 * pre : recorrido no debe ser NULL
	 * post : devuelve true si el recorrido me deja lo suficientemente cerca de mi destino final
	 */
	bool estoyCerca(Recorrido*& recorrido, int distancia);


	/* -------------EASYBMP -------------------*/

		/*
		 * Pre: recibe la direccion de una imagen bmp, un puntero a un recorrido y la distancia
		 * 		horizontal desde el borde izquierdo hacia la derecha.
		 * Post: setea los colores, colorea las estaciones y el trayecto entre las mismas en la
		 * 		 imagen.
		 */
		void colorearRecorrido(BMP&, Recorrido*, unsigned int);

		/*
		 * Pre: recibe la direccion de tres enteros que corresponden a los valores de los colores
		 * 		azul, rojo y verde en ese orden. También recibe un puntero a una estacion.
		 * Post: setea los valores para dichos colores dependiendo del tipo de estacion.
		 */
		void coloresSegunEstacion(ebmpBYTE&, ebmpBYTE&, ebmpBYTE&, Estacion*);

		/*
		 * Pre: recibe tres valores enteros que corresponden a los colores (azul, rojo, verde).
		 * 		La direccion de una imagen bmp y la distancia horizontal desde el borde izquierdo
		 * 		hacia la derecha.
		 * Post: agrega a la imagen las estaciones de origen y destino del recorrido.
		 */
		void colorearEstaciones(ebmpBYTE, ebmpBYTE, ebmpBYTE, BMP&, unsigned int);

		/*
		 * Pre: recibe tres valores (azul, rojo, verde), la direccion de una imagen bmp y dos
		 * 		enteros que indican desde y hasta que pixel se agrega la estacion dentro de la imagen.
		 * Post: colorea la estacion con la mezcla de colores indicada en la ubicacion indicada.
		 * 		Por ejemplo indicar el agregado de la estacion desde el pixel 50 al pixel 100 agregaria
		 * 		la estacion a una distancia de 50 pixeles desde borde horizontal izquierdo hacia la
		 * 		derecha hasta llegar al pixel 100, dotando a la estacion de un tamanio de 50 pixeles.
		 */
		void colorearEstacion(ebmpBYTE, ebmpBYTE, ebmpBYTE, BMP&, unsigned int, unsigned int);

		/*
		 * Pre: recibe la direccion de una imagen bmp y los valores de los pixeles desde donde, hasta
		 * 		donde se debe colorear.
		 * Post: colorea una linea recta mas delgada que una estacion que representa la union entre dos
		 * 		 estaciones.
		 */
		void colorearTrayecto(BMP&, unsigned int, unsigned int);

		/*
		 * Pre: recibe la direccion de una imagen bmp, un puntero apuntando al primer caracter de un
		 * 		texto y dos valores que indican el pixel exacto dentro de la imagen a partir del cual
		 * 		se insertara el texto.
		 * Post: se agrega el texto apuntado por el puntero a la imagen en la ubicacion indicada.
		 */
		void agregarTextoAImagen(BMP&, const char*, unsigned int, unsigned int);

		/*
		 * Pre: recibe la direccion de una imagen bmp, el valor del pixel horizontal desde el cual se
		 * 		desea insertar el texto en la imagen, un entero contador y un puntero a un recorrido.
		 * Post: si el valor del contador es 1, entonces agrega a la imagen textos indicando la linea
		 * 		 y el nombre de la estacion de origen. En caso de que contador sea igual al tamanio de
		 * 		 la lista camino, entonces los textos que se agregan corresponden a la estacion final del
		 * 		 camino. Si contador no toma ninguno de estos dos valores, no hace nada.
		 */
		void agregarTextos(BMP&, unsigned int, unsigned int, Recorrido*);

public:

	/* constructores */
	Camino();
	Camino(Lista<Estacion*>* transportes);
	Camino(Lista<Estacion*>* transportes, Coordenadas& origen, Coordenadas& destino, int distancia, TipoEstacion tipo, bool conAuto);

	/* destructor */
	~Camino();

	/* genera un camino entre el origen y el destino indicados, teniendo en cuenta la distancia
	 * que se desea caminar, y preferentemente (pero no exclusivamente) utilizando un tipo en
	 * particular de medio de transporte
	 *
	 * pre : los medios de transporte deben haber sido previamente cargados (utilizando un
	 * 		 constructor o invocando a setTransportes)
	 * post : devuelve false si las precondiciones no se cumplen
	 */
	bool generarCamino(Coordenadas& origen, Coordenadas& destino, int distancia, TipoEstacion tipo, bool conAuto);

	/* asigna un valor a la variable privada transportes */
	void setTransportes(Lista<Estacion*>*& transportes);

	/* muestra por pantalla el camino armando, y genera un BMP ilustrando el camino.
	 *
	 * pre : se debe haber generado un camino previamente
	 * post : se crea un archivo BMP en la carpeta del ejecutable
	 */
	void imprimirCamino();

	/* compara el camino actual con un camino proporcionado para si los
	 * recorridos son los mismos.
	 *
	 * pre : camino no debe ser NULL
	 * post : se crea un archivo BMP en la carpeta del ejecutable
	 */
	bool esIgual(Camino*& camino);
};


#endif /* CAMINO_H_ */
