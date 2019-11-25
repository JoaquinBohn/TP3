/*
 * ruta.cpp
 *
 *  Created on: Oct 30, 2019
 *      Author: cristian
 */

#include "camino.h"
#include <iostream>
#include "EasyBMP.h"
#include "EasyBMP_Font.h"
#include "EasyBMP_Geometry.h"

Camino::Camino() {
	this->transportes = NULL;
	this->camino = new Lista<Recorrido*>;
	this->conAuto = false;
	this->preferencia = indefinido;
}

Camino::Camino(Lista<Estacion*>* transportes) {
	this->camino = new Lista<Recorrido*>;
	this->transportes = transportes;
	this->conAuto = false;
	this->preferencia = indefinido;
}

Camino::Camino(Lista<Estacion*>* transportes, Coordenadas& origen, Coordenadas& destino, int distancia, TipoEstacion tipo, bool conAuto) {
	this->camino = new Lista<Recorrido*>;
	this->transportes = transportes;
	generarCamino(origen, destino, distancia, tipo, conAuto);
}

Camino::~Camino() {
	limpiarCamino();
}

unsigned int Camino::lineaEsta(Lista<Estacion*> &lista, Estacion* &buscada) {
	bool esta = false;
	int posicion = 0;

	lista.iniciarCursor();
	while(!esta && lista.avanzarCursor()) {
		posicion++;
		Estacion* e = lista.obtenerCursor();
		if (e->getLinea().compare(buscada->getLinea()) == 0) {
			esta = true;
		}
	}

	return (esta) ? posicion : 0;
}

Recorrido* Camino::generarRecorrido(Coordenadas& origen, int metros, TipoEstacion tipo) {
	Lista<Estacion*> paradasOrigen;
	Recorrido* recorrido = NULL;

	double distancia;
	this->transportes->iniciarCursor();

	/* recorro la lista de medios de transporte buscando estaciones que esten a
	 * "metros" de distancia del origen
	 */
	while(this->transportes->avanzarCursor()) {
		Estacion* e = this->transportes->obtenerCursor();

		/* si tipo no es indefinido, descarto las estaciones que no coincidan con el tipo indicado */
		if (tipo == indefinido || e->getTipo() == tipo) {

			/* si no uso el auto descarto los garajes */
			if (e->getTipo() != garaje || this->conAuto) {
				distancia = e->getCoordenadas().distancia(origen);
				if (distancia < metros) {
					int posicion = lineaEsta(paradasOrigen, e);
					/* si la linea esta entre las candidatas pero esta estacion
					 * esta mas cerca que la anterior, la agrego */
					if (posicion > 0) {
						int distanciaVieja = paradasOrigen.obtenerCursor()->getCoordenadas().distancia(origen);
						if (distancia < distanciaVieja) {
							paradasOrigen.remover(posicion);
							paradasOrigen.agregar(e);
						}
					} else {
						/* si la linea no esta todavia dentro de las candidatas, la agrego */
						paradasOrigen.agregar(e);
					}
				}
			}
		}
	}

	/* si encontre lineas candidatas, busco un recorrido posible dentro de esas lineas */
	if (!paradasOrigen.estaVacia()) {
		recorrido = buscarRecorrido(paradasOrigen, origen, tipo);
	}

	/* devuelvo NULL si no encontre un recorrido */
	return recorrido;
}

Recorrido* Camino::buscarRecorrido(Lista<Estacion*>& paradasOrigen, Coordenadas& origen, TipoEstacion tipo) {
	Estacion* cercanaOrigen = NULL;
	Estacion* cercanaDestino = NULL;
	Recorrido* recorrido = NULL;
	Lista<Estacion*> lineasRechazadas;
	bool encontrado = false;

	while (!encontrado) {
		/* busco una estacion dentro de una lista de posibles lineas candidatas
		 * que sea de un cierto tipo y este cerca de mi destino final, y tambien me quedo
		 * con el origen correspondiente */
		conseguirEstaciones(cercanaOrigen, cercanaDestino, paradasOrigen, lineasRechazadas, tipo);

		/* si las dos estaciones que encontre son la misma, descarto la linea */
		if (cercanaOrigen->getNombre().compare(cercanaDestino->getNombre()) == 0) {
			lineasRechazadas.agregar(cercanaDestino);

			/* si la cantidad de lineas descartas es igual a la cantidad
			 * de lineas candidatas, dejo de buscar un recorrido
			 */
			if (lineasRechazadas.contarElementos() == paradasOrigen.contarElementos()) {
				encontrado = true;
			}
		} else {
			recorrido = new Recorrido(cercanaOrigen, cercanaDestino);
			encontrado = true;
		}
	}

	/* devulevo NULL si no encontre un recorrido */
	return recorrido;
}

void Camino::conseguirEstaciones(Estacion*& cercanaOrigen, Estacion*& cercanaDestino, Lista<Estacion*> &paradasOrigen, Lista<Estacion*>& lineasRechazadas, TipoEstacion tipo) {
	/* incializo la distancia minima con una distancia exageradamente grande */
	double distanciaMinima = 100000000;

	/* recorro la lista de medios de transporte buscando la estacion mas cercana
	 * a mi destino final
	 */
	this->transportes->iniciarCursor();
	while(this->transportes->avanzarCursor()) {
		Estacion* e = this->transportes->obtenerCursor();

		/* si tipo no es indefinido, descarto las estaciones que no coincidan con el tipo indicado */
		if (tipo == indefinido || e->getTipo() == tipo) {

			/* si no uso el auto descarto los garajes */
			if (e->getTipo() != garaje || this->conAuto) {

				/* solo me interesan la estaciones que pertenezcan a las lineas que pasan
				 * cerca de mi origen y que no hayan sido rechazadas anteriormente
				 */
				if(lineaEsta(paradasOrigen, e) && !lineaEsta(lineasRechazadas, e)) {
					double distancia = e->getCoordenadas().distancia(this->destino);
					if (distancia < distanciaMinima) {
						distanciaMinima = distancia;
						cercanaDestino = e;
						cercanaOrigen = paradasOrigen.obtenerCursor();
					}
				}
			}
		}
	}
}

bool Camino::verificarPrecondiciones() {
	bool verificado = true;
	if (this->transportes == NULL) {
		verificado = false;
	}

	return verificado;
}

void Camino::limpiarCamino() {
	if (!(this->camino == NULL || this->camino->estaVacia())) {
		this->camino->iniciarCursor();
		while (this->camino->avanzarCursor()) {
			delete this->camino->obtenerCursor();
		}
	}
	delete this->camino;
	this->camino = NULL;
}

void Camino::inicializarCamino() {
	limpiarCamino();
	this->camino = new Lista<Recorrido*>;
}

bool Camino::estoyCerca(Recorrido*& recorrido, int distancia) {
	return (recorrido->getDestino()->getCoordenadas().distancia(this->destino) < distancia);
}

bool Camino::generarCamino(Coordenadas& origen, Coordenadas& destino, int distancia, TipoEstacion tipo, bool conAuto) {
	Recorrido* recorrido;
	bool hayCaminos = true;

	if (!verificarPrecondiciones()) {
		return false;
	}

	inicializarCamino();

	this->origen = origen;
	this->destino = destino;
	this->preferencia = tipo;
	this->conAuto = conAuto;

	Coordenadas nuevoOrigen = origen;

	do {
		/* primero busco un recorrido utilizando el tipo de medio de transporte preferido,
		 * si no se encuentra ningun recorrido busco otro utilizando culaquier tipo
		 * de medio de transporte
		 */
		recorrido = generarRecorrido(nuevoOrigen, distancia, tipo);
		if (recorrido == NULL) {
			recorrido = generarRecorrido(nuevoOrigen, distancia, indefinido);
		}
		if (recorrido == NULL) {
			/* no puedo llegar al destino final, no hay camino */
			limpiarCamino();
			hayCaminos = false;
		} else {
			this->camino->agregar(recorrido);

			if (estoyCerca(recorrido, distancia)) {
				/* llegue a mi destino final, fin del camino */
				hayCaminos = false;
			} else {
				/* cambio el origen para que el proximo recorrido lo busque a partir
				 * de hasta donde llegue con mi ultimo recorrido
				 */
				nuevoOrigen = recorrido->getDestino()->getCoordenadas();
			}
		}
	} while(hayCaminos);

	return true;
}

void Camino::setTransportes(Lista<Estacion*> *&transportes) {
	this->transportes = transportes;
}

void Camino::imprimirCamino() {
	std::cout << "Camino prefiriendo " << Estacion::TIPOS[this->preferencia] << ":" << std::endl;
	if (this->camino == NULL || this->camino->estaVacia()) {
		std::cout << "No hay camino." << std::endl;
	} else {
		this->camino->iniciarCursor();
		/*largo corresponde a una ubicacion dentro de la imagen bmp*/
		unsigned int largo=50, contador=1;
		/*se crea un archivo tipo bmp*/
		BMP imagen;
		int cantidad = this->camino->contarElementos();
		/*configura el tamanio de la imagen ajustandose a la cantidad
		 * de recorridos del camino */
		imagen.SetSize(640*cantidad,480);
		imagen.SetBitDepth(8);

		while(this->camino->avanzarCursor()) {
			Recorrido* recorrido = this->camino->obtenerCursor();
			/*colorearRecorrido agrega las estaciones a la imagen*/
			this->colorearRecorrido(imagen, recorrido, largo);
			/*mientras queden recorridos se agregan uniones entre ellos*/
			if(contador<(this->camino->contarElementos())){
				/*colorearTrayecto agrega dichas uniones*/
				this->colorearTrayecto(imagen, largo+395, largo+475);
			}
			/*se agregan los nombres de las estaciones de origen y destino*/
			this->agregarTextos(imagen, largo, contador, recorrido);
			/*se suma a largo el tamanio ocupado en la imagen de todo lo anterior
			 * para continuar desde alli en la proxima iteracion*/
			largo += 480;
			contador++;

			std::cout << Estacion::TIPOS[recorrido->getOrigen()->getTipo()] << " "
					<< recorrido->getOrigen()->getLinea()
					<< ": de " << recorrido->getOrigen()->getNombre()
					<< " hasta " << recorrido->getDestino()->getNombre() << std::endl;
		}
		/*se guarda la imagen en el archivo bmp*/
		imagen.WriteToFile((std::string("imagenRecorrido-") + Estacion::TIPOS[this->preferencia] + std::string(".bmp")).c_str());
	}
	std::cout << std::endl;
}

bool Camino::esIgual(Camino*& camino) {
	bool sonIguales = true;

	if (camino == NULL || camino->camino == NULL) {
		sonIguales = false;
	}
	else if (this->camino->contarElementos() != camino->camino->contarElementos()) {
		sonIguales = false;
	} else {
		this->camino->iniciarCursor();
		camino->camino->iniciarCursor();

		while(sonIguales && this->camino->avanzarCursor()) {
			camino->camino->avanzarCursor();
			Recorrido* recorrido1 = this->camino->obtenerCursor();
			Recorrido* recorrido2 = camino->camino->obtenerCursor();

			if (!recorrido1->esIgual(recorrido2)) {
				sonIguales = false;
			}
		}
	}

	return sonIguales;
}


/* --------------- EASYBMP ---------------------*/


void Camino::colorearRecorrido(BMP& imagen, Recorrido* recorrido, unsigned int largo){
	/*se crea una paleta de colores*/
	ebmpBYTE azul, rojo, verde;
	/*configura los valores para la paleta de colores segun el tipo de estacion*/
	this->coloresSegunEstacion(azul, rojo, verde, recorrido->getOrigen());

	/*agrega las estaciones del recorrido a la imagen*/
	this->colorearEstaciones(azul,rojo, verde, imagen, largo);
	/*agrega la union entre las estaciones del recorrido*/
	this->colorearTrayecto(imagen, largo+155, largo+235);
}

void Camino::coloresSegunEstacion(ebmpBYTE& color1, ebmpBYTE& color2, ebmpBYTE& color3, Estacion* estacion){
	if(estacion->getTipo() == subte){
		color1 = 0;
		color2 = 150;
		color3 = 150;
	}else if(estacion->getTipo() == colectivo){
		color1 = 200;
		color2 = 0;
		color3 = 0;
	}else if(estacion->getTipo() == tren){
		color1 = 0;
		color2 = 100;
		color3 = 0;
	}else if(estacion->getTipo() == metrobus){
		color1 = 100;
		color2 = 100;
		color3 = 50;
	}else{
		color1 = 150;
		color2 = 0;
		color3 = 150;
	}
}

void Camino::colorearEstaciones(ebmpBYTE color1, ebmpBYTE color2, ebmpBYTE color3, BMP& imagen, unsigned int largo){
	/*agrega la estacion de origen del recorrido*/
	this->colorearEstacion(color1, color2, color3, imagen, largo, largo+150);
	/*agrega la estacion de destino del recorrido*/
	this->colorearEstacion(color1, color2, color3, imagen, largo+240, largo+390);
}

void Camino::colorearEstacion(ebmpBYTE color1, ebmpBYTE color2, ebmpBYTE color3, BMP& imagen, unsigned int iInicio, unsigned int iFinal){
	/*recorre pixel por pixel desde la ubicacion indicada hasta el final de ella
	 * y agrega el color que corresponda a cada pixel para colorear la estacion*/
	for(unsigned int i=iInicio; i<iFinal; i++){
		for(unsigned int j=200; j<280; j++){
			imagen(i,j)->Blue = color1;
			imagen(i,j)->Red = color2;
			imagen(i,j)->Green = color3;
		}
	}
}

void Camino::colorearTrayecto(BMP& imagen, unsigned int iInicio, unsigned int iFinal){
	/*recorre piexel por pixel desde la ubicacion indicada hasta el final de ella
	 * y agrega color para colorear la union entre estaciones*/
	for(unsigned int i=iInicio; i<iFinal; i++){
		for(unsigned int j=235; j<245; j++){
			imagen(i,j)->Blue = 0;
			imagen(i,j)->Red = 0;
			imagen(i,j)->Green = 200;
		}
	}
}

void Camino::agregarTextoAImagen(BMP& imagen, const char* texto, unsigned int x, unsigned int y){
	/*crea una paleta de colores*/
	RGBApixel fontColor;
	/*configura los valores de la paleta de colores*/
	fontColor.Red = 255; fontColor.Green = 0; fontColor.Blue = 0; fontColor.Alpha = 255;
	char* textoAImprimir;
	textoAImprimir = new char[50];
	/*se copia el texto del archivo a un puntero a char para agregar dicho texto a la imagen*/
	strcpy(textoAImprimir, texto);
	/*PrintString agrega el texto a la imagen en la ubicacion (x,y) con un tamanio de fuente
	 * 20 y la paleta de colores configurada*/
	PrintString(imagen, textoAImprimir, x, y, 10, fontColor);
	/*se libera la memoria*/
	delete textoAImprimir;
}

void Camino::agregarTextos(BMP& imagen,unsigned int largo, unsigned int contador, Recorrido* recorrido){
	/*si es la primera estacion del camino, toma la linea y el nombre de la estacion,
	 * y los agrega a la imagen*/
	if(contador==1){
		std::string lineaTransporte = recorrido->getOrigen()->getLinea();
		const char* linea = lineaTransporte.c_str();
		std::string nombreTransporte = recorrido->getOrigen()->getNombre();
		const char* nombre = nombreTransporte.c_str();
		this->agregarTextoAImagen(imagen, linea, largo, 290);
		this->agregarTextoAImagen(imagen, nombre, largo, 315);
	/*el mismo proceso pero para la ultima estacion del camino*/
	}
	if(contador==(this->camino->contarElementos())){
		std::string lineaTransporte = recorrido->getDestino()->getLinea();
		const char* linea = lineaTransporte.c_str();
		std::string nombreTransporte = recorrido->getDestino()->getNombre();
		const char* nombre = nombreTransporte.c_str();
		this->agregarTextoAImagen(imagen, linea, largo+240, 290);
		this->agregarTextoAImagen(imagen, nombre, largo+240, 315);
	}
}







