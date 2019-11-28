/*
 * transporte.h
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
 */

#ifndef TRANSPORTE_H_
#define TRANSPORTE_H_

#include "Lista.h"
#include "estacion.h"
#include "coordenadas.h"

class Transporte {
private:
	/* constantes para indicar la posicion de cada campo en cada archivo */
	static const int ID;
	static const int NOMBRE;
	static const int LATITUD;
	static const int LONGITUD;
	static const int LINEA;
	static const int IGNORAR;
	static const int FIN;

	/* coordenadas minimas y maximas aceptables, se modifican
	 * a medida que se van cargando las estaciones */
	Coordenadas minimo;
	Coordenadas maximo;

	/* lista de estaciones que se cargan de los archivos csv */
	Lista<Estacion*>* transportes;

	/* modifica las coordenadas maximas y minimas aceptables
	 *
	 * post: modifica las variables privadas minimo y maximo
	 */
	void ajustarMinimoYMaximo(Coordenadas& coordenadas);

	/* carga las estaciones de un csv en la lista privada transportes
	 *
	 * pre: archivo debe ser un archivo valido, orden debe contener un mapeo entre los
	 * campos del archivo y los campos requeridos por la clase (ver constantes privadas)
	 * post: las estaciones leidas se agregan a transportes, se modifica la posicion de su cursor
	 */
	void cargarArchivo(const char* archivo, TipoEstacion tipo, int orden[], char separador);

	/* lee un regsitro de un csv y convierte los campos en variables para crear una nueva Estacion
	 * que se agrega a transportes
	 *
	 * pre: registro debe tener el formato de una linea de un csv, transportes no debe ser NULL
	 * post: una nueva estacion es agregada a transportes, se modifica la posicion de su cursor
	 */
	void agregarEstacion(std::string& registro, TipoEstacion tipo, int orden[], char separador);

	unsigned int lineaEsta(Lista<Estacion*> &lista, Estacion* &buscada);

	void encontrarParadasCercanas(Coordenadas& origen, int metros, TipoEstacion tipo, Lista<Estacion*>& paradasOrigen);

public:
	Transporte();
	~Transporte();

	/* carga los archivos de cada medio de transporte en la list privada transportes
	 *
	 * post: transportes queda cargada con las estaciones de cada csv
	 */
	void cargarTransportes();

	/* devuelve la lista privada de estaciones llamada transportes */
	Lista<Estacion*>*& getTransportes();

	/* devuelve la coordenada minima aceptable
	 *
	 * pre: se debe haber invocado a cargarTransportes() primero
	 */
	Coordenadas& getMinimo();

	/* devuelve la coordenada maxima aceptable
	 *
	 * pre: se debe haber invocado a cargarTransportes() primero
	 */
	Coordenadas& getMaximo();
};



#endif /* TRANSPORTE_H_ */
