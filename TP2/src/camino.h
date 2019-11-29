/*
 * ruta.h
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
 */

#ifndef CAMINO_H_
#define CAMINO_H_

#include "Lista.h"
#include "recorrido.h"
#include "EasyBMP.h"

class Camino {
private:
	/* indica el numero maximo de conexiones que se pueden realizar en un camino */
	static const int MAX_CONEXIONES;

	/* indinca el numero maximo de estasciones de un cierto tipo que se tienen en
	 * consideracion para armar una conexion
	 */
	static const int MAX_CONEXIONES_POR_TIPO;

	/* un distancia muy grande, utilizada para inicializar variables que guardan
	 * la distancia minima entre dos estaciones
	 */
	static const double DISTANCIA_ABSURDA;

	/* lista de recorridos para un mismo camino */
	Lista<Recorrido*>* camino;

	/* puntero al ultimo recorrido del camino mas corto de todos los caminos generados */
	Recorrido* recorridoFinalDelCaminoMasCorto;

	/* la distancia final del camino, es la distincia minima entre todos los caminos generados */
	double distanciaFinal;

	/* lista de medios de transporte a utilizar para armar un camino */
	Lista<Estacion*>* transportes;

	/* coordenadas del punto de partida del camino */
	Coordenadas origen;

	/* coordenadas del punto de llegada del camino */
	Coordenadas destino;

	/* indica si se desea usar un auto en el camino.
	 * en caso contrario los garajes no se utilizan. */
	bool conAuto;

	/* la distancia que se desea caminar entre estaciones/conexiones */
	int distanciaCaminar;

	/* busca si la linea a la que pertenece una estacion en particular
	 * figura en una lista de estaciones.
	 *
	 * pre : lista y buscada no deben ser NULL
	 * post : devuelve la posicion de la estacion encontrada en la lista, 0 si no se encontro.
	 * 		  El cursor de la lista queda en la posicion de la estacion encontrada.
	 */
	unsigned int lineaEsta(Lista<Estacion*>& lista, Estacion*& buscada);

	/* verifica que hay una lista de medios de transporte con la que se pueda trabajar
	 *
	 * post : devuelve false si no hay una lista de medios de transporte
	 */
	bool verificarPrecondiciones();

	/* elimina los recorridos encontrados para poder empezar un nuevo camino*/
	void limpiarCamino();

	/* inicializa la lista de recorridos */
	void inicializarCamino();

	/* verifica si el recorrido proporcianado se acerca lo suficiente al destino final
	 *
	 * pre : recorrido no debe ser NULL
	 * post : devuelve true si el recorrido me deja lo suficientemente cerca de mi destino final
	 */
	bool estoyCerca(Recorrido*& recorrido);

	/* arma un recorrido entre la estacion de partida y una estacion de la misma linea que se
	 * encuentre lo mas cerca posible del destino final.
	 *
	 * pre : partida no debe ser NULL
	 * post : devuelve un nuevo recorrido que contiene la distancia total recorrida hasta el momento y
	 * 		  un puntero al recorrido anterior. si no se encuentra una estacion de destino valida
	 * 		  devuelve NULL
	 */
	Recorrido* generarRecorrido(Estacion* partida, double total, Recorrido* recorridoAnterior);

	/* verifica que se puedan seguir creando recorridos de un cierto tipo antes de llamar a generarRecorrido
	 *
	 * pre : nuevosOrigenes contiene los posibles puntos de partida del recorrido y no debe ser NULL
	 * post : devuelve un nuevo recorrido de un tipo en particular si no se supero MAX_CONEXIONES_POR_TIPO.
	 * 		  en caso contrario devuelve NULL
	 */
	Recorrido* crearRecorrido(Lista<Estacion*>& nuevosOrigenes, int cantidadPorTipo[], double distanciaTotal, Recorrido* recorrido);

	/* devuelve una lista de estaciones cercanas a unas ciertas coordenadas
	 *
	 * pre : paradasOrigen no debe ser NULL
	 * post : carga paradasOrgien con estaciones que se encuentren a distanciaCaminar de origen
	 */
	void encontrarParadasCercanas(const Coordenadas& origen, Lista<Estacion*>& paradasOrigen);

	/* arma todos los caminos posibles entre el origen y el destino final
	 *
	 * pre : destino, distanciaCaminar y conAuto deben contener valores validos.
	 * post : se crean recorridos enlazados entre si para formar caminos desde origen hasta destino
	 */
	void agregarRecorrido(Recorrido* r, int conexiones);

	/* busca entre los caminos armados cual es el mas corto basandose en la distantciaTotal del
	 * ultimo recorrido de cada camino
	 *
	 * pre : se deben haber armado los caminos candidatos previamente
	 * post : modifica recorridoFinalDelCaminoMasCorto para que apunte al ultimo recorrido
	 * 		  del camino mas corto
	 */
	void buscarCaminoMasCorto(Recorrido* r);

	/* arma una lista con los recorridos pertenecientes al camino mas corto
	 *
	 * pre : recorridoFinalDelCaminoMasCorto debe haber sido previamente
	 * 		inicializada llamando a buscarCaminoMasCorto()
	 * post : la lista camino queda cargada con los recorridos del camino mas corto
	 */
	void crearCaminoMasCorto();

	/* remueve de la memoria los recorridos de los caminos que fueron descartados por
	 * no ser los mas cortos
	 *
	 * pre : el parametro recorrido debe apuntar al primer recorrido de un camino
	 * post : los recorridos que fueron descartados son eliminados
	 */
	void limpiarRecorridos(Recorrido* recorrido);

	/* busca si un recorrido pertenece a la lista de recorridos del camino mas corto
	 *
	 * pre : camino debe estar cargada con el camino mas corto
	 * post : devuelve true si el recorrido pertence al camino mas corto, false
	 * 		  en caso contrario
	 */
	bool buscarRecorridoEnCamino(Recorrido* recorrido);


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
	Camino(Lista<Estacion*>* transportes);

	/* destructor */
	~Camino();

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
	 * post: devuelve true si los recorridos de los caminos coinciden
	 */
	bool esIgual(Camino*& camino);

	/* genera varios caminos posibles entre origen y destino, y finalmente guarda en camino
	 * el mas corto de todos los caminos generados
	 *
	 * pre : la lista de transportes debe haber sido previamente cargada
	 * post: devuelve true si se pudo generar un camino, false en caso contrario
	 */
	bool generarCaminos(Coordenadas& origen, Coordenadas& destino, int distancia, bool conAuto);

	double obtenerPrecio();

};


#endif /* CAMINO_H_ */
